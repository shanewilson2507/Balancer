/*
 * MotorConfig.h
 *
 *  Created on: Mar 26, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_MOTORCONFIG_H_
#define MIDDLEWARE_INC_MOTORCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Platform/inc/PWM.h" //"PWM.h"

typedef struct MotorConfig {
    PWM_Context_t* pwm_ctx;
} MotorConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* MIDDLEWARE_INC_MOTORCONFIG_H_ */
