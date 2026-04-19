/*
 * MPU6050_Driver.h
 *
 *  Created on: Mar 30, 2025
 *      Author: shanewilson2507
 */

#ifndef PERIPHERALS_MPU6050_INC_MPU6050_DRIVER_H_
#define PERIPHERALS_MPU6050_INC_MPU6050_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../../../Platform/inc/I2C.h" // "I2C.h" // "../../../Platform/inc/I2C.h"
#include "MPU6050.h"

typedef struct MPU6050 MPU6050_t;

typedef struct MPU6050_Raw_Data {
    int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;

	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
} MPU6050_Raw_Data_t;

typedef struct MPU6050_Scale {
	float accel_lsb_per_g; //LSB per g
	float gyro_lsb_per_dps; //LSB per degree per second
} MPU6050_Scale_t;

typedef struct MPU6050_Config {
    uint32_t timeout;
    uint16_t dev_addr;
    I2C_t* i2c;
    MPU6050_Gyro_FS_t fs_sel;
	MPU6050_Accel_AFS_t afs_sel;
} MPU6050_Config_t;

struct MPU6050 {
    MPU6050_Scale_t scale;
    uint32_t timeout;
    uint16_t dev_addr;
    I2C_t* i2c;

    MPU6050_Raw_Data_t raw_data;
    
    void (*update_data) (MPU6050_t* self);
};

void MPU6050_Init(MPU6050_t* self, MPU6050_Config_t* cfg);

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERALS_MPU6050_INC_MPU6050_DRIVER_H_ */
