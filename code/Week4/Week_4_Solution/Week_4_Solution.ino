// Firmware Training Week 4 
// User Code Example
// Joe Spall, Varun Madabushi

#include <Wire.h>
#include <math.h>

#define MPU_ADDR 0x68

// I2C Registers
#define PWR_MGMT_1 0x6B
#define WHO_AM_I 0x75
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define ACCEL_CONFIG 0x1C

#define D1_PIN 11
#define D2_PIN 10
#define D3_PIN 9
#define D4_PIN 6
#define D5_PIN 5

#define ANG_RANGE_1 -1.0
#define ANG_RANGE_2 -0.5
#define ANG_RANGE_3 0.5
#define ANG_RANGE_4 1.0

#define SCALE_FACTOR_2G 16384.0


namespace tb
{

  // Stores the LED pins
  int pinArray[5] = {D1_PIN,D2_PIN,D3_PIN,D4_PIN,D5_PIN};

  struct Vector3D
  {
    float x_g;
    float y_g;
    float z_g;
  };

  void setBubbleIndicator(tb::Vector3D vector)
  {
    float angle = atan2f(vector.y_g, vector.z_g);
    int pinPos = -1;

    // Checks if angle of vector is in valid range
    if(angle <= ANG_RANGE_1)
    {
      pinPos = 0;
    }
    else if(angle > ANG_RANGE_1 && angle <= ANG_RANGE_2)
    {
      pinPos = 1;
    }
    else if(angle > ANG_RANGE_2 && angle <= ANG_RANGE_3)
    {
      pinPos = 2;
    }
    else if(angle > ANG_RANGE_3 && angle <= ANG_RANGE_4)
    {
      pinPos = 3;
    }
    else
    {
      pinPos = 4;            
    }
    // Loop through pin array
    for(int i = 0; i <= 4; i++)
    {
      if(i == pinPos)
      {
        digitalWrite(pinArray[i], HIGH);
      }
      else
      {
        digitalWrite(pinArray[i], LOW);
      }   
    }   
  }
}

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
    
  // Set direction of all of the LED pins
  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);
  pinMode(D4_PIN, OUTPUT);
  pinMode(D5_PIN, OUTPUT);
  
  digitalWrite(D1_PIN, LOW);
  digitalWrite(D2_PIN, LOW);
  digitalWrite(D3_PIN, LOW);
  digitalWrite(D4_PIN, LOW);
  digitalWrite(D5_PIN, LOW);

  // USER CODE - IMPLEMENT FOR LAB
  
  // POWER ON
  // Here set Power Management Register to appropriate value
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
  
  // WHO AM I
  // Here conduct a Who Am I test, reading from appropriate register
  // The result should be the I2C address of the device (0x68 or 104)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(WHO_AM_I);
  Wire.endTransmission(true);
  Wire.requestFrom(MPU_ADDR, 1, true);
  Serial.println(Wire.read());
  
  // SET AFS_SCALE
  // Optionally, change the scale
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(ACCEL_CONFIG);
  Wire.write(0b00000000);
  Wire.endTransmission(true);
}

void loop()
{
  // SET START REGISTER
  // Send the starting register address to the IMU to set the pointer
  // We want to start with register 0x3B (ACCEL_XOUT_H)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();
  
  // READ REGISTERS
  // Request a read from 6 registers total
  // This corresponds to 2 registers (16 bits) for each axis
  Wire.requestFrom(MPU_ADDR, 6, true);
  
  // PROCESS DATA
  // Read in the data and perform bitwise operations to combine
  // Make sure to scale by the correct scale factor
  float accX = (Wire.read() << 8 | Wire.read()) / SCALE_FACTOR_2G; // X-axis value
  float accY = (Wire.read() << 8 | Wire.read()) / SCALE_FACTOR_2G; // Y-axis value
  float accZ = (Wire.read() << 8 | Wire.read()) / SCALE_FACTOR_2G; // Z-axis value
  
  // Print the measured acceleration to the serial monitor
  Serial.print("accX ");
  Serial.print(accX);
  Serial.print(" accY ");
  Serial.print(accY);
  Serial.print(" accZ ");
  Serial.println(accZ);
  
  // Construct a tb::Vector3D struct instance containing the measured accelerations
  tb::Vector3D currentSample{accX,accY,accZ};
  
  // BUBBLE INDICATOR
  // Pass the vector to the tb::setBubbleIndicator function
  tb::setBubbleIndicator(currentSample);
  
  // A delay of 100ms so we do not sample or print too fast
  delay(1000);
}
