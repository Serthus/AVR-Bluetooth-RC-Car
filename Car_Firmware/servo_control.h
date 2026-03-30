/**
 * @file servo_control.h
 * @brief Controls servo motor
 */ 

#ifndef SERVO_CONTROL_H_
#define SERVO_CONTROL_H_

#include <avr/io.h>

void servo_init(void);
void servo_set(uint16_t value); // Set to positions: "SERVO_MIDDLE", "SERVO_LEFT", "SERVO_RIGHT"

#endif /* SERVO_CONTROL_H_ */ 