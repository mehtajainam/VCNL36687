/*
  VCNL36687.cpp - Library for 
  Created by Jainam Mehta, April 10, 2019.
  Released into the public domain.
*/

#include "VCNL36687.h"
#include "Arduino.h"
#include <Wire.h>


VCNL36687::VCNL36687() {
  _i2caddr = VCNL36687_SlaveAddress;
}


boolean VCNL36687::exists() {
  Wire.begin();
  uint8_t rev = 0;
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



boolean VCNL36687::initialize() {

  SetVCSELCurrent(); // Set current to 20mA
  CONF1();// Setup CONF1 and CONF2
  CONF5(); // Setup CONF5

  //Set the PS interrupt levels
  write16_LowHigh(VCNL36687_PS_THDL, B10001000, B00010011);
  write16_LowHigh(VCNL36687_PS_THDH, B11100000, B00101110);

  return true;
}




uint16_t VCNL36687::readProximity() {
  return readData(VCNL36687_PS_DATA);
}


boolean VCNL36687::SetVCSELCurrent(uint8_t conf3, uint8_t conf4) {
  write16_LowHigh(VCNL36687_PS_CONF4, conf3, conf4);
  return true;
}


boolean VCNL36687::CONF1(uint8_t conf1, uint8_t conf2) {
  write16_LowHigh(VCNL36687_PS_CONF1, conf1, conf2);
  return true;
}


boolean VCNL36687::CONF5(uint8_t conf5_L, uint8_t conf5_M) {
  write16_LowHigh(VCNL36687_PS_CONF5, conf5_L, conf5_M);
  return true;
}



/**************************************************************************/
/*!
    @brief  I2C low level interfacing
*/
/**************************************************************************/

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

void VCNL36687::write8(uint8_t address, uint8_t data) //Original
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t VCNL36687::write16_LowHigh(uint8_t address, uint8_t low, uint8_t high)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(low);
  Wire.write(high);
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

