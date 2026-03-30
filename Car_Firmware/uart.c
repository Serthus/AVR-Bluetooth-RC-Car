/**
 * @file uart.c
 * @brief bluetooth using to control car
 */ 

#include "pins.h"

#include <avr/io.h>

void uart_init()
{
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	
	// Turns ON - transmitter and receiver
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	// Without doubling transfer rate
	UCSR0A &= ~(1 << U2X0);
	
	// Asynchronous communication doesn't require clock pin
	UCSR0C &= ~((1 << UMSEL01) | (1 << UMSEL00));
	
	// Sets parity bits
	UCSR0C &= ~((1 << UPM01) | (1 << UPM00));
	
	// Sets one stop bit
	UCSR0C &= ~(1 << USBS0);
	
	// Sets number of data bits
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	// Turns off clock polarity
	UCSR0C &= ~(1 << UCPOL0);
	
	// Sets 9600bps
	UBRR0L = 103;
}
uint8_t uart_receiver() // Receives data
{
	while(!(UCSR0A & (1 << RXC0))); // Receive complete
	return UDR0;
}
void uart_transmit(uint8_t data) // Sends data
{
	while(!(UCSR0A & (1 << UDRE0))); // Transmit complete
	UDR0 = data;
}
uint8_t uart_pad_key(uint8_t value) // Recognizes the pad button
{
	if(uart_receiver() == 255)
	{
		if(uart_receiver() == 1)
		{
			if(uart_receiver() == 1)
			{
				if(uart_receiver() == 1)
				{
					if(uart_receiver() == 2)
					{
						value = uart_receiver();
						if(value == 0)
						{
							value = uart_receiver();
						}
						else
						{
							value++;
						}
					}
				}
			}
		}
	}
	return value;
}