/*
 * PWM.h
 *
 *  Created on: Mar 26, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_INC_PWM_H_
#define PLATFORM_INC_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct PWM PWM_t;
typedef struct PWM_Context PWM_Context_t; //in implementation files

struct PWM {
    PWM_Context_t* pwm_ctx;
    uint16_t period_us; //PWM period in microseconds
    uint16_t pulse_width_us; //high pulse width in microseconds
    void (*set_period_us) (PWM_t* self, uint16_t period_us);
    void (*set_pulse_width_us) (PWM_t* self, uint16_t period_us);
    void (*start) (const PWM_t* self);
    void (*stop) (const PWM_t* self);
};

void PWM_Init(PWM_t* self, PWM_Context_t* ctx);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_INC_PWM_H_ */
