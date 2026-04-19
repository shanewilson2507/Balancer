/*
 * IMU.cpp
 *
 *  Created on: Apr 1, 2026
 *      Author: shanewilson2507
 */

#include "IMU.hpp"
#include "../../Peripherals/MPU6050/inc/MPU6050.h" // "MPU6050.h" // "../../Peripherals/MPU6050/inc/MPU6050.h"
#include "../../Common/inc/Constants.h" // "Constants.h" // "../../Common/inc/Constants.h"

 IMU::IMU(const IMU_Config_t& imu_cfg) 
    : dataPublic(data)
 {
    I2C_Init(&i2c, imu_cfg.i2c_ctx);

    MPU6050_Config_t mpu6050_cfg = {
        .timeout = 10, // ms
        .dev_addr = MPU6050_ADDRESS,
        .i2c = &i2c,
        .fs_sel = MPU6050_FS_SEL_250DPS,
        .afs_sel = MPU6050_AFS_SEL_2G
    };

    MPU6050_Init(&mpu, &mpu6050_cfg);

    accel_scale = G / (float) mpu.scale.accel_lsb_per_g;

    gyro_scale = DEG_TO_RAD / (float) mpu.scale.gyro_lsb_per_dps;

    updateData();
 }

 void IMU::updateData() {
    mpu.update_data(&mpu);
    data.a_x = ((float) mpu.raw_data.accel_x) * accel_scale;
    data.a_y = ((float) mpu.raw_data.accel_y) * accel_scale;
    data.a_z = ((float) mpu.raw_data.accel_z) * accel_scale;
    
    data.omega_x = ((float) mpu.raw_data.gyro_x) * gyro_scale;
    data.omega_y = ((float) mpu.raw_data.gyro_y) * gyro_scale;
    data.omega_z = ((float) mpu.raw_data.gyro_z) * gyro_scale;
}
