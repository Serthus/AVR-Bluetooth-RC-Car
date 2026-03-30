/**
 * @file uart.h
 * @brief bluetooth using to control car
 */ 

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void uart_init(void);
uint8_t uart_receiver(void); // Receives data
void uart_transmit(uint8_t); // Sends data
uint8_t uart_pad_key(uint8_t value); // Recognizes the pad button

#endif /* UART_H_ */