/**
 * Blink - RoboJackets Firmware Training Week 1
 * 
 * As an introduction to firmware, we're going to be blinking the onboard LED on
 * the Arduino Nano board.  The onboard LED is attached to pin 13.
 * 
 * As a first task, try blinking the led at 500 millisecond intervals.
 * 
 * Once you can blink the led every 500 milliseconds, is there a way that we can
 * store the delay in a variable so we can change the delay between blinking the led
 * without modifying each delay call?
 * 
 * Challenge: For an extra challenge, the schematics for the training board are located
 * within the board directory of this repo. On the training board there are 5 leds that
 * you can also control.  Try making these leds blink in a pattern of your choice.
 * Personally, I like making them blink one after another, but the choice is up to you.
 * 
 * Hint: Take a look at Arduino's documentation (https://docs.arduino.cc/language-reference/).
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>

#define PINS 5
uint8_t pins[PINS] = {11, 10, 9, 6, 5};

void setup() {
    for (int i = 0; i < PINS; i++) {
        pinMode(pins[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < PINS; i++) {
        digitalWrite(pins[i], HIGH);
        delay(500);
        digitalWrite(pins[i], LOW);
        delay(500);
    }
}
