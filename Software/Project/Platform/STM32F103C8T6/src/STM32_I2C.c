/*
 * STM32_I2C.c
 *
 *  Created on: Mar 30, 2026
 *      Author: shanewilson2507
 */

#include "STM32_I2C.h"

static I2C_Status_t get_i2c_status(HAL_StatusTypeDef status) {
    switch (status) {
        case HAL_OK: return I2C_OK;
        case HAL_ERROR: return I2C_ERROR;
        case HAL_BUSY: return I2C_BUSY;
        case HAL_TIMEOUT: return I2C_TIMEOUT;
        default: return I2C_ERROR;
    }
}

I2C_Status_t STM32_I2C_Mem_Write(const I2C_t* self, I2C_Mem_Request_t* write_req) {
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(
        self->i2c_ctx->hi2c,
        write_req->dev_addr,
        write_req->mem_addr,
        self->i2c_ctx->i2c_mem_addr_size,
        write_req->pdata,
        write_req->size,
        write_req->timeout
    );
    return get_i2c_status(status);
}

I2C_Status_t STM32_I2C_Mem_Read(const I2C_t* self, I2C_Mem_Request_t* write_req) {
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
        self->i2c_ctx->hi2c,
        write_req->dev_addr,
        write_req->mem_addr,
        self->i2c_ctx->i2c_mem_addr_size,
        write_req->pdata,
        write_req->size,
        write_req->timeout
    );
    return get_i2c_status(status);
}

void I2C_Init(I2C_t* self, I2C_Context_t* ctx) {
    self->i2c_ctx = ctx;
    self->mem_read = STM32_I2C_Mem_Read;
    self->mem_write = STM32_I2C_Mem_Write;
}

