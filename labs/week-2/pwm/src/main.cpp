/**
 * For the pwm lab, we're going to generate pwm in two different ways.
 * 
 * First, we're going to do the old-fashioned and (arguably) more
 * difficult way.  Using just digitalWrite and delayMicroseconds, generate
 * a pwm of 0.25, 0.5, 0.75, and 1.0 with a period of 1 millisecond on led
 * 1.  Space the different measurements by 1 second
 * 
 * Next, to demonstrate that your pwm frequencies are correct, use
 * analogWrite to generate the same pwm values on led 2.
 * 
 * Hint: pwm is just on-time divided by the period
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>

#define LED1 11
#define LED2 10

#define PERIOD 1000

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // 0.25 PWM
  analogWrite(LED2, 255 / 4);
  for (size_t i = 0; i < 1000; i++) {
    digitalWrite(LED1, HIGH);
    delayMicroseconds(250);
    digitalWrite(LED1, LOW);
    delayMicroseconds(750);
  }

  // 0.5 PWM
  analogWrite(LED2, 255 / 2);
  for (size_t i = 0; i < 1000; i++) {
    digitalWrite(LED1, HIGH);
    delayMicroseconds(500);
    digitalWrite(LED1, LOW);
    delayMicroseconds(500);
  }

  // 0.75 PWM
  analogWrite(LED2, 3 * 255 / 4);
  for (size_t i = 0; i < 1000; i++) {
    digitalWrite(LED1, HIGH);
    delayMicroseconds(750);
    digitalWrite(LED1, LOW);
    delayMicroseconds(250);
  }

  // 1.0 PWM
  analogWrite(LED2, 255);
  for (size_t i = 0; i < 1000; i++) {
    digitalWrite(LED1, HIGH);
    delayMicroseconds(1000);
  }
}
