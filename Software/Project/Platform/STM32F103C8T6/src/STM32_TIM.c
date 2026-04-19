/*
* STM32_TIM.c
*
*  Created on: Mar 10, 2026
*      Author: shanewilson2507
*/

#include "STM32_TIM.h"
#include "stm32f103xb.h"
#include <string.h>

//Global timer objects used for this board configuration
extern TIM_HandleTypeDef htim3;
extern TIM_t tim3;

static IRQn_Type TIM_GetIRQn(TIM_HandleTypeDef* htim) {
    switch((uintptr_t)htim->Instance) {
        case (uintptr_t)TIM1: return TIM1_UP_TIM10_IRQn;
        case (uintptr_t)TIM2: return TIM2_IRQn;
        case (uintptr_t)TIM3: return TIM3_IRQn;
        case (uintptr_t)TIM4: return TIM4_IRQn;
        default: return (IRQn_Type)0xFF; //invalid/unsupported
    }
}

void STM32_TIM_Start(const TIM_t* self) {
    __HAL_TIM_CLEAR_FLAG(self->tim_ctx->htim, TIM_FLAG_UPDATE);
    HAL_NVIC_EnableIRQ(TIM_GetIRQn(self->tim_ctx->htim));
    HAL_TIM_Base_Start_IT(self->tim_ctx->htim);
}

void STM32_TIM_Stop(const TIM_t* self) {
    HAL_TIM_Base_Stop_IT(self->tim_ctx->htim);
}

void STM32_TIM_Enable_Interrupt(const TIM_t* self) {
    IRQn_Type it = TIM_GetIRQn(self->tim_ctx->htim);
    HAL_NVIC_EnableIRQ(it);
}

void STM32_TIM_Disable_Interrupt(const TIM_t* self) {
    IRQn_Type it = TIM_GetIRQn(self->tim_ctx->htim);
    HAL_NVIC_DisableIRQ(it);
}

void STM32_TIM_Set_Callback(TIM_t* self, CallbackContext_t cb_ctx) {
    self->cb_ctx = cb_ctx;
}

void TIM_Init(TIM_t* self, TIM_Context_t* ctx) {
    //memset(self, 0, sizeof(*self));
    self->tim_ctx = ctx;
    self->cb_ctx.args = NULL;
    self->cb_ctx.callback = NULL;

    self->start = STM32_TIM_Start;
    self->stop = STM32_TIM_Stop;
    self->enable_interrupt = STM32_TIM_Enable_Interrupt;
    self->disable_interrupt = STM32_TIM_Disable_Interrupt;
    self->set_callback = STM32_TIM_Set_Callback;

    self->stop(self);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim == &htim3) {
        if (tim3.cb_ctx.callback != NULL) {
            void* args = tim3.cb_ctx.args;
            tim3.cb_ctx.callback(args);
        }
    }
}


