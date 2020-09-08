#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_adc.h"

typedef struct __attribute__((__packed__)) direct_memory_access {
	ADC_HandleTypeDef*	hadc;
	uint32_t 			number_channels;
	uint32_t 			adc_values[4];
} direct_memory_access;

direct_memory_access* direct_memory_access_init(ADC_HandleTypeDef* hadc, uint32_t number_channels);

void direct_memory_access_start(direct_memory_access* dma);

uint32_t direct_memory_access_get_adc_value(direct_memory_access* dma, uint32_t channel);

// This function is based on a callback whenever the DMA reads from peripherals to memory
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif
