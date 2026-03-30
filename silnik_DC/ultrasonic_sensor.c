/**
 * @file ultrasonic_sensor.c
 * @brief ultrasonic sensor witch is cooperating with servo motor measure distance between obstacle
 */

#include "pins.h"
#include "ultrasonic_sensor.h"
#include "config.h"
#include "wheel_drive.h"
#include "ssd1306.h"

#include <avr/io.h>
#include <util/delay.h>

void sensor_init()
{
	DDRC |= (1 << TRIG);
	DDRB &= ~(1 << ECHO);
}
uint8_t sensor_measure_distance()
{
	uint8_t pulse_tics = 0;
	float pulse_time_us = 0;
	float distance_cm = 0;
	
	// transmit pulses
	PORTC &= ~(1 << TRIG);
	
	TCNT2 = 0;
	while(TCNT2 < 1); // 16us
	
	PORTC |= (1 << TRIG);
	
	TCNT2 = 0;
	while(TCNT2 < 1); // 16us
	
	PORTC &= ~(1 << TRIG);
	
	TCNT2 = 0;
	// receive pulses
	while(!(PINB & (1 << ECHO)))
	{
		if(TCNT2 == 255)
		{
			return 69;
		}
	}
	TCNT2 = 0;
	while(PINB & (1 << ECHO))
	{
		if(TCNT2 == 255)
		{
			break;
		}
	}
	pulse_tics = TCNT2;
	if(pulse_tics == 0)
	{
		return 0;
	}
	else
	{
		pulse_time_us = (pulse_tics * 16.0f) / 2;
		distance_cm = pulse_time_us * 0.0343;
		return distance_cm;
	}
}