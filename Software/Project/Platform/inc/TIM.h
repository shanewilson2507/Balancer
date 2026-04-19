/*
 * TIM.h
 *
 *  Created on: Mar 10, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_INC_TIM_H_
#define PLATFORM_INC_TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Common/inc/Callback.h" //"Callback.h"

typedef struct TIM TIM_t;
typedef struct TIM_Context TIM_Context_t; //in implementation files

struct TIM {
    TIM_Context_t* tim_ctx;
    CallbackContext_t cb_ctx;
    void (*start) (const TIM_t* self);
    void (*stop) (const TIM_t* self); 
    void (*enable_interrupt) (const TIM_t* self);
    void (*disable_interrupt) (const TIM_t* self);
    void (*set_callback) (TIM_t* self, CallbackContext_t cb_ctx);
};

void TIM_Init(TIM_t* self, TIM_Context_t* ctx);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_INC_TIM_H_ */
