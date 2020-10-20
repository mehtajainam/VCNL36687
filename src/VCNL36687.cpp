/**************************************************************************/
/*! 
  @file VCNL36687.cpp

  @section intro Introduction
  This is an Arduino library for the Vishay VCNL36687 VCSEL based proximity sensor

  @section author Author
  Jainam Mehta
  jainam1995@gmail.com
*/
/**************************************************************************/

#include "VCNL36687.h" // Include header definition

/* Instantiate a new VCNL36687 class */
VCNL36687::VCNL36687() {
  _i2caddr = VCNL36687_SlaveAddress;
}

/* Check that VCNL36687 exists and begin I2C communication */
boolean VCNL36687::exists() {
  Wire.begin();
  Wire.beginTransmission(_i2caddr);
  Wire.write(VCNL36687_PS_ID);
  Wire.endTransmission(false);
  Wire.requestFrom(_i2caddr, uint8_t(2));
  byte lowByte = Wire.read();
  byte highByte = Wire.read();
  
  
  //Strange that lowByte returns 0xFF (255) every time. Documentation says it should return 0x88 for lowByte
  // if ((lowByte == 0x88) && (highByte == 0x10)) {
  //   return true;
  // }
  // return false;

  Serial.println(lowByte);
  Serial.println(highByte);

  return true;
}


/**************************************************************************/
/*!
    @brief  Setup and basic functions to get a proximity reading
*/
/**************************************************************************/

/* Set up initialization parameters */
boolean VCNL36687::initialize() {

  SetVCSELCurrent(); // Set current to 20mA
  CONF1();// Setup CONF1 and CONF2
  CONF5(); // Setup CONF5

  //Set the PS interrupt levels
  write16_LowHigh(VCNL36687_PS_THDL, B10001000, B00010011);
  write16_LowHigh(VCNL36687_PS_THDH, B11100000, B00101110);

  return true;
}

/* Set register CONF4 for VCSEL (laser) current 
   VCSEL_I 2:0 - 7, 11, 14, 17 or 20mA */
boolean VCNL36687::SetVCSELCurrent(uint8_t conf3, uint8_t conf4) {
  write16_LowHigh(VCNL36687_PS_CONF4, conf3, conf4);
  return true;
}

/* Set registers CONF1 and CONF2
   PS_Period
   PS_PERS
   PS_INT
   PS_SD (set to 0 to turn on proximity sensor) */
boolean VCNL36687::CONF1(uint8_t conf1, uint8_t conf2) {
  write16_LowHigh(VCNL36687_PS_CONF1, conf1, conf2);
  return true;
}

/* Set register CONF5 (0x08)
   POR_S (set to 1 to use proximity sensor) */
boolean VCNL36687::CONF5(uint8_t conf5_L, uint8_t conf5_M) {
  write16_LowHigh(VCNL36687_PS_CONF5, conf5_L, conf5_M);
  return true;
}

/* Get 16-bit proximity measurement value */
uint16_t VCNL36687::readProximity() {
  return readData(VCNL36687_PS_DATA);
}


/**************************************************************************/
/*!
    @brief  I2C low level interfacing
*/
/**************************************************************************/

/* Read 2 bytes from the VCNL36687 */
uint16_t VCNL36687::readData(uint8_t command_code)
{
  uint16_t reading;
  Wire.beginTransmission(_i2caddr);
  Wire.write(command_code);
  Wire.endTransmission(false);
  Wire.requestFrom(_i2caddr, uint8_t(2));
  while (!Wire.available());
  uint8_t byteLow = Wire.read();
  while (!Wire.available());
  uint16_t byteHigh = Wire.read();
  reading = (byteHigh <<= 8) + byteLow;
  
  return reading;
}

/* Write 2 bytes to the VCNL36687, data byte low then high */
void VCNL36687::write16_LowHigh(uint8_t address, uint8_t low, uint8_t high)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(low);
  Wire.write(high);
  Wire.endTransmission();
}

/* 8-bit I2C write function */
void VCNL36687::write8(uint8_t address, uint8_t data) //Original
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}



// Read 1 byte from the VCNL4000 at 'address'
// uint8_t VCNL36687::read8(uint8_t address)
// {
//   uint8_t data;

//   _wire->beginTransmission(_i2caddr);
// #if ARDUINO >= 100
//   _wire->write(address);
// #else
//   _wire->send(address);
// #endif
//   _wire->endTransmission(false); // send repeated stop bit

//   delayMicroseconds(170);  // delay required

//   _wire->requestFrom(_i2caddr, (uint8_t)1);

// #if ARDUINO >= 100
//   return _wire->read();
// #else
//   return _wire->receive();
// #endif
// }


// Read 2 byte from the VCNL4000 at 'address'
// uint16_t VCNL36687::read16(uint8_t address)
// {
//   uint16_t data;

//   _wire->beginTransmission(_i2caddr);
// #if ARDUINO >= 100
//   _wire->write(address);
// #else
//   _wire->send(address);
// #endif

//   _wire->endTransmission(false); // send repeated stop bit

//   delayMicroseconds(170);  // delay required

//   _wire->requestFrom(_i2caddr, (uint8_t)2);
//   while(!_wire->available());
// #if ARDUINO >= 100
//   data = _wire->read();
//   data <<= 8;
//   while(!_wire->available());
//   data |= _wire->read();
// #else
//   data = _wire->receive();
//   data <<= 8;
//   while(!_wire->available());
//   data |= _wire->receive();
// #endif

//   return data;
// }

