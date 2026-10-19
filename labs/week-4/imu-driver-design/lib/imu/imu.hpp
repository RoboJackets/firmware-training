/**
 * MPU 6050 Driver written for the Arduino runtime
 * 
 * Register Map: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 * Datasheet: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 * 
 * Note: Most of the private methods are there as a guide.  When I was implementing this lab I
 * used all of the helper methods there to make it clear what I was doing.  You don't need to
 * implement them or use them, they're just there as a bit of a guide.
 */

#ifndef IMU_HPP
#define IMU_HPP

#include <Arduino.h>
#include <Wire.h>

// What is the address for the IMU connected to your Arduino (check the datasheet)
// <TODO>
#define IMU_ADDRESS 0b1101000

// The configuration register
// <TODO>
#define CONFIGURATION 0x1A
// The gyroscope configuration register
// <TODO>
#define GYROSCOPE_CONFIGURATION 0x1B
// The gyroscope X High Byte Register
// <TODO>
#define GYRO_X_HI 0x43
// The gyroscope Low Byte Register
// <TODO>
#define GYRO_X_LO 0x44
// The gyroscope Y High Byte Register
// <TODO>
#define GYRO_Y_HI 0x45
// The gyroscope Y Low Byte Register
// <TODO>
#define GYRO_Y_LO 0x46
// The gyroscope Z High Byte Register
// <TODO>
#define GYRO_Z_HI 0x47
// The gyroscope Z Low Byte Register
// <TODO>
#define GYRO_Z_LO 0x48
// The first power management register
// <TODO>
#define PWR_MGMT_1 0x6B

// The register the who-am-i information is kept in
// <TODO>
#define WHO_AM_I_REGISTER 0x75
// The value in the WHO_AM_I register (always use this to make sure you are talking to
// the correct device)
// <TODO>
#define WHO_AM_I 0x68

// Error from operating the IMU.
// 
// Feel free to add your own errors here
enum ImuError {
    // No error occurred
    NO_ERROR = 0,
    // The whoami value returned from the IMU was incorrect
    INVALID_WHOAMI = 1,
    // I2C Communication Failed (likely something is unplugged)
    I2C_FAILED = 2,
};

// The various digial low-pass filter options for initializing the IMU (check page 13 of the register map)
// <TODO>
enum LowPassFilter {
    // 256 Hz at 0.98 ms
    CFG0 = 0,
    // 188 Hz at 1.9 ms
    CFG1 = 1,
    // 98 Hz at 2.8 ms
    CFG2 = 2,
    // 42 Hz at 4.8 ms
    CFG3 = 3,
    // 20 Hz at 8.3 ms
    CFG4 = 4,
    // 10 Hz at 13.4 ms
    CFG5 = 5,
    // 5 Hz at 18.6 ms
    CFG6 = 6,
};

// The full sacle options for the gyroscope outputs (check page 14 of the register map document)
// <TODO>
enum FullScaleSelect {
    // +- 250 degrees / second
    FS0,
    // +- 500 degrees / second
    FS1,
    // +- 1000 degrees / second
    FS2,
    // +- 2000 degrees / second
    FS3,
};

// A struct containing the gyrometer data coming from the Imu
struct GyroReading {
    // The gyrometer reading in the x-direction (in millidegrees (i.e. 1000 counts / 1 degree))
    double x;
    // The gyrometer reading in the y-direction (in millidegrees (i.e. 1000 counts / 1 degree))
    double y;
    // The gyrometer reading in the z-direction (in millidegrees (i.e. 1000 counts / 1 degree))
    double z;
};

class Imu {
public:
    /**
     * @brief Create a new instance of the IMU driver.
     * 
     * Do not initialize the driver in this method, that should be completed in begin
     * 
     * @param address the address of the IMU
     */
    Imu(uint8_t address);

    /**
     * @brief Actually initialize the IMU driver setting the desired low pass filter and scale select
     * 
     * This will also need to clear the sleep bit of the power register (see Power Management 1)
     * 
     * @param filter the low pass filter value to use with the imu
     * @param scale_select the scale select value to use with the imu
     * @returns The possible error from attempting to initialize the imu
     */
    ImuError begin(LowPassFilter filter, FullScaleSelect scale_select);

    /**
     * @brief Read the gyrometer measurements of the imu
     * 
     * @param reading The struct to store measurements in
     */
    ImuError read_gyro(GyroReading *reading);
private:
    /**
     * @brief Exit sleep mode for the IMU 
     *
     * @return True if the operation was successful
     */
    bool exit_sleep();
    /**
     * @brief Read from a given address
     * 
     * @param address The address to read from
     * @param data The output data 
     * @return True if the operation was successful
     */
    bool read_byte(uint8_t address, uint8_t *data);

    /**
     * @brief Read a number of bytes starting from an address
     * 
     * @param address The start address
     * @param length The number of bytes to read
     * @param data The buffer to store the output into
     * @return True if the operation was successful
     */
    bool read_bytes(uint8_t address, uint8_t length, uint8_t *data);

    /**
     * @brief write a byte to a given address 
     * 
     * @param address The address on the IMU to write to
     * @param data The data to write to the address
     * @return True if the operation was successful
     */
    bool write_byte(uint8_t address, uint8_t data);

    /**
     * @brief Write a number of bytes starting at a given address
     * 
     * @param address The address on the IMU to start writing to
     * @param length The number of bytes to write
     * @param data The data to write to the IMU
     * @return True if the operation was successful
     */
    bool write_bytes(uint8_t address, uint8_t length, uint8_t *data);

    /**
     * @brief Write to a given bit of an address provided
     * 
     * @param address The address to write to
     * @param bit The bit number to write to
     * @param data The data to write into the bit
     * @return True if the operation was successful
     */
    bool write_bit(uint8_t address, uint8_t bit, uint8_t data);

    // The I2C address of the IMU
    uint8_t address_;
    // The Low Pass Filter Applied to the IMU
    LowPassFilter low_pass_;
    // The scale select applied to the IMU
    FullScaleSelect scale_select_;
};

#endif
