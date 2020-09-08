#include <util/stm32_util.h>

uint32_t stm32_util_read_analog(uint32_t channel){
	return 0;
}

void stm32_util_set_pin_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void stm32_util_set_pin_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void stm32_util_delay_in_seconds(uint32_t seconds){
	stm32_util_delay_in_milliseconds(seconds * 1000);
}

void stm32_util_delay_in_microseconds(uint32_t microseconds){
	DWT_Delay(microseconds);
}

void stm32_util_delay_in_milliseconds(uint32_t milliseconds){
	HAL_Delay(milliseconds);
}
