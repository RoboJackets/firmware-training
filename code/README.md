# Arduino IDE Installation Instructions

1. Download the Arduino IDE [here](https://www.arduino.cc/en/software). Just do a normal install.

2. Most of Arduino Nanos are old, so they need the old bootloader. Follow the instructions [here](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all) to install the old bootloader.

3. Before uploading to the firmware training board make sure you select:
* Tools > Board > Arduino Nano
* Tools > Processor > ATmega328P (Old Bootloader). If that doesn't work, try Tools > Processor > ATmega328P.