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
	time_ms++;
	AppFlags* appFlags = (AppFlags*) flags;
	appFlags->update_imu = true;
	appFlags->send_data = true;
}

uint64_t App::time_ms = 0u;

