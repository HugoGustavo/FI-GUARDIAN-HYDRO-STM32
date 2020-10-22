#ifndef SEN0169_H
#define SEN0169_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"

typedef struct __attribute__((__packed__)) sen0169 {
	uint32_t				channel;
	unsigned int 			readings[12];
	unsigned int 			index;
} sen0169;

sen0169* sen0169_init(uint32_t channel);

void sen0169_destroy(sen0169* sen0169);

uint32_t sen0169_get_channel(sen0169* sen0169);

void sen0169_set_channel(sen0169* sen0169, uint32_t channel);

unsigned int* sen0169_get_readings(sen0169* sen0169);

void sen0169_set_readings(sen0169* sen0169, unsigned int readings[]);

unsigned int sen0169_get_index(sen0169* sen0169);

void sen0169_set_index(sen0169* sen0169, const unsigned int index);

float sen0169_read(sen0169* sen0169);

float sen0169_average(sen0169* sen0169);

#endif
