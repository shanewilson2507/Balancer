#pragma once

#include "AppConfig.h"
#include "../../Middleware/inc/LED.hpp" //"LED.hpp" //"../../Middleware/inc/LED.hpp"
#include "../../Middleware/inc/Timer.hpp" //"Timer.hpp" //"../../Middleware/inc/Timer.hpp"
#include "../../Common/inc/Callback.h"//"Callback.h"
#include  "../../Middleware/inc/Motor.hpp" // "Motor.hpp"
#include "../../Middleware/inc/Transmitter.hpp" // "Transmitter.hpp"
#include "../../Middleware/inc/IMU.hpp" // "IMU.hpp"

//TODO: Remove all relative includes
//TODO: add static and const wherever required

struct AppFlags {
    bool update_state_estimate = false;
    bool update_motor_command = false;
    bool update_imu = false;
    bool send_data = false;
};

class App {
protected:
    static uint64_t time_ms; //time in ms since update timer started (interrupt freq = 1kHz)
    LED led;
    Timer flagUpdateTimer;
    Motor leftMotor;
    Motor rightMotor;
    Transmitter transmitter;
    IMU imu;

    AppFlags flags;

    explicit App(const App_Config_t& cfg);
public:
    virtual ~App() = default;
    virtual void main(void) = 0;
private:
    static void flagUpdateCallback(void* flags);
};
