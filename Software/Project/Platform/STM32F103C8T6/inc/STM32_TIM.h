/*
 * STM32_TIM.h
 *
 *  Created on: Mar 10, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_STM32F103C8T6_INC_STM32_TIM_H_
#define PLATFORM_STM32F103C8T6_INC_STM32_TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "TIM.h"

struct TIM_Context {
    TIM_HandleTypeDef* htim;
};

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_STM32F103C8T6_INC_STM32_TIM_H_ */
