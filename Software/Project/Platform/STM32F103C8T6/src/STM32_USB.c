/*
 * STM32_USB.c
 *
 *  Created on: Mar 29, 2026
 *      Author: shanewilson2507
 */

#include "USB.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include <string.h>

void STM32_USB_Write(const USB_t* usb, uint8_t* data, uint16_t len) {
    while(CDC_Transmit_FS(data, len) == USBD_BUSY); // wait until USB ready to transmit    
}

void STM32_USB_Write_String(const USB_t* usb, const char* string) {
    STM32_USB_Write(usb, (uint8_t*) string, strlen(string));
}

void USB_Init(USB_t* usb) {
    usb->write = STM32_USB_Write;
    usb->write_string = STM32_USB_Write_String;
}




