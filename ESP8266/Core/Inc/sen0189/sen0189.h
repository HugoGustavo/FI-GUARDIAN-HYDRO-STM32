#ifndef SEN0189_H
#define SEN0189_H

#include <stdlib.h>
#include <stdio.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"

typedef struct sen0189 {
	ADC_HandleTypeDef* pin;
} sen0189;

sen0189* sen0189_init(ADC_HandleTypeDef* pin);

void sen0189_destroy(sen0189* sen0189);

ADC_HandleTypeDef* sen0189_get_pin(sen0189* sen0189);

void sen0189_set_pin(sen0189* sen0189, ADC_HandleTypeDef* pin);

float sen0189_read(sen0189* sen0189);

#endif
