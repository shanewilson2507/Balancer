/*
* STM32_PWM.c
*
*  Created on: Mar 26, 2026
*      Author: shanewilson2507
*/

#include "STM32_PWM.h"

void STM32_PWM_Set_Period_us(PWM_t* self, uint16_t period_us) {
    //Prescaler set to APB clock frequency/1M - so ARR increments period by 1us
    __HAL_TIM_SET_AUTORELOAD(self->pwm_ctx->htim, period_us - 1);  // ARR = period - 1, because counter counts from 0
    self->period_us = period_us;
    __HAL_TIM_SET_COUNTER(self->pwm_ctx->htim, 0); // reset the counter
}

void STM32_PWM_Set_Pulse_Width_us(PWM_t* self, uint16_t pulse_width_us) {
    if (pulse_width_us > self->period_us) pulse_width_us = self->period_us;
    __HAL_TIM_SET_COMPARE(self->pwm_ctx->htim, self->pwm_ctx->channel, pulse_width_us - 1); // CCR = pulse - 1
    self->pulse_width_us = pulse_width_us;
}

void STM32_PWM_Start(const PWM_t* self) {
    HAL_TIM_PWM_Start(self->pwm_ctx->htim, self->pwm_ctx->channel);
}

void STM32_PWM_Stop(const PWM_t* self) {
    HAL_TIM_PWM_Stop(self->pwm_ctx->htim, self->pwm_ctx->channel);
}

void PWM_Init(PWM_t* self, PWM_Context_t* ctx) {
    self->pwm_ctx = ctx;

    self->start = STM32_PWM_Start;
    self->stop = STM32_PWM_Stop;
    self->set_period_us = STM32_PWM_Set_Period_us;
    self->set_pulse_width_us = STM32_PWM_Set_Pulse_Width_us;

    self->set_period_us(self, 1000u);
    self->set_pulse_width_us(self, 0u);
    self->stop(self);
}
