/*
 * Constants.h
 *
 *  Created on: Apr 1, 2026
 *      Author: shanewilson2507
*/

#ifndef COMMON_INC_CONSTANTS_H_
#define COMMON_INC_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

// Mathematical constants
#define PI 3.1415927f    // float

// Physical constants
#define G  9.80665f      // standard gravity in m/s^2

// Angle conversion macros
#define DEG_TO_RAD (PI / 180.0f)
#define RAD_TO_DEG (180.0f / PI)

#ifdef __cplusplus
}
#endif

#endif // COMMON_INC_CONSTANTS_H_