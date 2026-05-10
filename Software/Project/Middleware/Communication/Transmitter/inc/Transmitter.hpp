/*
 * Transmitter.hpp
 *
 *  Created on: Mar 29, 2026
 *      Author: shanewilson2507
 */

#ifndef MIDDLEWARE_INC_TRANSMITTER_HPP_
#define MIDDLEWARE_INC_TRANSMITTER_HPP_

#include  "USB.h" // "USB.h" // "../../../../Platform/inc/USB.h"
#include <string>

class Transmitter {
    USB_t usb;
public:
    Transmitter(void);
    void sendString(const std::string& str);
    void sendLine(const std::string& str);
};

#endif /* MIDDLEWARE_INC_TRANSMITTER_HPP_ */
