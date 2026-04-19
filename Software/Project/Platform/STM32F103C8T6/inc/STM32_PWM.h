/*
 * STM32_PWM.h
 *
 *  Created on: Mar 26, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_STM32F103C8T6_INC_STM32_PWM_H_
#define PLATFORM_STM32F103C8T6_INC_STM32_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "PWM.h"

struct PWM_Context {
    TIM_HandleTypeDef* htim;
    uint32_t channel;
};

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_STM32F103C8T6_INC_STM32_PWM_H_ */
