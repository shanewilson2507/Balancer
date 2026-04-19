/*
 * MPU6050_Driver.c
 *
 *  Created on: Dec 25, 2025
 *      Author: shanewilson2507
 */

#include "MPU6050_Driver.h"

//TODO: Add DMA

// Helper macro to combine high and low bytes into int16_t
#define COMBINE_BYTES(high, low) ((int16_t)(((uint16_t)(high) << 8) | (low)))

static inline uint8_t clamp_u8(uint8_t val, uint8_t min, uint8_t max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

/* Lookup table for accelerometer scale (LSB per g) */
static const float ACCEL_LSB_PER_G_LUT[4] = {
	16384.0f,
	8192.0f,
	4096.0f,
	2048.0f
};

/* Lookup table for gyroscope scale (LSB per °/s) */
static const float GYRO_LSB_PER_DPS_LUT[4] = {
	131.0f,
	65.5f,
	32.8f,
	16.4f
};

static void MPU6050_mem_read_bytes(MPU6050_t* self, uint16_t mem_addr, uint8_t* pdata, uint16_t size) {
    I2C_Mem_Request_t req = {
        .dev_addr = self->dev_addr,
        .mem_addr = mem_addr,
        .pdata = pdata,
        .size = size,
        .timeout = self->timeout
    };
    
    self->i2c->mem_read(self->i2c, &req);
}

static void MPU6050_mem_write_bytes(const MPU6050_t* self, uint16_t mem_addr, uint8_t* pdata, uint16_t size) {
    I2C_Mem_Request_t req = {
        .dev_addr = self->dev_addr,
        .mem_addr = mem_addr,
        .pdata = pdata,
        .size = size,
        .timeout = self->timeout
    };
    
    self->i2c->mem_write(self->i2c, &req);	
}

static void MPU6050_mem_write_bits(const MPU6050_t* self, uint8_t reg_addr, uint8_t msb_start, uint8_t length, uint8_t data) {
	if (length == 0 || length > 8 || msb_start > 7) return; // invalid input
	if (data >= (1U << length)) return; // or assert

    uint8_t tmp; // temp for current value in byte

    I2C_Mem_Request_t read_req = {
        .dev_addr = self->dev_addr,
        .mem_addr = reg_addr,
        .pdata = &tmp,
        .size = 1,
        .timeout = self->timeout
    };

    self->i2c->mem_read(self->i2c, &read_req);

    uint8_t mask = (uint8_t)(((uint16_t)1U << length) - 1) << (msb_start + 1 - length);
    tmp &= ~mask; // clear bits
    tmp |= ((uint16_t)data << (msb_start + 1 - length)) & mask; // set new bits safely

    I2C_Mem_Request_t write_req = {
        .dev_addr = self->dev_addr,
        .mem_addr = reg_addr,
        .pdata = &tmp,
        .size = 1,
        .timeout = self->timeout
    };

    self->i2c->mem_write(self->i2c, &write_req);
}

static void MPU6050_Update_Data(MPU6050_t* self) {
    uint8_t buff[14];

    MPU6050_mem_read_bytes(self, MPU6050_ACCEL_XOUT_H_REG, buff, 14);

    self->raw_data.accel_x = COMBINE_BYTES(buff[0], buff[1]);
    self->raw_data.accel_y = COMBINE_BYTES(buff[2], buff[3]);
    self->raw_data.accel_z = COMBINE_BYTES(buff[4], buff[5]);

    // skip buff[6] and buff[7] (temperature)

    self->raw_data.gyro_x  = COMBINE_BYTES(buff[8],  buff[9]);
    self->raw_data.gyro_y  = COMBINE_BYTES(buff[10], buff[11]);
    self->raw_data.gyro_z  = COMBINE_BYTES(buff[12], buff[13]);
}

static void MPU6050_WakeUp(const MPU6050_t* self) {
    // --- Wake up device and select clock ---
    uint8_t pwr_val = MPU6050_CLKSEL_PLL_XGYRO; // SLEEP=0 + CLKSEL=PLL_XGYRO
    MPU6050_mem_write_bytes(self, MPU6050_PWR1_REG, &pwr_val, 1);
}

void MPU6050_Init(MPU6050_t* self, MPU6050_Config_t* cfg) {
    self->dev_addr = cfg->dev_addr;
    self->i2c = cfg->i2c;
    self->timeout = cfg->timeout;

    MPU6050_WakeUp(self);

	cfg->afs_sel = clamp_u8(cfg->afs_sel, MPU6050_AFS_SEL_2G, MPU6050_AFS_SEL_16G);
	cfg->fs_sel = clamp_u8(cfg->fs_sel, MPU6050_FS_SEL_250DPS, MPU6050_FS_SEL_2000DPS);

	self->scale.accel_lsb_per_g = ACCEL_LSB_PER_G_LUT[cfg->afs_sel];
	self->scale.gyro_lsb_per_dps = GYRO_LSB_PER_DPS_LUT[cfg->fs_sel];

	self->update_data = MPU6050_Update_Data;

	MPU6050_mem_write_bits(self,
        MPU6050_ACCEL_CONFIG_REG,
        MPU6050_ACCEL_CONFIG_AFS_SEL_BIT,
        MPU6050_ACCEL_CONFIG_AFS_SEL_LENGTH,
        cfg->afs_sel
    ); // accelerometer configuration

	MPU6050_mem_write_bits(self,
        MPU6050_GYRO_CONFIG_REG,
        MPU6050_GYRO_CONFIG_FS_SEL_BIT,
        MPU6050_GYRO_CONFIG_FS_SEL_LENGTH,
	    cfg->fs_sel
    ); // gyroscope configuration
}









