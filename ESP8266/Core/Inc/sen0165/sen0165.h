#ifndef SEN0165_H
#define SEN0165_H

#include <stdio.h>
#include <stdlib.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"

typedef struct sen0165 {
	ADC_HandleTypeDef* 	pin;
	float 				offset;
	unsigned int* 		readings;
	unsigned int 		index;
} sen0165;

sen0165* sen0165_init(ADC_HandleTypeDef* pin);

void sen0165_destroy(sen0165* sen0165);

ADC_HandleTypeDef* sen0165_get_pin(sen0165* sen0165);

void sen0165_set_pin(sen0165* sen0165, ADC_HandleTypeDef* pin);

float sen0165_get_offset(sen0165* sen0165);

void sen0165_set_offset(sen0165* sen0165, const float offset);

unsigned int* sen0165_get_readings(sen0165* sen0165);

void sen0165_set_readings(sen0165* sen0165, unsigned int* readings);

unsigned int sen0165_get_index(sen0165* sen0165);

void sen0165_set_index(sen0165* sen0165, const unsigned int index);

float sen0165_read(sen0165* sen0165);

float sen0165_average(sen0165* sen0165);

#endif
