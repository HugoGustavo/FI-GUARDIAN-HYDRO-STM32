#ifndef STM32_UTIL_H
#define STM32_UTIL_H

#include "stm32l4xx_hal.h"

uint32_t stm32_util_read_analog(ADC_HandleTypeDef* pin);

#endif
