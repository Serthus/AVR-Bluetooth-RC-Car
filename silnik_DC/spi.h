/**
 * @file spi.h
 * @brief Controls the SPI peripheral for the OLED display
 */ 

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void spi_init();
void spi_write_command(uint8_t data); // Sends command via SPI
void spi_write_data(uint8_t data); // Sends data via SPI

#endif /* SPI_H_ */