/**
 * @file ssd1306.h
 * @brief File contains commands to communicate with OLED display
 */ 

#ifndef SSD1306_H_
#define SSD1306_H_

#include <avr/io.h>

// --- Initialization & Hardware Control ---
void ssd1306_init(void);
void ssd1306_spi_cs_high(void);
void ssd1306_spi_cs_low(void);
void ssd1306_command_mode(void);
void ssd1306_data_mode(void);
void ssd1306_setup(void);

// --- Display Operations ---
void ssd1306_set_column(uint8_t value);
void ssd1306_clear_display(void);

// --- Drawing Digits ---
void ssd1306_print_zero(uint8_t *page, uint8_t *current_column);
void ssd1306_print_one(uint8_t *page, uint8_t *current_column);
void ssd1306_print_two(uint8_t *page, uint8_t *current_column);
void ssd1306_print_three(uint8_t *page, uint8_t *current_column);
void ssd1306_print_four(uint8_t *page, uint8_t *current_column);
void ssd1306_print_five(uint8_t *page, uint8_t *current_column);
void ssd1306_print_six(uint8_t *page, uint8_t *current_column);
void ssd1306_print_seven(uint8_t *page, uint8_t *current_column);
void ssd1306_print_eight(uint8_t *page, uint8_t *current_column);
void ssd1306_print_nine(uint8_t *page, uint8_t *current_column);

// --- Logic & Math ---
void ssd1306_send_number(uint32_t number, uint8_t *page, uint8_t *current_column);
uint8_t ssd1306_unfold_number(int *digit_array, uint32_t number, uint8_t digit_count);

#endif /* SSD1306_H_ */