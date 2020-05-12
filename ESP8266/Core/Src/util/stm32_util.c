#include <util/stm32_util.h>

uint32_t stm32_util_read_analog(ADC_HandleTypeDef* pin){
	HAL_ADC_Start(pin);
	HAL_ADC_PollForConversion(pin, 100);
	uint32_t raw = (uint32_t) ( HAL_ADC_GetValue(pin) * 0.0049 );
	HAL_ADC_Stop(pin);
	return raw;
}

