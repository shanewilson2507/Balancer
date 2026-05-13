#include "SystemIdentificationApp.hpp"
#include <algorithm>
#include <cmath>
#include <cinttypes>

static constexpr uint32_t MAX_TIME = 220000; //ms

PIController::PIController(float Kp, float Ki, float u_i_min, float u_i_max)
    : 
    Kp(Kp), 
    Ki(Ki), 
    error_integral(0.0f),
    u_i_min(u_i_min),
    u_i_max(u_i_max)
{}

float PIController::update(float error, float dt) {
    error_integral += error * dt;

    // compute tentative output
    float u_i = Ki * error_integral;

    // clamp output
    u_i = std::clamp(u_i, u_i_min, u_i_max);

    // reflect clamp back into state
    error_integral = u_i / Ki;

    float u_p = Kp * error;

    return u_p + u_i;
}

	

ComplementaryFilter::ComplementaryFilter(float alpha)
	: alpha(alpha)
{}

float ComplementaryFilter::estimate(const IMU_Data& data, float dt) {

    // gyro integration (assuming y-axis)
    float gyro_theta = theta + data.omega_y * dt;

    // accelerometer angle estimate (assuming w_y is small)
    float accel_theta = std::atan2(-data.a_x, data.a_z);

	if (!initialized) {
		theta = accel_theta;
		initialized = true;
		return theta;
	}

    // complementary blend
    theta = alpha * gyro_theta + (1.0f - alpha) * accel_theta;

    return theta;
}

PRBS16Generator::PRBS16Generator(uint16_t seed) 
	: lfsr(seed ? seed : 0xACE1),
	  state((lfsr & 1) ? 1.0f : -1.0f)
	  {}

void PRBS16Generator::update() {
	uint16_t feedback_bit = ((lfsr >> 15) ^
				    (lfsr >> 13) ^
				    (lfsr >> 12) ^
				    (lfsr >> 10)) &
				    1;
	lfsr = (lfsr << 1) | feedback_bit;
	
	state = (lfsr & 1) ? 1.0f : -1.0f;

}

float PRBS16Generator::getState() const {
	return state;
}

SystemIdentificationApp::SystemIdentificationApp(const App_Config_t& cfg)
    : App(cfg) {}

void SystemIdentificationApp::main(void) {
    rightMotor.start();
	leftMotor.start();
	imu.calibrate();
	led.on(); //initialization complete

	const IMU_Data& imuData = imu.dataPublic;


	char buff[200];
	snprintf(buff, sizeof(buff), "t (ms), theta_estimate (rad), uL (%%), uR (%%), f_x (ms^-2), f_y (ms^-2), f_z (ms^-2), w_x (rad/s), w_y (rad/s), w_z (rad/s)");
	transmitter.sendLine(std::string(buff));
	
	bool stabilized = false;

	flagUpdateTimer.start();

	float reference_angle = 0.0f;
	
	while(time_ms <= MAX_TIME) {

		if (time_ms >= 20000) stabilized = true;

		//system update freq
		if (flags.flag_100Hz) {
			flags.flag_100Hz = false;
			float dt = 0.01f;

			//gather data from imu
			imu.updateData();

			//update state estimate
			theta_estimate = observer.estimate(imu.dataPublic, dt);

			//control + motor update
			float delta_u_controller, delta_uL, delta_uR, uL_prbs, uR_prbs, uL, uR;
			delta_u_controller = stabilizer.update(reference_angle - theta_estimate, dt);
			delta_uL = delta_u_controller/2.0f;
			delta_uR = -1.0f * delta_u_controller / 2.0f;
			uL_prbs = stabilized ? 1.0f * randomGenerator_L.getState() : 0.0f;
			uR_prbs = stabilized ? 1.0f * randomGenerator_R.getState() : 0.0f;
			uL = trim.uL + delta_uL + uL_prbs;
			uR = trim.uR + delta_uR + uR_prbs;

			uL = std::clamp(uL, 0.0f, 100.0f);
			uR = std::clamp(uR, 0.0f, 100.0f);

			leftMotor.setThrottlePercentage(uL);
			rightMotor.setThrottlePercentage(uR);

			//telemetry
			snprintf(buff, sizeof(buff), "%lu, %.2f, %.2f, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %.3f",
			static_cast<unsigned long> (time_ms),
			leftMotor.getThrottlePercentage(),
			rightMotor.getThrottlePercentage(),
			imuData.a_x, imuData.a_y, imuData.a_z,
			imuData.omega_x, imuData.omega_y, imuData.omega_z,
			theta_estimate);

			transmitter.sendLine(std::string(buff));

		}

		if (flags.flag_10Hz) {
			flags.flag_10Hz = false;
			
			//update PRBS's
			randomGenerator_L.update();
			randomGenerator_R.update();
		}
	}
	
	rightMotor.setThrottlePercentage(0.0f);
	leftMotor.setThrottlePercentage(0.0f);
	led.off(); // transmission complete
}