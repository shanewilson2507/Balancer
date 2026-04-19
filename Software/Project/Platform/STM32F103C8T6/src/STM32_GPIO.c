/*
 * STM32_GPIO.c
 *
 *  Created on: Feb 12, 2026
 *      Author: shanewilson2507
 */

#include "STM32_GPIO.h"
#include <string.h>

void STM32_GPIO_Write(const GPIO_t* self, GPIOLevel_t level) {
	HAL_GPIO_WritePin(
		self->gpio_ctx->gpio_port,
		self->gpio_ctx->pin,
		(level == GPIO_LEVEL_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET
	);
}

GPIOLevel_t STM32_GPIO_Read(const GPIO_t* self) {
	return (HAL_GPIO_ReadPin(
			self->gpio_ctx->gpio_port,
			self->gpio_ctx->pin
		) == GPIO_PIN_RESET) ? GPIO_LEVEL_LOW : GPIO_LEVEL_HIGH;
}

void GPIO_Init(GPIO_t* self, GPIO_Context_t* ctx) {
	memset(self, 0, sizeof(*self));
	self->gpio_ctx = ctx;
	self->write = STM32_GPIO_Write;
	self->read = STM32_GPIO_Read;
}




