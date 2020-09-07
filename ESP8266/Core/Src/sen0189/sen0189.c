#include <sen0189/sen0189.h>

sen0189* sen0189_init(direct_memory_access* dma, uint32_t channel){
	sen0189* result = (sen0189*) malloc(sizeof(sen0189));
	result->channel = channel;
	result->dma = dma;
	return result;
}

void sen0189_destroy(sen0189* sen0189){
	if( sen0189 == NULL ) return;
	sen0189->dma = NULL;
	free(sen0189);
	sen0189 = NULL;
}

uint32_t sen0189_get_channel(sen0189* sen0189){
	return sen0189 == NULL ? 0 : sen0189->channel;
}

void sen0189_set_channel(sen0189* sen0189, uint32_t channel){
	if( sen0189 == NULL ) return;
	sen0189->channel = channel;
}

direct_memory_access* sen0189_get_dma(sen0189* sen0189){
	return sen0189 == NULL ? NULL : sen0189->dma;
}

void sen0189_set_dma(sen0189* sen0189, direct_memory_access* dma){
	if( sen0189 == NULL ) return;
	sen0189->dma = dma;
}

float sen0189_read(sen0189* sen0189){
	if( sen0189 == NULL ) return 0.0;
	int sensor_value = direct_memory_access_get_adc_value(sen0189_get_dma(sen0189), sen0189_get_channel(sen0189));
	return sensor_value * ( 3.3 / 4096.0 );
}
