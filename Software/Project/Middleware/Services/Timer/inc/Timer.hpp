/*
 * Timer.hpp
 *
 *  Created on: Mar 23, 2026
 *      Author: shanewilson2507
 */

#include "TIM.h"//"TIM.h"
#include "TimerConfig.h"
#include "Callback.h" //"Callback.h"


//TODO: Add functionality to change the Timer period in TIM_t and then set default in the constructor
//TODO: Add delay_ms (maybe in utils/ or just delay.h)
class Timer {
private:
    CallbackContext_t callbackContext;
    TIM_t* tim;
public:
    Timer(const TimerConfig_t& cfg);
    void start();
    void stop();
    void setCallback(CallbackContext_t callbackContext);
 };
