#include <util/stm32_util.h>

uint32_t stm32_util_read_analog(ADC_HandleTypeDef* pin){
	HAL_ADC_Start(pin);
	HAL_ADC_PollForConversion(pin, 100);
	uint32_t raw = (uint32_t) ( HAL_ADC_GetValue(pin) * 0.0049 );
	HAL_ADC_Stop(pin);
	return raw;
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

