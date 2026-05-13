#include "TrimIdentificationApp.hpp"
#include "Delay.hpp"

static constexpr uint16_t MAX_TIME = TrimIdentificationApp::NUM_STEPS * TrimIdentificationApp::HOLD_PERIOD;

static constexpr float uL_STEP_INCREMENT =
    (TrimIdentificationApp::uL_MAX -
     TrimIdentificationApp::uL_MIN) /
    (TrimIdentificationApp::NUM_STEPS - 1);

TrimIdentificationApp::TrimIdentificationApp(const App_Config_t& cfg)
    : App(cfg) {}

float TrimIdentificationApp::trimThrottleStepFunction(uint16_t time_ms) {
    uint16_t stepIndex = time_ms / HOLD_PERIOD;

    if (stepIndex >= NUM_STEPS)
        stepIndex = NUM_STEPS - 1;

    return uL_MIN + stepIndex * uL_STEP_INCREMENT;
}

void TrimIdentificationApp::main(void) {

    rightMotor.start();
	leftMotor.start();
	imu.calibrate();
	led.on(); //initialization complete

	const IMU_Data& imuData = imu.dataPublic;


	char buff[110];
	snprintf(buff, sizeof(buff), "t (ms), uL (%%), uR (%%), f_x (ms^-2), f_y (ms^-2), f_z (ms^-2), w_x (rad/s), w_y (rad/s), w_z (rad/s)");
	transmitter.sendLine(std::string(buff));

	//letting any transients stabilize before collecting data
	leftMotor.setThrottlePercentage(TrimIdentificationApp::uL_MIN);
	rightMotor.setThrottlePercentage(TrimIdentificationApp::TRIM_SUM - TrimIdentificationApp::uL_MIN);
	delay_ms(5000);

	flagUpdateTimer.start();

	while(time_ms <= MAX_TIME) {

        if (flags.flag_100Hz) {
			flags.flag_100Hz = false;
			
			//update motor command
            float uL = trimThrottleStepFunction(time_ms);
            float uR = TrimIdentificationApp::TRIM_SUM - uL;
            leftMotor.setThrottlePercentage(uL);
            rightMotor.setThrottlePercentage(uR);

			//update imu
			imu.updateData();

			//telemetry
			snprintf(buff, sizeof(buff), "%u, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f",
         		(uint16_t)time_ms,
				leftMotor.getThrottlePercentage(),
				rightMotor.getThrottlePercentage(),
				imuData.a_x, imuData.a_y, imuData.a_z,
         		imuData.omega_x, imuData.omega_y, imuData.omega_z);

			transmitter.sendLine(std::string(buff));			
        }
	}
	
	rightMotor.setThrottlePercentage(0.0f);
	leftMotor.setThrottlePercentage(0.0f);
	led.off(); // transmission complete
}