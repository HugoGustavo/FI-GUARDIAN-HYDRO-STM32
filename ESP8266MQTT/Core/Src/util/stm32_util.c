#include <util/stm32_util.h>

volatile atomic_flag adc_in_use = ATOMIC_FLAG_INIT;

void stm32_util_read_analog_configure(uint32_t channel){
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, channel);
	LL_ADC_SetChannelSamplingTime(ADC1, channel, LL_ADC_SAMPLINGTIME_24CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, channel, LL_ADC_SINGLE_ENDED);
}

uint16_t stm32_util_read_analog(uint32_t channel){
	stm32_util_read_analog_configure(channel);

	if( atomic_flag_test_and_set(&adc_in_use) == true) return 0xFFFF;

	// Start Internal Regulator
	LL_ADC_DisableDeepPowerDown(ADC1);
	LL_ADC_EnableInternalRegulator(ADC1);

	LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
	while ( LL_ADC_IsCalibrationOnGoing(ADC1) );

	LL_ADC_Enable(ADC1);
	while ( LL_ADC_IsActiveFlag_ADRDY(ADC1) == 0 );
	if( LL_ADC_IsActiveFlag_EOC(ADC1) ) LL_ADC_ClearFlag_EOC(ADC1);

	//LL_ADC_REG_StartConversion(ADC1);
	//while(LL_ADC_IsActiveFlag_EOC(ADC1) == 0);


	uint16_t result = 0;
	for(register uint32_t i = 0 ; i < 10; i++){
		LL_ADC_REG_StartConversion(ADC1);
		while( LL_ADC_IsActiveFlag_EOC(ADC1) == 0 );
		if( LL_ADC_IsActiveFlag_EOC(ADC1) ) LL_ADC_ClearFlag_EOC(ADC1);
		result = result + LL_ADC_REG_ReadConversionData12(ADC1);
		LL_ADC_REG_StopConversion(ADC1);
	}
	result = result / 10;
	LL_ADC_Disable(ADC1);
	atomic_flag_clear(&adc_in_use);
	return result;
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
