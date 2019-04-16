# VCNL36687 Arduino library
Arduino library for the [VCNL36687 proximity sensor](http://www.vishay.com/ppg?84907)

## Sensor description
VCNL36687S by Vishay Intertechnology, Inc is a fully integrated proximity sensor that combines a high power vertical-cavity surface-emitting laser (VCSEL), a photodiode, a signal processing IC, and a 12-bit ADC in a single package. The new VCNL36687S is designed to be used in smartphones, tablets, virtual reality / augmented reality (VR / AR) headsets and other battery-operated devices.

Through its standard I2C bus serial digital interface, the VCNL36687S allows easy access to the proximity signal. Its programmable interrupt function offers wake-up functionality for the microcontroller when a proximity change occurs, which reduces processing overhead by eliminating the need for continuous polling.

Compared to previous generation devices, the VCNL36687S requires less energy to carry out the same functionality; with a 20 mA pulse current, the VCNL36687S can detect a Kodak Gray Card at a distance of 20 cm, where previous VCNL series devices required 200 mA of current.    

* Datasheet: https://www.vishay.com/docs/84907/vcnl36687s.pdf
* Eval board: http://www.vishay.com/landingpage/SensorXplorer/

## Usage

This library supports I2C commmunication with the VCNL36687, 2 pins are required to interface

### Installation

Simply clone or download this library into your Arduino/libraries folder.

### Proximity sensing

The proximity sensor has a range of approximately 20 cm (or 7.9 in.)

### Example list

* **Proximity**: demonstrates declaring an _VCNL36687_ object, initializing the sensor and reading data from the proximity sensor

## Hardware

Please refer to the [VCNL36687 datasheet](https://www.vishay.com/docs/84907/vcnl36687s.pdf) and your microcontroller's pinout diagram. This library was developed using the [VCNL36687S Sensor Evaluation Board](http://www.vishay.com/docs/84967/vcnl36687ssensorboardfiles.pdf) from Vishay Semiconductors. 

### Wiring and I2C

The VCNL36687 pins should be connected as:

1. GND: ground
2. VPP: 1.65V to 1.95V power source
3. VDD: 1.65V to 1.95V power source
4. VCSEL_A: 2.68V to 4.8V power source
5. VCSEL_C: ground
6. INT: (optional) connect to interruptable pin on microcontroller
7. SDA: connect to SDA
8. SCA: connect to SCL

Addtional resistors (2.4 kΩ to 10 kΩ) should be used as pullups on SCL and SDA.

### Compatibility

This library has been tested with:
* Arduino Uno
* nRF52 Development Kit from Nordic
