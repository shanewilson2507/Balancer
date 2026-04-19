/*
 * STM32_I2C.h
 *
 *  Created on: Mar 30, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_STM32F103C8T6_INC_STM32_I2C_H_
#define PLATFORM_STM32F103C8T6_INC_STM32_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "I2C.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

struct I2C_Context {
    I2C_HandleTypeDef* hi2c;
    uint16_t i2c_mem_addr_size;
};

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_STM32F103C8T6_INC_STM32_I2C_H_ */
