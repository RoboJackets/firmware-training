#include "TiltSensor.h"

void setup() {
  Serial.begin(9600);

  tilt_sensor::BubbleIndicator bubbleIndicator;
  tilt_sensor::IMU imu;
  
  bubbleIndicator.initIndicator();
  imu.initIMU();
}

void loop() {
  tilt_sensor::AccelVector vector = imu.getMeasurement();
  bubbleIndicator.updateIndicator(vector);
  delay(100);
}
