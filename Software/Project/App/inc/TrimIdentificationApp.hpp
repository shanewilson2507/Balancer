#include "App.hpp"

class TrimIdentificationApp : public App {
public:
    static constexpr float TRIM_SUM = 50.0f; // S = uL* + uR*
    static constexpr float uL_MIN = 27.7f;
    static constexpr float uL_MAX = 28.0f;
    static constexpr uint16_t HOLD_PERIOD = 5000; //ms
    static constexpr uint16_t NUM_STEPS = 10;
public:
    TrimIdentificationApp(const App_Config_t& cfg);
    void main(void) override;
private:
    float trimThrottleStepFunction(uint16_t time_ms);
};