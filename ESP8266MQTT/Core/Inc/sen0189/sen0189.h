#ifndef SEN0189_H
#define SEN0189_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"
#include <dma/direct_memory_access.h>

typedef struct __attribute__((__packed__)) sen0189 {
	uint32_t				channel;
	direct_memory_access*	dma;
} sen0189;

sen0189* sen0189_init(direct_memory_access* dma, uint32_t channel);

void sen0189_destroy(sen0189* sen0189);

uint32_t sen0189_get_channel(sen0189* sen0189);

void sen0189_set_channel(sen0189* sen0189, uint32_t channel);

direct_memory_access* sen0189_get_dma(sen0189* sen0189);

void sen0189_set_dma(sen0189* sen0189, direct_memory_access* dma);

float sen0189_read(sen0189* sen0189);

#endif
