#include "Timer.hpp"

Timer::Timer(const TimerConfig_t& cfg) 
    : tim(cfg.tim)
{
    TIM_Init(tim, cfg.tim_ctx);
    tim->disable_interrupt(tim);
    tim->stop(tim);
    tim->enable_interrupt(tim);
}

void Timer::start() {
    tim->start(tim);
}

void Timer::stop() {
    tim->stop(tim);
}

void Timer::setCallback(CallbackContext_t callbackContext) {
    tim->set_callback(tim, callbackContext);
    this->callbackContext = callbackContext;
}
