/*
 * MPU6050.h
 *
 *  Created on: Mar 30, 2025
 *      Author: shanewilson2507
 */

#ifndef PERIPHERALS_MPU6050_INC_MPU6050_H_
#define PERIPHERALS_MPU6050_INC_MPU6050_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MPU6050_ADDRESS 0x68 << 1 //When AD0 is low. Shifted as it's the 6-bit address - bit 0 is reserved
#define MPU6050_WHO_AM_I_REG


//Gyro config
#define MPU6050_GYRO_CONFIG_REG 0x1B
#define MPU6050_GYRO_CONFIG_FS_SEL_BIT 4
#define MPU6050_GYRO_CONFIG_FS_SEL_LENGTH 2

typedef enum {
	MPU6050_FS_SEL_250DPS  = 0u, // +/- 250 degrees/sec full scale range
	MPU6050_FS_SEL_500DPS  = 1u,
	MPU6050_FS_SEL_1000DPS = 2u,
	MPU6050_FS_SEL_2000DPS = 3u
} MPU6050_Gyro_FS_t; //Full scale range enumeration based on FS_SEL


//Accelerometer config
#define MPU6050_ACCEL_CONFIG_REG 0x1C
#define MPU6050_ACCEL_CONFIG_AFS_SEL_BIT 4
#define MPU6050_ACCEL_CONFIG_AFS_SEL_LENGTH 2

typedef enum {
    MPU6050_AFS_SEL_2G  = 0u, // +/- 2G full scale range
    MPU6050_AFS_SEL_4G  = 1u,
    MPU6050_AFS_SEL_8G  = 2u,
    MPU6050_AFS_SEL_16G = 3u
} MPU6050_Accel_AFS_t; //Full scale range enumeration based on AFS_SEL


// Sensor data registers
#define MPU6050_SENSOR_DATA_SIZE 14

#define MPU6050_ACCEL_XOUT_H_REG 0x3B
#define MPU6050_ACCEL_XOUT_L_REG 0x3C
#define MPU6050_ACCEL_YOUT_H_REG 0x3D
#define MPU6050_ACCEL_YOUT_L_REG 0x3E
#define MPU6050_ACCEL_ZOUT_H_REG 0x3F
#define MPU6050_ACCEL_ZOUT_L_REG 0x40

#define MPU6050_GYRO_XOUT_H_REG 0x43
#define MPU6050_GYRO_XOUT_L_REG 0x44
#define MPU6050_GYRO_YOUT_H_REG 0x45
#define MPU6050_GYRO_YOUT_L_REG 0x46
#define MPU6050_GYRO_ZOUT_H_REG 0x47
#define MPU6050_GYRO_ZOUT_L_REG 0x48

/* PWR_MGMT_1 register bits */
#define MPU6050_PWR1_REG        0x6B
#define MPU6050_PWR1_DEVICE_RESET   (1 << 7)
#define MPU6050_PWR1_SLEEP          (1 << 6)
#define MPU6050_PWR1_CYCLE          (1 << 5)
#define MPU6050_PWR1_TEMP_DIS       (1 << 3)
#define MPU6050_PWR1_CLKSEL_MASK    0x07
#define MPU6050_CLKSEL_INTERNAL     0
#define MPU6050_CLKSEL_PLL_XGYRO    1
#define MPU6050_CLKSEL_PLL_YGYRO    2
#define MPU6050_CLKSEL_PLL_ZGYRO    3
#define MPU6050_CLKSEL_PLL_EXT32K   4
#define MPU6050_CLKSEL_PLL_EXT19M   5

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERALS_MPU6050_INC_MPU6050_H_ */
