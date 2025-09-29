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

void setup() {

}

void loop() {

}
