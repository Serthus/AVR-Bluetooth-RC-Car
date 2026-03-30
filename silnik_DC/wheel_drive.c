/**
 * @file wheel_drive.c
 * @brief Main source file for wheel control.
 */

#include "config.h"
#include "wheel_drive.h"
#include "pins.h"

#include <avr/io.h>

void wheel_init()
{
	DDRD |= (1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4) | (1 << IN6);
	DDRB |= (1 << IN7) | (1 << IN8);
	DDRC |= (1 << IN5);
}
void wheel_control_direction(uint8_t state)
{
	PORTD &= ~(0xDC);
	PORTB &= ~(0x03);
	PORTC &= ~(0x20);
	
	PORTD |= ((state & (0x07)) << 2); // bits PD4, PD3, PD2
	PORTD |= ((state & (0x08)) << 3); // bit PD6
	PORTD |= ((state & (0x20)) << 2); // bit PD7
	PORTB |= ((state & (0x40)) >> 6); // bit PB0
	PORTB |= ((state & (0x80)) >> 6); // bit PB1
	PORTC |= ((state & (0x10)) << 1); // bit PC5
}