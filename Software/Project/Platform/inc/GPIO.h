/*
 * GPIO.h
 *
 *  Created on: Feb 12, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_INC_GPIO_H_
#define PLATFORM_INC_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPIO GPIO_t;
typedef struct GPIO_Context GPIO_Context_t; //implemented in implementation files

typedef enum GPIOLevel {
	GPIO_LEVEL_LOW = 0u,
	GPIO_LEVEL_HIGH
} GPIOLevel_t;

struct GPIO {
	GPIO_Context_t* gpio_ctx;
	void (*write) (const GPIO_t* self, GPIOLevel_t level);
	GPIOLevel_t (*read) (const GPIO_t* self);
};

void GPIO_Init(GPIO_t* self, GPIO_Context_t* ctx);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_INC_GPIO_H_ */
