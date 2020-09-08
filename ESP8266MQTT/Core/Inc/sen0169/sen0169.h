#ifndef SEN0169_H
#define SEN0169_H

#include <stdlib.h>
#include <stdio.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"
#include <dma/direct_memory_access.h>

typedef struct __attribute__((__packed__)) sen0169 {
	uint32_t				channel;
	float 					offset;
	unsigned int 			readings[30];
	unsigned int 			index;
	direct_memory_access*	dma;
} sen0169;

sen0169* sen0169_init(direct_memory_access* dma, uint32_t channel, float offset);

void sen0169_destroy(sen0169* sen0169);

uint32_t sen0169_get_channel(sen0169* sen0169);

void sen0169_set_channel(sen0169* sen0169, uint32_t channel);

float sen0169_get_offset(sen0169* sen0169);

void sen0169_set_offset(sen0169* sen0169, const float offset);

unsigned int* sen0169_get_readings(sen0169* sen0169);

void sen0169_set_readings(sen0169* sen0169, unsigned int readings[]);

unsigned int sen0169_get_index(sen0169* sen0169);

void sen0169_set_index(sen0169* sen0169, const unsigned int index);

direct_memory_access* sen0169_get_dma(sen0169* sen0169);

void sen0169_set_dma(sen0169* sen0169, direct_memory_access* dma);

float sen0169_read(sen0169* sen0169);

float sen0169_average(sen0169* sen0169);

#endif
