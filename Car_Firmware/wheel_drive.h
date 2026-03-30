/**
 * @file wheel_drive.h
 * @brief control wheels direction
 */

#ifndef WHEEL_DRIVE_H_
#define WHEEL_DRIVE_H_

#include <avr/io.h>

void wheel_init();
void wheel_control_direction(uint8_t state);

#endif /* WHEEL_DRIVE_H_ */