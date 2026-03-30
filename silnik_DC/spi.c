/**
 * @file spi.c
 * @brief Controls the SPI peripheral for the SSD1306 display
 */ 

#include "spi.h"
#include "pins.h"
#include "ssd1306.h"

#include <avr/io.h>

void spi_init()
{
	DDRB |= (1 << PB2); // Pin PB2 set as output for SPI Master
	
	SPCR = 0;
	
	SPCR |= (1 << SPE) | (1 << MSTR); // Enable SPI (these bits have to be set simultaneously for correct work)
	
	SPCR &= ~(1 << DORD); // MSB first then LSB
	
	SPCR &= ~(1 << CPOL); // Clock set to 1 when data is send
	SPCR &= ~(1 << CPHA); // Sampling on rising edge
	
	// Clock frequency: 16 000 000 / 32 = 500 000 Hz
	SPCR &= ~(1 << SPR0);
	SPCR |= (1 << SPR1);
	SPSR |= (1 << SPI2X);
}
void spi_write_command(uint8_t data) // Sends command via SPI and manages OLED pins
{
	ssd1306_command_mode(); // Set pin to communicate via command
	ssd1306_spi_cs_low();
	SPDR = data;
	while(!(SPSR & (1 << SPIF))); // Waits for complete serial transfer 
	ssd1306_spi_cs_high(); 
	
}
void spi_write_data(uint8_t data) // Sends data via SPI and manages OLED pins
{
	ssd1306_data_mode(); // Set pin to communicate via data
	ssd1306_spi_cs_low();
	SPDR = data;
	while(!(SPSR & (1 << SPIF))); // Waits for complete serial transfer 
	ssd1306_spi_cs_high();
}