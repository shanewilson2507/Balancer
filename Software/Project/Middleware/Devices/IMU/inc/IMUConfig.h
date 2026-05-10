/*
 * IMUConfig.h
 *
 *  Created on: Apr 1, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_IMUCONFIG_H_
#define MIDDLEWARE_INC_IMUCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "I2C.h" //"I2C.h" //"../../../../Platform/inc/I2C.h"

typedef struct IMU_Config {
    I2C_Context_t* i2c_ctx;
} IMU_Config_t;

#ifdef __cplusplus
}
#endif

#endif /* MIDDLEWARE_INC_IMUCONFIG_H_ */
