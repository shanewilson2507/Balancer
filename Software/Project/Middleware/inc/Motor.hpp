/*
 * Motor.hpp
 *
 *  Created on: Mar 26, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_MOTOR_HPP_
#define MIDDLEWARE_INC_MOTOR_HPP_

#include "MotorConfig.h"
#include "../../Platform/inc/PWM.h" // "PWM.h"

class Motor {
    PWM_t pwm;
    uint16_t throttle; //as a permille (per thousand ie./ 1-1000)
public:
    Motor(const MotorConfig_t& cfg);
    void start();
    void stop();
    void setThrottle(uint16_t throttle);
    void setThrottlePercentage(float throttlePercentage);
    uint16_t getThrottle();
    float getThrottlePercentage();
    //void calibrate();
private:
    void _init(); //motor initialization sequence
};

#endif /* MIDDLEWARE_INC_MOTOR_HPP_ */
