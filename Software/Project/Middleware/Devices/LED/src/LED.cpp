/*
 * LED.cpp
 *
 *  Created on: Mar 3, 2026
 *      Author: shanewilson2507
 */

#include "GPIO.h"
#include "LED.hpp"

LED::LED(const LED_Config_t& cfg)
	: state(LEDState::OFF)
{
	GPIO_Init(&gpio, cfg.gpio_ctx);
	gpio.write(&gpio, GPIO_LEVEL_HIGH);
}

void LED::on() {
	gpio.write(&gpio, GPIO_LEVEL_LOW); // LED wired in active low configuration
	state = LEDState::ON;
}

void LED::off() {
	gpio.write(&gpio, GPIO_LEVEL_HIGH); // LED wired in active low configuration
	state = LEDState::OFF;
}

void LED::toggle() {
	if (state == LEDState::ON) {
		off();
	} else {
		on();
	}
}

LEDState LED::getState() const {
	return state;
}

void LED::setState(LEDState s) {
	if (s == LEDState::ON) {
		on();
	} else {
		off();
	}
}




