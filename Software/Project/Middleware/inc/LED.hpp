/*
 * LED.hpp
 *
 *  Created on: Mar 3, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_LED_HPP_
#define MIDDLEWARE_INC_LED_HPP_

#include "LEDConfig.h"

enum class LEDState {
	OFF,
	ON
};

class LED {
private:
	GPIO_t gpio;
	LEDState state;
public:
	explicit LED(const LED_Config_t& cfg);

	void on();
	void off();
	void toggle();

	LEDState getState() const;
	void setState(LEDState state);
};

#endif /* MIDDLEWARE_INC_LED_HPP_ */
