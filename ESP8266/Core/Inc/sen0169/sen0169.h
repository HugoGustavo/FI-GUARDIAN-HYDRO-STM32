#ifndef SEN0169_H
#define SEN0169_H

#include <stdlib.h>
#include <stdio.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"

typedef struct sen0169 {
	ADC_HandleTypeDef* 	pin;
	float 				offset;
	unsigned int* 		readings;
	unsigned int 		index;
} sen0169;

sen0169* sen0169_init(ADC_HandleTypeDef* pin);

void sen0169_destroy(sen0169* sen0169);

ADC_HandleTypeDef* sen0169_get_pin(sen0169* sen0169);

void sen0169_set_pin(sen0169* sen0169, ADC_HandleTypeDef* pin);

float sen0169_get_offset(sen0169* sen0169);

void sen0169_set_offset(sen0169* sen0169, const float offset);

unsigned int* sen0169_get_readings(sen0169* sen0169);

void sen0169_set_readings(sen0169* sen0169, unsigned int* readings);

unsigned int sen0169_get_index(sen0169* sen0169);

void sen0169_set_index(sen0169* sen0169, const unsigned int index);

float sen0169_read(sen0169* sen0169);

float sen0169_average(sen0169* sen0169);

#endif
