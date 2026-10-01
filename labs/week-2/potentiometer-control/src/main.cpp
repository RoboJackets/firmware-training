/**
 * For this lab, we're going to be reading from the potentiometer and outputting the
 * registered analog voltage to the led so that the led is mirroring the current
 * state of the potentiometer.  For this example, make sure that the signal pin
 * of the potentiometer is connected to pin A5 (SCL of the IMU).
 * 
 * Hint: Remember analogRead and analogWrite
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>

#define SIG A5
#define LED 11

void setup() {
  pinMode(SIG, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  uint32_t value = analogRead(SIG);
  analogWrite(LED, value / 4);
}
