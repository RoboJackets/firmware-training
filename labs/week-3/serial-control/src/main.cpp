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

void setup() {

}

void loop() {

}
