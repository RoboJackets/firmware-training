#include "TiltSensor.h"

namespace tilt_sensor {

  void printVector(AccelVector vector) {
    Serial.print("x: ");
    Serial.print(vector.x);
    Serial.print(", y: ");
    Serial.print(vector.y);
    Serial.print(", z: ");
    Serial.println(vector.z);
  }

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
    // Write PWR_MGMT_1 to the IMU
    writeByte(PWR_MGMT_1, 0);

    // Check that the IMU has the right I2C addr
    int id = getID();

    // Write ACCEL_CONFIG to the IMU
    writeByte(ACCEL_CONFIG, 0);

    return (id == MPU_ADDR);
  }

  int IMU::getID() {
    char buffer[1];
    readConsecutiveBytes(WHO_AM_I, 1, buffer);

    return buffer[0];
  }

  AccelVector IMU::getMeasurement() {
    // Read data from the MCU
    char buffer[6];
    readConsecutiveBytes(ACCEL_XOUT_H, 2, buffer);

    // Format data into an AccelVector
    AccelVector vector;
    vector.x = (buffer[0] << 8 | buffer[1]) / SCALE_FACTOR_2G;
    vector.y = (buffer[2] << 8 | buffer[3]) / SCALE_FACTOR_2G;
    vector.z = (buffer[4] << 8 | buffer[5]) / SCALE_FACTOR_2G;

    return vector;
  }

  void IMU::readConsecutiveBytes(char addr, int len, char *buffer) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(addr);
    Wire.endTransmission();
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
