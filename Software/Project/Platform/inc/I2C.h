/*
 * I2C.h
 *
 *  Created on: Mar 30, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_INC_I2C_H_
#define PLATFORM_INC_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct I2C I2C_t;
typedef struct I2C_Context I2C_Context_t; //implemented in implementation files

typedef enum {
    I2C_OK = 0,
    I2C_ERROR,
    I2C_BUSY,
    I2C_TIMEOUT
} I2C_Status_t;

typedef struct I2C_Request {
    uint16_t dev_addr;
    uint16_t mem_addr; 
    uint8_t* pdata;
    uint16_t size;
    uint32_t timeout;
} I2C_Mem_Request_t;

struct I2C {
    I2C_Context_t* i2c_ctx;
    I2C_Status_t (*mem_read) (const I2C_t* self, I2C_Mem_Request_t* read_req);
    I2C_Status_t (*mem_write) (const I2C_t* self, I2C_Mem_Request_t* write_req);
};

void I2C_Init(I2C_t* self, I2C_Context_t* ctx);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_INC_I2C_H_ */
