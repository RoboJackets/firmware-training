#ifndef TILT_SENSOR
#define TILT_SENSOR

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

namespace tilt_sensor {

  struct AccelVector {
    float x;
    float y;
    float z;
  };

  class BubbleIndicator {
  public:
    BubbleIndicator();    
    void initIndicator();
    void updateIndicator(AccelVector vector);
  private:
    // Pin values for the 5 LEDs
    const int D1_PIN = 11;
    const int D2_PIN = 10;
    const int D3_PIN = 9;
    const int D4_PIN = 6;
    const int D5_PIN = 5;

    // Array of output pins
    const int pinArr[5] = {D1_PIN, D2_PIN, D3_PIN, D4_PIN, D5_PIN};

    // Threshold Values used to determine how many lights to turn on
    const float THRESHOLD_1 = -0.95 * M_PI;
    const float THRESHOLD_2 = -0.45 * M_PI;
    const float THRESHOLD_3 = 0.45 * M_PI;
    const float THRESHOLD_4 = 0.95 * M_PI;
  };

  class IMU {
  public:
    IMU();
    bool initIMU();
    AccelVector getMeasurement();
  private:
    const char MPU_ADDR = 0x68;
    const char PWR_MGMT_1 = 0x6B;
    const char WHO_AM_I = 0x75;
    const char ACCEL_XOUT_H = 0x3B;
    const char ACCEL_XOUT_L = 0x3C;
    const char ACCEL_YOUT_H = 0x3D;
    const char ACCEL_YOUT_L = 0x3E;
    const char ACCEL_ZOUT_H = 0x3F;
    const char ACCEL_ZOUT_L = 0x40;
    const char ACCEL_CONFIG = 0x1C;
  
    void readConsecutiveBytes(char addr, int len, char *const buffer);
    void writeByte(char addr, char data);
  };

}


#endif
