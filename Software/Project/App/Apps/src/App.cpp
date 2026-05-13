#include "App.hpp"

App::App(const App_Config_t& cfg)
	: 
	  led(cfg.led_cfg), 
	  flagUpdateTimer(cfg.timer_cfg),
	  leftMotor(cfg.left_motor_cfg),
	  rightMotor(cfg.right_motor_cfg),
	  imu(cfg.imu_cfg)
{
	CallbackContext_t callbackContext = {
		.callback = flagUpdateCallback,
		.args = &flags
	};
	flagUpdateTimer.setCallback(callbackContext);
};

void App::flagUpdateCallback(void* flags) {
	AppFlags* appFlags = (AppFlags*) flags;
	
	if (time_ms % 1 == 0) appFlags->flag_1kHz = true;
	if (time_ms % 2 == 0) appFlags->flag_500Hz = true;
	if (time_ms  % 10 == 0) appFlags->flag_100Hz = true;
	if (time_ms % 100 == 0) appFlags->flag_10Hz = true;
	if (time_ms % 1000 == 0) appFlags->flag_1Hz = true;

	time_ms++;
}

uint64_t App::time_ms = 0u;

