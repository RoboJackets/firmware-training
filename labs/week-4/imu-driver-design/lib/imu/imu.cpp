#include "imu.hpp"

Imu::Imu(uint8_t address): address_(address) {}

ImuError Imu::begin(LowPassFilter filter, FullScaleSelect scale_select) {
    this->low_pass_ = filter;
    this->scale_select_ = scale_select;

    // Read the Who-am-i register
    uint8_t whoami;
    if (!this->read_byte(WHO_AM_I_REGISTER, &whoami)) {
        return ImuError::I2C_FAILED;
    }

    // Check the WHO_AM_I value is correct
    if (whoami != WHO_AM_I) {
        return ImuError::INVALID_WHOAMI;
    }

    // Set the low pass value
    uint8_t configuration;
    if (!this->read_byte(CONFIGURATION, &configuration)) {
        return ImuError::I2C_FAILED;
    }
    configuration |= filter;
    if (!this->write_byte(CONFIGURATION, configuration)) {
        return ImuError::I2C_FAILED;
    }

    // Set the scale select value
    uint8_t gyro_config;
    if (!this->read_byte(GYROSCOPE_CONFIGURATION, &gyro_config)) {
        return ImuError::I2C_FAILED;
    }
    gyro_config |= (scale_select << 3);
    if (!this->write_byte(GYROSCOPE_CONFIGURATION, gyro_config)) {
        return ImuError::I2C_FAILED;
    }

    // Get out of sleep mode
    if (!this->exit_sleep()) {
        return ImuError::I2C_FAILED;
    }

    return ImuError::NO_ERROR;
}

ImuError Imu::read_gyro(GyroReading *reading) {
    uint8_t buffer[6] = {0};
    if (!this->read_bytes(GYRO_X_HI, 6, buffer)) {
        return ImuError::I2C_FAILED;
    }
    double readings[3] = {
        (double) (((int16_t) buffer[0] << 8) | buffer[1]),
        (double) (((int16_t) buffer[2] << 8) | buffer[3]),
        (double) (((int16_t) buffer[4] << 8) | buffer[5])
    };

    switch (this->scale_select_) {
        case FullScaleSelect::FS0:
            for (size_t i = 0; i < 3; i++) {
                readings[i] = readings[i] * 1000 / 131.0;
            }
            break;
        case FullScaleSelect::FS1:
            for (size_t i = 0; i < 3; i++) {
                readings[i] = readings[i] * 1000 / 65.5;
            }
            break;
        case FullScaleSelect::FS2:
            for (size_t i = 0; i < 3; i++) {
                readings[i] = readings[i] * 1000 / 32.8;
            }
            break;
        case FullScaleSelect::FS3:
            for (size_t i = 0; i < 3; i++) {
                readings[i] = readings[i] * 1000 / 16.4;
            }
            break;
        default:
            break;
    }
    reading->x = readings[0];
    reading->y = readings[1];
    reading->z = readings[2];

    return ImuError::NO_ERROR;
}

bool Imu::exit_sleep() {
    return this->write_bit(PWR_MGMT_1, 6, 0);
}

bool Imu::read_byte(uint8_t address, uint8_t *data) {
    return this->read_bytes(address, 1, data);
}

bool Imu::read_bytes(uint8_t address, uint8_t length, uint8_t *data) {
    Wire.beginTransmission(this->address_);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(this->address_, length);
    for (size_t i = 0; i < length; i++) {
        data[i] = Wire.read();
    }
    return true;
}

bool Imu::write_byte(uint8_t address, uint8_t data) {
    return this->write_bytes(address, 1, &data);
}

bool Imu::write_bytes(uint8_t address, uint8_t length, uint8_t *data) {
    Wire.beginTransmission(this->address_);
    Wire.write(address);
    for (size_t i = 0; i < length; i++) {
        Wire.write(data[i]);
    }
    Wire.endTransmission();
    return true;
}

bool Imu::write_bit(uint8_t address, uint8_t bit, uint8_t data) {
    uint8_t b;
    if (!this->read_byte(address, &b)) {
        return false;
    }

    b = (data != 0) ? (b | (1 << bit)) : (b & ~(1 << bit));
    return this->write_byte(address, b);
}
