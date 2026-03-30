/**
 * @file pins.h
 * @brief Defines pins connected to motors 
 */ 

#ifndef PINS_H_
#define PINS_H_

#include <avr/io.h>

// Left front wheel
#define IN1 PD2 // 1 for forward spin
#define IN2 PD3 // 0 for forward spin

// Right front wheel
#define IN3 PD4 // 1 for forward spin
#define IN4 PD6 // 0 for forward spin

// Left rear wheel
#define IN5 PC5 // 1 for forward spin
#define IN6 PD7 // 0 for forward spin

// Right rear wheel
#define IN7 PB0 // 1 for forward spin
#define IN8 PB1 // 0 for forward spin

// servo motor
#define PWM_SERVO_MOTOR PD5 // Pin for servo motor

// ultrasonic sensor
#define TRIG PC0 // Transmit ultrasonic pulses
#define ECHO PB4 // Receive ultrasonic pulses

#define SPI_CLK PB5        // SPI clock wire
#define SPI_DATA PB3       // SPI data wire
#define SPI_CS PC3         // Chip select (active low)
#define SPI_OLED_RESET PC2 // 0 - reset, 1 - active
#define SPI_OLED_MODE PC1  // 0 - command, 1 - data

#endif