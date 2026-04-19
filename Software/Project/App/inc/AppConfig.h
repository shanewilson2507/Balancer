/*
 * AppConfig.h
 *
 *  Created on: Mar 3, 2026
 *      Author: shanewilson2507
 */

#ifndef APP_INC_APPCONFIG_H_
#define APP_INC_APPCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Middleware/inc/LEDConfig.h" //"LEDConfig.h" //"../../Middleware/inc/LEDConfig.h"
#include "../../Middleware/inc/TimerConfig.h" //"TimerConfig.h" //"../../Middleware/inc/TimerConfig.h"
#include "../../Middleware/inc/MotorConfig.h" //"MotorConfig.h" //"../../Middleware/inc/MotorConfig.h"
#include "../../Middleware/inc/IMUConfig.h" //"IMUConfig.h" //"../../Middleware/inc/IMUConfig.h"

typedef struct App_Config {
	LED_Config_t led_cfg;
	TimerConfig_t timer_cfg;
	MotorConfig_t left_motor_cfg;
	MotorConfig_t right_motor_cfg;
	IMU_Config_t imu_cfg;
} App_Config_t;

#ifdef __cplusplus
}
#endif

#endif /* APP_INC_APPCONFIG_H_ */
