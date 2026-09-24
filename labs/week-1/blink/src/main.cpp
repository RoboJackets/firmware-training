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

#define LED_PIN 13

uint8_t external_leds[] = {11, 10, 9, 3, 2};
size_t counter = 0;

void setup() {
    // Set pinMode of the onboard led so it can be used as an output
    pinMode(LED_PIN, OUTPUT);

    // Set the pinMode of each of the external leds so they can
    // be used as outputs
    for (size_t i = 0; i < 5; i++) {
        pinMode(external_leds[i], OUTPUT);
    }
}

void loop() {
    // Turn on the onboard led
    digitalWrite(LED_PIN, HIGH);
    // Turn on one of the external leds
    digitalWrite(external_leds[counter], HIGH);

    // Wait 500 milliseconds
    delay(500);

    // Turn off the onboard led
    digitalWrite(LED_PIN, LOW);
    // Turn off one of the external leds
    digitalWrite(external_leds[counter], LOW);

    // Wait 500 milliseconds
    delay(500);

    // Increment the counter
    counter = (counter + 1) % 5;
}
