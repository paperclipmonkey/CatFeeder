# OmNomCat - An automated Cat Feeder
OmNomCat was created for M79 - Interactive Hardware and Devices - module at Swansea University.

The project chosen was to create a hardware platform that allowed the automated feeding of more than one cat. It is implemented in code with Arduino.

It consists of two main tasks:

* Track cats using the device - This is done using RFID. When a cat uses the device this is logged and displayed on a series of LEDs that track how long ago this interaction occurred.
* Automatically dispense food at a pre-determined interval. This is set using a potentiometer and displayed on an LCD screen mounted to the device. A servo motor is driven which connects directly to the dispenser paddles.
