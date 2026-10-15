/**
 * Serial Control: controlling the Arduino via the Serial Monitor
 * 
 * The first serial port on the Arduino Nano is used to connect the Arduino to the computer.
 * This means that not only can it send data for the computer to display, your computer can
 * send data to the arduino to control the Arduino's capabilities.
 * 
 * In this lab, we're going to be using the serial terminal to send different commands to
 * the Arduino.  These commands can be anything, but they should be used to set the pwm for
 * each of the LEDS on the test board.
 * 
 * As an example, you could define the following command:
 *    Dn=xxx
 * Where n is the number of the led and x is the pwm value to send to the led (i.e. from 000-255).
 * 
 * Then sending the command `D1=255` should turn on D1 with maximum brightness.
 * 
 * Hint: The documentation for the Arduino Serial Interface can be found here:
 *  https://docs.arduino.cc/language-reference/en/functions/communication/serial/
 * 
 * Hint: All data transmitted over the serial peripheral is in ASCII format.  You can
 *  use an ascii table () to decode what data is sent to the Arduino from the computer.
 * 
 * Hint: It is incredibly useful to print information to the terminal for debugging
 *  when working with an Arduino.  You can print data using Serial.print and Serial.println
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>

uint8_t led_pins[5] = { 11, 10, 9, 6, 5 };

uint8_t command[10] = {};

void setup() {
  Serial.begin(9600);
  for (size_t i = 0; i < 5; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    size_t num_bytes = Serial.readBytesUntil('\n', command, 10);
    for (size_t i = 0; i < num_bytes; i++) {
      Serial.print((char) command[i]);
    }
    Serial.print("\n");

    if (num_bytes >= 4 && command[0] == 'D') {
      uint8_t pin;
      pin = command[1] - 48;
      Serial.print("Pin: ");
      Serial.println(pin);

      if (pin > 5) {
        return;
      }

      uint8_t value;
      value = (command[3] - 48) * 100 +
        (command[4] - 48) * 10 +
        (command[5] - 48);

      Serial.print("Value: ");
      Serial.println(value);

      analogWrite(led_pins[pin - 1], value);
    }
  }
}
