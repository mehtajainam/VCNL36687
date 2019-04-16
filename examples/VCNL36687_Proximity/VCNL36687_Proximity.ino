/********************************************************************************************
VCNL36687_Proximity.ino
Jainam Mehta
jainam1995@gmail.com

Example program for using the VCNL36687 library.

The VCNL36687 library uses the standard I2C library and assumes that the default hardware 
I2C ports for SDA and SCL are being utilized. The address of the VCNL36687 is hardcoded at 
0x60 and cannot be changed.                                                                                                                             

********************************************************************************************/
#include "VCNL36687.h" // include the library

VCNL36687 vcnl;

void setup() {
  Serial.begin(9600);
  Serial.println("VCNL36687 test");

  while (!Serial);
  Serial.println("Booting.");
  if (vcnl.exists()) {
    Serial.println("VCNL36687 found");
    vcnl.initialize();
    Serial.println("VCNL36687 initialized");
  }

  delay(500);
  
  Serial.println("Entering loop.....");
}


void loop() {
   
  Serial.print("Proximity: ");
  Serial.println(vcnl.readProximity());

  delay(100);
}
