/**
 * @file ssd1306.c
 * @brief File contains commands for SSD1306
 */ 
#include "ssd1306.h"
#include "pins.h"
#include "spi.h"
#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

void ssd1306_init() // Initializes SSD1306 display 
{
	DDRB |= (1 << SPI_CLK) | (1 << SPI_DATA);
	DDRC |= (1 << SPI_CS) | (1 << SPI_OLED_MODE) | (1 << SPI_OLED_RESET);
	
	PORTC &= ~(1 << SPI_CS);
}
void ssd1306_spi_cs_high() // Manges pin CS for correct transmission
{
	PORTC |= (1 << SPI_CS);
}
void ssd1306_spi_cs_low() // Manges pin CS for correct transmission
{
	PORTC &= ~(1 << SPI_CS);
}
void ssd1306_command_mode() // Communication via commands
{
	PORTC &= ~(1 << SPI_OLED_MODE); 
}
void ssd1306_data_mode() // Communications via data
{
	PORTC |= (1 << SPI_OLED_MODE); 
}
void ssd1306_setup() // Configurations SSD1306 
{
	// reset
	PORTC &= ~(1 << SPI_OLED_RESET);
	_delay_us(10);
	
	PORTC |= (1 << SPI_OLED_RESET);
	_delay_ms(1);
	
	// Sets charging pump
	spi_write_command(0x8D);
	spi_write_command(0x14);
	
	// Sets contrast
	spi_write_command(0x81);
	spi_write_command(0xFF);
	
	// Normal display mode (pixels ON based on data)
	spi_write_command(0xA4); 
	spi_write_command(0xA6); // Non-inverted display
	
	// Sets page addressing mode
	spi_write_command(0x20);
	spi_write_command(0x02);
	
	spi_write_command(0x40); // Sets display start line to 0
	spi_write_command(0xA1); // Horizontal re-map (horizontal flip)
	spi_write_command(0xC8); // Vertical re-map (vertical flip)
	
	// Sets multiplex ratio to 64
	spi_write_command(0xA8);
	spi_write_command(0x3F); 
	
	// Sets value of display offset: 0
	spi_write_command(0xD3);
	spi_write_command(0x00); 
	
	// Configures COM pins hardware
	spi_write_command(0xDA);
	spi_write_command(0x12);
	
	// Sets display clock divide equals zero 0, oscillator frequency = 100% ?? 
	spi_write_command(0xD5);
	spi_write_command(0xF0); 
	
	// Configures pre-charge period
	spi_write_command(0xD9);
	spi_write_command(0x77);
	
	// Sets voltage: 0,65V
	spi_write_command(0xDB);
	spi_write_command(0x30); 
	
	// Turns display ON
	spi_write_command(0xAF); 
	_delay_ms(100); 
}
void ssd1306_clear_display() // Clears all RAM across all pages
{
	spi_write_command(0x00); // Sets LSB for column start address
	spi_write_command(0x10); // Sets MSB for column start address
	
	for(int i = 0; i < 8; i++)
	{
		spi_write_command(0xB0 + i); // Sets page address (0 to 7)
		for(int j = 0; j < 128; j++)
		{
			spi_write_data(0x00); // Clears 8 vertical pixels for all 128 columns
		}
	}
}
void ssd1306_print_zero(uint8_t *page, uint8_t *current_column) // Prints digit 0 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b11111100);
	spi_write_data(0b11111100);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b11111100);
	spi_write_data(0b11111100);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_one(uint8_t *page, uint8_t *current_column) // Prints digit 1 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00001100);
	spi_write_data(0b00001100);
	spi_write_data(0b11111111);
	spi_write_data(0b11111111);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
}
void ssd1306_print_two(uint8_t *page, uint8_t *current_column) // Prints digit 2 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00001100);
	spi_write_data(0b00001100);
	spi_write_data(0b11000011);
	spi_write_data(0b11000011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00001100);
	spi_write_data(0b00001100);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
}
void ssd1306_print_three(uint8_t *page, uint8_t *current_column) // Prints digit 3 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b10000100);
	spi_write_data(0b10000100);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b11001100);
	spi_write_data(0b11001100);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_four(uint8_t *page, uint8_t *current_column) // Prints digit 4 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b11110000);
	spi_write_data(0b11110000);
	spi_write_data(0b11001100);
	spi_write_data(0b11001100);
	spi_write_data(0b11111111);
	spi_write_data(0b11111111);
	spi_write_data(0b11000000);
	spi_write_data(0b11000000);
	
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_five(uint8_t *page, uint8_t *current_column) // Prints digit 5 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00111111);
	spi_write_data(0b00111111);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b11000011);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_six(uint8_t *page, uint8_t *current_column) // Prints digit 6 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b11111100);
	spi_write_data(0b11111100);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b11000011);
	spi_write_data(0b11000000);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_seven(uint8_t *page, uint8_t *current_column) // Prints digit 7 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b11000011);
	spi_write_data(0b11000011);
	spi_write_data(0b00111100);
	spi_write_data(0b00111100);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_eight(uint8_t *page, uint8_t *current_column) // Prints digit 8 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column);
	
	spi_write_data(0b11001100);
	spi_write_data(0b11001100);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b11001100);
	spi_write_data(0b11001100);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_print_nine(uint8_t *page, uint8_t *current_column) // Prints digit 9 (8x10 pixels, 8x16 memory block)
{
	spi_write_command(*page); // Sets current page
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00001100);
	spi_write_data(0b00001100);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b00110011);
	spi_write_data(0b11111100);
	spi_write_data(0b11111100);
	
	spi_write_command(*page+1); // Sets next page (lower half of digit)
	ssd1306_set_column(*current_column); // Sets current column
	
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000011);
	spi_write_data(0b00000000);
	spi_write_data(0b00000000);
}
void ssd1306_send_number(uint32_t number, uint8_t *page, uint8_t *current_column) // Splits a number into digits, stores them in an array, and prints them sequentially
{
	uint8_t digit_count = 0;
	int digit_array[32];
	digit_count = ssd1306_unfold_number(digit_array, number, digit_count);
	for(int i = 0; i < digit_count; i++)
	{
		// Handles line wrapping and screen clearing if display is full
		if(*current_column >= 108)
		{
			*current_column = 0;
			if(*page == 0xB6)
			{
				*page = 0xB0;
				ssd1306_clear_display();
			}
			else
			{
				*page = *page + 2;
			}
		}
		switch(digit_array[i]) // Prints sequentially digits
		{
			case 0:
				ssd1306_print_zero(page, current_column);
				break;
			
			case 1:
				ssd1306_print_one(page, current_column);
				break;
			
			case 2:
				ssd1306_print_two(page, current_column);
				break;
			
			case 3:
				ssd1306_print_three(page, current_column);
				break;
			
			case 4:
				ssd1306_print_four(page, current_column);
				break;
			
			case 5:
				ssd1306_print_five(page, current_column);
				break;
			
			case 6:
				ssd1306_print_six(page, current_column);
				break;
			
			case 7:
				ssd1306_print_seven(page, current_column);
				break;
			
			case 8:
				ssd1306_print_eight(page, current_column);
				break;
			
			case 9:
				ssd1306_print_nine(page, current_column);
				break;
				
		    default:
				break;
		}
		*current_column = *current_column + 10;
	}
	*current_column = *current_column + 10;
}
void ssd1306_set_column(uint8_t value)
{
	spi_write_command(value & 0x0F); // Sets LSB for column start address
	spi_write_command(0x10 | (value >> 4)); // Sets MSB for column start address
}
uint8_t ssd1306_unfold_number(int *digit_array, uint32_t number, uint8_t digit_count) // Splits a number into individual digits and stores them in an array
{
	uint8_t rest_from_division = 0;
	while(number != 0)
	{
		// Splits number into digits
		rest_from_division = number % 10;
		number = number / 10;
		digit_array[digit_count] = rest_from_division;
		digit_count++;
	}
	// Handles case where the input number is 0
	if(digit_count == 0 && number == 0)
	{
		digit_array[digit_count] = 0;
		digit_count++;
	}
	uint8_t buffer = 0;
	uint8_t i = digit_count;
	for(int j = 0; j < (digit_count / 2); j++)
	{
		// Reverses the array to put digits in the correct order
		buffer = digit_array[j];
		digit_array[j] = digit_array[i - 1];
		digit_array[i - 1] = buffer;
		i--;
	}
	return digit_count;
}