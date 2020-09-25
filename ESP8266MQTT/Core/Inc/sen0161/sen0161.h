#ifndef SEN0161_H
#define SEN0161_H

#include <stdlib.h>
#include <stdio.h>
#include <util/stm32_util.h>
#include <dma/direct_memory_access.h>
#include "stm32l4xx_hal.h"

typedef struct __attribute__((__packed__)) sen0161 {
	uint32_t				channel;
	unsigned int 			readings[12];
	unsigned int 			index;
	direct_memory_access*	dma;
} sen0161;

sen0161* sen0161_init(direct_memory_access* dma, uint32_t channel);

void sen0161_destroy(sen0161* sen0161);

ADC_HandleTypeDef* sen0161_get_pin(sen0161* sen0161);

void sen0161_set_pin(sen0161* sen0161, ADC_HandleTypeDef* pin);

uint32_t sen0161_get_channel(sen0161* sen0161);

void sen0161_set_channel(sen0161* sen0161, uint32_t channel);

unsigned int* sen0161_get_readings(sen0161* sen0161);

void sen0161_set_readings(sen0161* sen0161, unsigned int readings[]);

unsigned int sen0161_get_index(sen0161* sen0161);

void sen0161_set_index(sen0161* sen0161, const unsigned int index);

direct_memory_access* sen0161_get_dma(sen0161* sen0161);

void sen0161_set_dma(sen0161* sen0161, direct_memory_access* dma);

float sen0161_read(sen0161* sen0161);

float sen0161_average(sen0161* sen0161);

#endif
