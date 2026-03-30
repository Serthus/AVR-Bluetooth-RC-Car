/**
 * @file servo_control.c
 * @brief Controls servo motor that rotates ultrasonic sensor
 */ 

#include "servo_control.h"
#include "pins.h"

#include <avr/io.h>

void servo_init()
{
	DDRD |= (1 << PWM_SERVO_MOTOR);
}
void servo_set(uint16_t value)
{
	OCR0B = value; // Changing the PWM duty cycle 
}