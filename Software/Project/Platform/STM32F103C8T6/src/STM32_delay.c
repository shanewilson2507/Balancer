/*
 * STM32_delay.c
 *
 *  Created on: Mar 29, 2026
 *      Author: shanewilson2507
 */

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "delay.h"

void delay_ms(uint32_t delay) {
    HAL_Delay(delay);
}
