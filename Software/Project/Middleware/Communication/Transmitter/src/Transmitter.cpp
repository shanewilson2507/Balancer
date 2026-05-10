/*
 * Transmitter.cpp
 *
 *  Created on: Mar 29, 2026
 *      Author: shanewilson2507
 */

#include "Transmitter.hpp"

Transmitter::Transmitter(void) {
    USB_Init(&usb);
}

void Transmitter::sendString(const std::string& str) {
    usb.write_string(&usb, str.c_str());
}

void Transmitter::sendLine(const std::string& str) {
    sendString(str);
    usb.write_string(&usb, "\n");
}


