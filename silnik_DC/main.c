#include "config.h"
#include "wheel_drive.h"
#include "servo_control.h"
#include "timer_init.h"
#include "ultrasonic_sensor.h"
#include "pins.h"
#include "spi.h"
#include "uart.h"
#include "ssd1306.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t distance_cm = 0;
uint8_t interrupt_iteration = 0;

uint8_t turn_iteration = 0;

uint8_t page_value = 0xB0;
uint8_t current_column_value = 0;

uint8_t *page = &page_value;
uint8_t *current_column = &current_column_value;

int main(void)
{	
	ssd1306_init();

	spi_init();
	ssd1306_setup();

	sensor_init();
	
	timer_set();
	
	wheel_init();
	
	servo_init();
	
	uart_init();
	
	ssd1306_clear_display();
	
	servo_set(SERVO_MIDDLE);
	
	uint8_t pad_key = 0;
    while (1)
    {
		pad_key = uart_pad_key(pad_key);
		switch(pad_key)
		{
			case 0: // the car will stop
			wheel_control_direction(BRAKE); 
			break;
			
			case 1: // car will go forwards
            wheel_control_direction(FORWARDS); 
			break;
			
			case 2: // car will go backwards
			wheel_control_direction(BACKWARDS); 
			break;
			
			case 4: // car will turn left
			wheel_control_direction(TURN_LEFT); 
			break;
			
			case 5: // motor with ultrasonic sensor will turn on middle
			servo_set(SERVO_MIDDLE); 
			break;
			
			case 8: // car will turn right
			wheel_control_direction(TURN_LEFT); 
			break;
			
			case 9: // motor with ultrasonic sensor will turn on right side
			servo_set(SERVO_RIGHT); 
			break;
			
			case 17: // turn on/off interrupts
			if(turn_iteration % 2 == 0)
			{
				sei();
			}
			else
			{
				cli(); 
				distance_cm = 21;
			}
			turn_iteration++;
			break;
			
			case 33: // motor with ultrasonic sensor will turn on left side
			servo_set(SERVO_LEFT); 
			break;
			
			default: // car will stop
			wheel_control_direction(BRAKE); 
			break;
		}
    }
}
ISR(TIMER1_COMPA_vect) // interrupt will check distance and print on OLED
{
	interrupt_iteration++;
	if((interrupt_iteration % 5) == 0) // once on five times distance will be checked
	{
		distance_cm = sensor_measure_distance(); // ultrasonic sensor return value of distance
		ssd1306_send_number(distance_cm, page, current_column); // OLED displaying distance [cm]
	}
}