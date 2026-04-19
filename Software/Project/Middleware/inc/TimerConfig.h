/*
 * TimerConfig.h
 *
 *  Created on: Mar 23, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_TIMERCONFIG_H_
#define MIDDLEWARE_INC_TIMERCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Platform/inc/TIM.h"///"TIM.h" //"../../Platform/inc/TIM.h"

typedef struct TimerConfig {
	TIM_t* tim;
	TIM_Context_t* tim_ctx;
} TimerConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* MIDDLEWARE_INC_TIMERCONFIG_H_ */