/*
 * Callback.h
 *
 *  Created on: Mar 26, 2026
 *      Author: shanewilson2507
*/

#ifndef COMMON_INC_CALLBACK_H_
#define COMMON_INC_CALLBACK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Callback_t) (void* args); // Callback function type

typedef struct {
    Callback_t callback;
    void* args;
} CallbackContext_t; // Callback context

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_INC_TIM_H_ */

