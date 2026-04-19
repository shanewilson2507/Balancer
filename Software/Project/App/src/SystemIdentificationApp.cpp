#include "SystemIdentificationApp.hpp"

SystemIdentificationApp::SystemIdentificationApp(const App_Config_t& cfg)
    : App(cfg) {}

void SystemIdentificationApp::main(void) {
    rightMotor.start();
	leftMotor.start();
	led.on(); //initialization complete

	const IMU_Data& imuData = imu.dataPublic;


	char buff[100];
	snprintf(buff, sizeof(buff), "t_ms, ml_%%, mr_%%, a_x, a_y, a_z, w_x, w_y, w_z");
	transmitter.sendLine(std::string(buff));

	flagUpdateTimer.start();
	
	while(time_ms <= 5000) {
		if (flags.update_imu) {
			imu.updateData();
			flags.update_imu = false;		
		}

		if (flags.send_data && (time_ms % 10 == 0)) {

			snprintf(buff, sizeof(buff), "%u, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f",
         		(uint16_t)time_ms,
				leftMotor.getThrottlePercentage(),
				rightMotor.getThrottlePercentage(),
				imuData.a_x, imuData.a_y, imuData.a_z,
         		imuData.omega_x, imuData.omega_y, imuData.omega_z);
			transmitter.sendLine(std::string(buff));
			flags.send_data = false;
		}
	}

	led.off(); // transmission complete
}