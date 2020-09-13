#include <dma/direct_memory_access.h>

direct_memory_access* direct_memory_access_instance = NULL;

direct_memory_access* direct_memory_access_init(ADC_HandleTypeDef* hadc, uint32_t number_channels){
	if( number_channels == 0 ) return NULL;
	if( direct_memory_access_instance == NULL ){
		direct_memory_access_instance = (direct_memory_access*) malloc(sizeof(direct_memory_access));
		direct_memory_access_instance->hadc = hadc;
		direct_memory_access_instance->number_channels = number_channels;
		for(register uint32_t i = 0; i < number_channels; i++)
			direct_memory_access_instance->adc_values[i] = (uint32_t) 0;
	}
	return direct_memory_access_instance;
}

void direct_memory_access_start(direct_memory_access* dma){
	if( dma == NULL ) return;
	HAL_ADC_Start_DMA(dma->hadc, dma->adc_values, dma->number_channels);
}

uint32_t direct_memory_access_get_adc_value(direct_memory_access* dma, uint32_t channel){
	if( dma == NULL || channel < 0 ) return 0;

	switch( channel ){
		case ADC_CHANNEL_1: return dma->adc_values[0];
		case ADC_CHANNEL_2: return dma->adc_values[1];
		case ADC_CHANNEL_3: return dma->adc_values[2];
		case ADC_CHANNEL_12: return dma->adc_values[3];
		default: return 0;
	}

}

void direct_memory_access_restart(direct_memory_access* dma){
	if( dma == NULL ) return;
	HAL_ADC_Stop_DMA(dma->hadc);
	HAL_ADC_Start_DMA(dma->hadc, dma->adc_values, dma->number_channels);
}

// This function is based on a callback whenever the DMA reads from peripherals to memory
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

}
