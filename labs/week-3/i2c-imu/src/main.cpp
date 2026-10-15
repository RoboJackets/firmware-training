/**
 * I2C-IMU: Reading the acceleration from the IMU using I2C
 * 
 * I2C allows us to talk to a wide range of sensors.  One such sensor is the MPU 6050
 * IMU (connected to the development board).  In this demo, you will read the IMU's
 * gyroscopic rotation values to determine how fast the IMU is being shaken at.
 * Instead of making you do this from scratch, I've added the Adafruit_MPU6050 library
 * which wraps the I2C peripheral of the device making it way easier to interface
 * with the IMU (Driver design is going to be the subject of next week's lecture).
 * 
 * Using either the accelerometer or the gyrometer, find a way to toggle D1 on and off
 * when the IMU is shaken.
 * 
 * Hint: The GitHub repo for the IMU can be found here:
 *  https://github.com/adafruit/Adafruit_MPU6050
 * 
 * Hint: If you are having trouble only detecting a single shake, try looking at using
 *  a moving average (https://en.wikipedia.org/wiki/Moving_average).  Think about what
 *  this is doing
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>

#define D1 11

Adafruit_MPU6050 mpu;

uint8_t led_state = LOW;

bool high_velocity = false;
double velocity_cutoff = 0.2;

size_t speeds_idx = 0;
double speeds[20] = {0.0};

void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  if (!mpu.begin()) {
    while (1) {
      Serial.println("Failed to find MPU6050 Chip");
      delay(1000);
    }
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  double speed = sqrt(square(g.gyro.x) + square(g.gyro.y) + square(g.gyro.z));
  speeds[speeds_idx] = speed;

  double average_speed = 0.0;
  for (size_t i = 0; i < 20; i++) {
    average_speed += speeds[i];
  }
  average_speed /= 20;

  if (high_velocity && average_speed < velocity_cutoff) {
    high_velocity = false;
    if (led_state == LOW) {
      digitalWrite(D1, HIGH);
      led_state = HIGH;
    } else {
      digitalWrite(D1, LOW);
      led_state = LOW;
    }
  } else if (!high_velocity && average_speed > velocity_cutoff) {
    high_velocity = true;
  }

  delay(100);
}
