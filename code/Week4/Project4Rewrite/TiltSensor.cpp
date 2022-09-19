#include "TiltSensor.h"

namespace tilt_sensor {

  BubbleIndicator::BubbleIndicator() {}

  void BubbleIndicator::initIndicator() {
    for (int i = 0; i < 5; i++) {
      pinMode(pinArr[i], OUTPUT);
      digitalWrite(pinArr[i], LOW);
    }
  }

  void BubbleIndicator::updateIndicator(AccelVector vector) {
    float angle = atan2f(vector.y, vector.z);
    int pinPos = -1;

    if (angle < THRESHOLD_1) {
      pinPos = 0;
    } else if (angle < THRESHOLD_2) {
      pinPos = 1;
    } else if (angle < THRESHOLD_3) {
      pinPos = 2;
    } else if (angle < THRESHOLD_4) {
      pinPos = 3;
    } else {
      pinPos = 4;
    }

    for (int i = 0; i < 5; i++) {
      if (i == pinPos) {
        digitalWrite(pinArr[i], HIGH);
      } else {
        digitalWrite(pinArr[i], LOW);
      }
    }
  }

  IMU::IMU() {}

  bool IMU::initIMU() {
    // Begin i2c
    Wire.begin();

    // Write PWR_MGMT_1 to the IMU
    writeByte(PWR_MGMT_1, 0);

    // Write ACCEL_CONFIG to the IMU
    writeByte(ACCEL_CONFIG, 0);

    // Check that the IMU has the right I2C addr
    char buffer[1];
    readConsecutiveBytes(WHO_AM_I, 1, buffer);

    if (buffer[0] == MPU_ADDR) {
      return true;
    } else {
      return false;
    }
    
  }

  AccelVector IMU::getMeasurement() {
    // Read data from the MCU
    char buffer[6];
    readConsecutiveBytes(ACCEL_XOUT_H, 6, buffer);

    // Format data into an AccelVector
    AccelVector vector;
    vector.x = (buffer[0] << 8 | buffer[1]);
    vector.y = (buffer[2] << 8 | buffer[3]);
    vector.z = (buffer[4] << 8 | buffer[5]);

    return vector;
  }

  void IMU::readConsecutiveBytes(char addr, int len, char *const buffer) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(addr);
    Wire.endTransmission(true);
    Wire.requestFrom(MPU_ADDR, len, true);

    for (int i = 0; i < len; i++) {
      buffer[i] = Wire.read();
    }
  }

  void IMU::writeByte(char addr, char data) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(addr);
    Wire.write(data);
    Wire.endTransmission(true);
  }
  
}
