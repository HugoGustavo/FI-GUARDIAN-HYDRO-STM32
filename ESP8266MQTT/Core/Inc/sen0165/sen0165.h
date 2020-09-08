#ifndef SEN0165_H
#define SEN0165_H

#include <stdio.h>
#include <stdlib.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"
#include <dma/direct_memory_access.h>

typedef struct __attribute__((__packed__)) sen0165 {
	uint32_t				channel;
	float 					offset;
	float					voltage;
	unsigned int 			readings[40];
	unsigned int 			index;
	direct_memory_access*	dma;
} sen0165;

sen0165* sen0165_init(direct_memory_access* dma, uint32_t channel, float offset);

void sen0165_destroy(sen0165* sen0165);

ADC_HandleTypeDef* sen0165_get_pin(sen0165* sen0165);

void sen0165_set_pin(sen0165* sen0165, ADC_HandleTypeDef* pin);

uint32_t sen0165_get_channel(sen0165* sen0165);

void sen0165_set_channel(sen0165* sen0165, uint32_t channel);

float sen0165_get_offset(sen0165* sen0165);

void sen0165_set_offset(sen0165* sen0165, const float offset);

float sen0165_get_voltage(sen0165* sen0165);

void sen0165_set_voltage(sen0165* sen0165, const float voltage);

unsigned int* sen0165_get_readings(sen0165* sen0165);

void sen0165_set_readings(sen0165* sen0165, unsigned int readings[]);

unsigned int sen0165_get_index(sen0165* sen0165);

void sen0165_set_index(sen0165* sen0165, const unsigned int index);

direct_memory_access* sen0165_get_dma(sen0165* sen0165);

void sen0165_set_dma(sen0165* sen0165, direct_memory_access* dma);

float sen0165_read(sen0165* sen0165);

float sen0165_average(sen0165* sen0165);

#endif
