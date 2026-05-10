/*
 * LEDConfig.h
 *
 *  Created on: Mar 3, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_LEDCONFIG_H_
#define MIDDLEWARE_INC_LEDCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "GPIO.h" //"GPIO.h" //"../../../../Platform/inc/GPIO.h"

typedef struct LED_Config {
	GPIO_Context_t* gpio_ctx;
} LED_Config_t;

#ifdef __cplusplus
}
#endif

#endif /* MIDDLEWARE_INC_LEDCONFIG_H_ */
