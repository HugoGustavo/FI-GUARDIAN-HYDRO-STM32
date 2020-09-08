#ifndef STM32_UTIL_H
#define STM32_UTIL_H

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_adc.h"
#include <util/dwt_delay.h>

uint32_t stm32_util_read_analog(uint32_t channel);

void stm32_util_set_pin_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void stm32_util_set_pin_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void stm32_util_delay_in_seconds(uint32_t seconds);

void stm32_util_delay_in_microseconds(uint32_t microseconds);

void stm32_util_delay_in_milliseconds(uint32_t milliseconds);

#endif
