#pragma once

#include "App.hpp"
#include "IMU.hpp"
#include <cstdint>

class PIController {
    float Kp, Ki;
    float error_integral;
    float u_i_min, u_i_max;
public:
    PIController(float Kp, float Ki, float u_i_min, float u_i_max);
    float update(float error, float dt);
};

class ComplementaryFilter {
    float alpha;
    float theta;

    bool initialized = false;
public:
    ComplementaryFilter(float alpha);
    float estimate(const IMU_Data& data, float dt);
};

class PRBS16Generator {
    uint16_t lfsr;
    float state;
    public:
        explicit PRBS16Generator(uint16_t seed);
        void update();
        float getState() const;
};

struct TrimPoint {
    float uL;
    float uR;
};

class SystemIdentificationApp : public App {
public:
    SystemIdentificationApp(const App_Config_t& cfg);
    void main(void) override;

private:
    float theta_estimate;
    const TrimPoint trim {28.0f, 22.0f}; //measured trim values
    PIController stabilizer {2.0f, 1.0f, -20.0f, 20.0f};
    ComplementaryFilter observer {0.95f};
    PRBS16Generator randomGenerator_L {0xABCD};
    PRBS16Generator randomGenerator_R {0xBCDE};
};