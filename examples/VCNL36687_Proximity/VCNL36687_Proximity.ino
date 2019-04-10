#include <Wire.h>
#include "VCNL36687.h"

VCNL36687 vcnl;
// int reading;


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

  // reading = vcnl.readProximity();
  // Serial.println("Proximity = ");
  // Serial.println(reading);

  delay(100);
}
