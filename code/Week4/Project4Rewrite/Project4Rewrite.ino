#include "TiltSensor.h"
#include "Wire.h"

tilt_sensor::BubbleIndicator bubbleIndicator;
tilt_sensor::IMU imu;

bool value;

void setup() {
  // Begin i2c
  Wire.begin();
  Serial.begin(9600);
  
  bubbleIndicator.initIndicator();
  imu.initIMU();
}

void loop() {
  tilt_sensor::AccelVector vector = imu.getMeasurement();
  tilt_sensor::printVector(vector);
  delay(1000);
}
