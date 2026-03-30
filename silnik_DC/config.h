/**
 * @file config.h
 * @brief Global configuration definitions for the project.
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

/* System clock frequency */
#define F_CPU 16000000UL

// wheel direction
#define FORWARDS 0x55    // Motors turn forwards
#define BACKWARDS 0xAA   // Motors turn backwards
#define BRAKE 0xFF       // Motors brake
#define IDLE 0x00        // Motors idle
#define TURN_RIGHT 0x99  // Car spins right in place
#define TURN_LEFT 0x66   // Car spins left in place

// servo motor
#define SERVO_LEFT 20    // serve motor turn left
#define SERVO_MIDDLE 12  // serve motor set in the middle
#define SERVO_RIGHT 4    // serve motor turn right

#endif /* CONFIG_H_ */