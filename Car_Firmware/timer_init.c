/**
 * @file timer_init.c
 * @brief Initializes timer for servo motor
 */

#include "timer_init.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void timer_set()
{
	// timer0 - uses to control servo motor
	TCCR0A = 0;
	TCCR0B = 0;
	
	// Phase correct PWM, top value: 156
	TCCR0A |= (1 << WGM00); 
	TCCR0B |= (1 << WGM02); 
	TCCR0A |= (1 << COM0B1);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	OCR0A = 156;
	
	// timer1 - uses to ultrasonic sensor
	cli(); // Disables global interrupt
	TCCR1A = 0;
	TCCR1B = 0;
	
	// CTC, prescaler: 1024, top value: 255
	TCCR1A |= (1 << COM1B1) | (1 << WGM11);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12); 
	TIMSK1 |= (1 << OCIE1A);
	ICR1 = 0xFF;
	
	// timer2 - uses to measure distance by ultrasonic sensor
	TCCR2A = 0;
	TCCR2B = 0;
	
	// Normal mode, prescaler: 256, top value 255
	TCCR2B |= (1 << CS22) | (1 << CS21);
}