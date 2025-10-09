/**
 * For this Lab you will be designing (or at least completing) a driver
 * for the MPU 6050 IMU.  To decrease the scope of the project, our driver
 * will only initialize the IMU and read the gyroscope values.
 * 
 * For this lab, you will likely not need to change a lot of the code in
 * main.cpp, and most of your code will be in include/imu.hpp and src/imu.cpp.
 * 
 * In imu.hpp, I have indicated all necessary items with <TODO> so you know
 * where you will be modifying code.
 * 
 * imu.cpp is completely empty.  You will be responsible for implementing all
 * of the header methods in imu.hpp here.  Additionally, don't feel constrained
 * to the outline I created for you in imu.hpp.  You might want to add methods,
 * change method definitions, and delete methods.  Feel free, I'm just giving
 * you a basic setup but feel free to be creative.
 * 
 * In main.cpp, there will be a few methods to modify.  In general, this code
 * shouldn't be too foreign to you as it is just a shake sensor implementation
 * like in last week's labs.
 */

#include <Arduino.h>

#include "imu.hpp"

#define D1 11

// The IMU Driver
Imu imu = Imu(IMU_ADDRESS);

// The data buffer
double speed_buffer[20] = {0.0};
size_t speed_idx = 0;

// State information
uint8_t led_state = LOW;
bool high_velocity = false;
double velocity_cutoff = 20000;

void setup() {
  // Begin the serial monitor
  Serial.begin(9600);

  // Initialize the output led
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  
  // Setup the IMU
  imu = Imu(IMU_ADDRESS);
  // <TODO>: Change the low pass and full scale select filter values
  if (imu.begin(LowPassFilter::NOT_IMPLEMENTED, FullScaleSelect::NOT_IMPLEMENTED) != ImuError::NO_ERROR) {
    while (1) {
      Serial.println("Error Initializing IMU...");
      delay(500);
    }
  }
}

void loop() {
  // Read the gyro values from the IMU
  GyroReading reading = {};
  imu.read_gyro(&reading);

  double speed = sqrt(square(reading.x) + square(reading.y) + square(reading.z));
  Serial.print(speed);
  Serial.print("\n");
  speed_buffer[speed_idx] = speed;

  double average_speed = 0.0;
  for (size_t i = 0; i < 20; i++) {
    average_speed += speed_buffer[i];
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
