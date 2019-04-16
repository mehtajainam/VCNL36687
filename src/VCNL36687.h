/**************************************************************************/
/*! 
  @file VCNL36687.h

  @section intro Introduction
  This is an Arduino library for the Vishay VCNL36687 VCSEL based proximity sensor

  @section author Author
  Jainam Mehta
  jainam1995@gmail.com
*/
/**************************************************************************/

#ifndef VCNL36687_h
#define VCNL36687_h


#include "Arduino.h" // Arduino data type definitions
#include <Wire.h> // Standard I2C "Wire" library

/********************************************
** Declare all constants used in the class **
********************************************/

#define VCNL36687_SlaveAddress    0x60   ///< I2C address of the sensor

/** Registers */
#define VCNL36687_PS_CONF1      0x03
#define VCNL36687_PS_CONF2      0x03
#define VCNL36687_PS_CONF3      0x04
#define VCNL36687_PS_CONF4      0x04

#define VCNL36687_PS_THDL     0x05
#define VCNL36687_PS_THDH     0x06
#define VCNL36687_PS_CANC     0x07
#define VCNL36687_PS_CONF5      0x08
#define VCNL36687_PS_DATA     0xF2
#define VCNL36687_PS_INT_FLAG   0xF3
#define VCNL36687_PS_ID       0xF4

//Table 2 Datasheet Register 0x03 Low Byte
#define VCNL36687_PS_PERIOD_8ms   0x00<<6
#define VCNL36687_PS_PERIOD_16ms  0x01<<6
#define VCNL36687_PS_PERIOD_32ms  0x02<<6
#define VCNL36687_PS_PERIOD_64ms  0x03<<6
#define VCNL36686_PS_PERS_1     0x00<<4
#define VCNL36687_PS_PERS_2     0x01<<4
#define VCNL36687_PS_PERS_3     0x02<<4
#define VCNL36687_PS_PERS_4     0x03<<4
#define VCNL36687_PS_INT_DIS    0x01<<2
#define VCNL36687_PS_INT_EN     0x02<<2
#define VCNL36687_PS_INT_Logic    0x03<<2
#define VCNL36687_PS_SMART_PERS_EN  0x01<<1
#define VCNL36687_PS_ShutDown   0x01<<0
#define VCNL36687_PS_ON       0x00<<0

//Table 3 Datasheet Register 0x03 High Byte
#define VCNL36687_PS_1T       0x00<<6
#define VCNL36687_PS_2T       0x01<<6
#define VCNL36687_PS_4T       0x02<<6
#define VCNL36687_PS_8T       0x03<<6
#define VCNL36687_PS_MPS_1      0x00<<4
#define VCNL36687_PS_MPS_2      0x01<<4
#define VCNL36687_PS_MPS_4      0x02<<4
#define VCNL36687_PS_MPS_8      0x03<<4
#define VCNL36687_PS_ITB_25     0x00<<3
#define VCNL36687_PS_ITB_50     0x01<<3

//Table 4 Datasheet Register 4 Low Byte
#define VCNL36687_PS_AF_EN      0x01<<6
#define VCNL36687_PS_Auto     0x00<<6
#define VCNL36687_PS_FOR_Trig   0x01<<5

//Table 6 Datasheet Register 4 High Byte
#define VCNL36687_PS_SC_EN      0x01<<7
#define VCNL36687_PS_SC_CURRx1    0x00<<5
#define VCNL36687_PS_SC_CURRx2    0x01<<5
#define VCNL36687_PS_SC_CURRx4    0x02<<5
#define VCNL36687_PS_SC_CURRx8    0x03<<5
#define VCNL36687_PS_HD_EN      0x01<<4
#define VNCL36687_VCSEL_I_7mA   0x00<<0
#define VCNL36687_VCSEL_I_11mA    0x01<<0
#define VCNL36687_VCSEL_I_14mA    0x02<<0
#define VCNL36687_VCSEL_I_17mA    0x03<<0
#define VCNL36687_VCSEL_I_20mA    0x04<<0

//Table 9 Datasheet Register 9 Low Byte
#define VCNL36887_POR_S       0x01<<0



/**************************************************************************/
/*!
    @brief  The VCNL36687 class
*/
/**************************************************************************/
class VCNL36687 {
  public:
    VCNL36687();
    boolean exists();
    boolean initialize();

    // Edit the binary settings here to change default startup options
    boolean SetVCSELCurrent(uint8_t c3 = B00000000, uint8_t c4 = B00010100);
    boolean CONF1(uint8_t c1 = B10000000, uint8_t c2 = B01000000);
    boolean CONF5(uint8_t c5_L = B00000001, uint8_t c5_M = B00000000);

    uint16_t readProximity(void);
    

  private:
    void write8(uint8_t address, uint8_t data);
    uint8_t write16_LowHigh(uint8_t address, uint8_t low, uint8_t high);
    uint16_t readData(uint8_t command_code);

    uint8_t _i2caddr;
    TwoWire *_wire;
};

#endif
