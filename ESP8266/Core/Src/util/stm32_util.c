#include <util/stm32_util.h>

uint16_t stm32_util_configure_channel(ADC_HandleTypeDef* pin, uint32_t channel){
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	return HAL_ADC_ConfigChannel(pin, &sConfig) != HAL_OK ? 0 : 1;
}

uint32_t stm32_util_read_analog(ADC_HandleTypeDef* pin, uint32_t channel){
	stm32_util_configure_channel(pin, channel);

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

void stm32_util_delay_in_seconds(uint32_t seconds){
	stm32_util_delay_in_milliseconds(seconds * 1000);
}

void stm32_util_delay_in_microseconds(uint32_t microseconds){
	DWT_Delay(microseconds);
}

void stm32_util_delay_in_milliseconds(uint32_t milliseconds){
	HAL_Delay(milliseconds);
}

void stm32_util_float_to_char(float value, char* result){
	int is_negative = ( value < 0 ) ? 1 : 0;
	value = (value < 0) ? -value : value;

	int integer_part = value;                  // Get the integer part
	float fraction_value = value - integer_part;      // Get fraction fraction
	int fraction_part = trunc(fraction_value * 1000);  //  Get fraction to integer

	if( is_negative ) sprintf (result, (char*) "-%03d.%03d", integer_part, fraction_part);
	else sprintf (result, (char*) "%03d.%03d", integer_part, fraction_part);

}

