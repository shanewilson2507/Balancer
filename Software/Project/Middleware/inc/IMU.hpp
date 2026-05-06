/*
 * IMU.hpp
 *
 *  Created on: Apr 1, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_IMU_HPP_
#define MIDDLEWARE_INC_IMU_HPP_

#include "IMUConfig.h"
#include "../../Peripherals/MPU6050/inc/MPU6050_Driver.h" // MPU6050_Driver.h // "../../Peripherals/MPU6050/inc/MPU6050_Driver.h"

struct IMU_Data {
    float a_x; // m/s^2
    float a_y;
    float a_z;

    float omega_x; // rad/s
    float omega_y;
    float omega_z;
};

struct IMU_Bias {
    float omega_bx;
    float omega_by;
    float omega_bz; 
};

class IMU {
private:
    I2C_t i2c;
    MPU6050_t mpu;
    IMU_Data data; // internal unmodifiable data
    IMU_Bias bias;

    float accel_scale; // defined to avoid extra runtime divisions
    float gyro_scale;
public:
    const IMU_Data& dataPublic; // readonly reference to internal data
public:
    IMU(const IMU_Config_t& imu_cfg);
    void calibrate();
    void updateData();
};

#endif /* MIDDLEWARE_INC_IMU_HPP_ */
