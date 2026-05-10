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
	

	//10ms task divider
	if (time_ms % 10 == 0) {
		appFlags->update_imu = true;
		appFlags->send_data = true;
		appFlags->update_motor_command = true;
	}

	time_ms++;
}

uint64_t App::time_ms = 0u;

