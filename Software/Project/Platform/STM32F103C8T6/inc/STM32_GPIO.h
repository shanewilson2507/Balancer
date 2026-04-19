/*
 * STM32_GPIO.h
 *
 *  Created on: Feb 12, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_STM32F103C8T6_INC_STM32_GPIO_H_
#define PLATFORM_STM32F103C8T6_INC_STM32_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "GPIO.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>

struct GPIO_Context {
	GPIO_TypeDef* gpio_port;
	uint16_t pin;
};

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_STM32F103C8T6_INC_STM32_GPIO_H_ */
