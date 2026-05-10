/*
#include <Delay2.hpp>
 * Motor.cpp
 *
 *  Created on: Mar 26, 2026
 *      Author: shanewilson2507
 */

#include "Motor.hpp"
#include "MotorConfig.h"
#include "Delay.hpp"

Motor::Motor(const MotorConfig_t& cfg)
    : throttle(0u)
{
    PWM_Init(&pwm, cfg.pwm_ctx);
    pwm.set_period_us(&pwm, 20000u); //50Hz
    pwm.set_pulse_width_us(&pwm, 1000u); //minimum throttle pulse
}

void Motor::start() {
    pwm.start(&pwm);
    _init();
}

void Motor::stop() {
    pwm.stop(&pwm);
}

void Motor::setThrottle(uint16_t throttle) {
    if (throttle > 1000u) throttle = 1000u;
    pwm.set_pulse_width_us(&pwm, throttle + 1000u); //throttle PWM pulse between 1ms-2ms (1000us-2000us)
    this->throttle = throttle;
}

uint16_t Motor::getThrottle() {
    return throttle;
}

void Motor::setThrottlePercentage(float throttlePercentage) {
    if (throttlePercentage > 100.0f) {
        throttlePercentage = 100.0f;
    } else if (throttlePercentage < 0.0f) {
        throttlePercentage = 0.0f;
    }
    uint16_t throttle = static_cast<uint16_t>(throttlePercentage * 10.0f + 0.5f); //+0.5f to ensure rounding - not truncation
    setThrottle(throttle);
}

float Motor::getThrottlePercentage() {
    return static_cast<float>(throttle) / 10.0f;
}

void Motor::_init() {
    uint16_t requestedThrottle = getThrottle();
    setThrottle(0u);
    Delay::ms(5000);
    setThrottle(requestedThrottle);
}

/* Calibration sequence
void Motor::calibrate() {
    pwm.set_pulse_width_us(&pwm, 2000u);
    pwm.start(&pwm);
    Delay::ms(5000u);
    pwm.set_pulse_width_us(&pwm, 1000u);
}
*/
