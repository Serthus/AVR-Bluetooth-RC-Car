/**
 * @file ultrasonic_sensor.h
 * @brief measuring distance between obstacle
 */ 

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include <avr/io.h>

#define DISTANCE 15.0f // distance in cm, causes stopping motors max value = 130 cm, min value = 0,6 cm

void sensor_init();
uint8_t sensor_measure_distance();

#endif /* ULTRASONIC_SENSOR_H_ */