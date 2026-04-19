/*
 * USB.h
 *
 *  Created on: Mar 29, 2026
 *      Author: shanewilson2507
 */

#ifndef PLATFORM_INC_USB_H_
#define PLATFORM_INC_USB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct USB USB_t;

struct USB {
    void (*write) (const USB_t* usb, uint8_t* data, uint16_t len);
    void (*write_string) (const USB_t* usb, const char* string);
};

void USB_Init(USB_t* usb);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_INC_USB_H_ */
