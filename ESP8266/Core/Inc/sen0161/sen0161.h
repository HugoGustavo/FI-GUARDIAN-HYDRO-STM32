#ifndef SEN0161_H
#define SEN0161_H

#include <stdlib.h>
#include <stdio.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"

typedef struct sen0161 {
	ADC_HandleTypeDef* 	pin;
	float 				offset;
	unsigned int* 		readings;
	unsigned int 		index;
} sen0161;

sen0161* sen0161_init(ADC_HandleTypeDef* pin);

void sen0161_destroy(sen0161* sen0161);

ADC_HandleTypeDef* sen0161_get_pin(sen0161* sen0161);

void sen0161_set_pin(sen0161* sen0161, ADC_HandleTypeDef* pin);

float sen0161_get_offset(sen0161* sen0161);

void sen0161_set_offset(sen0161* sen0161, const float offset);

unsigned int* sen0161_get_readings(sen0161* sen0161);

void sen0161_set_readings(sen0161* sen0161, unsigned int* readings);

unsigned int sen0161_get_index(sen0161* sen0161);

void sen0161_set_index(sen0161* sen0161, const unsigned int index);

float sen0161_read(sen0161* sen0161);

float sen0161_average(sen0161* sen0161);

#endif
