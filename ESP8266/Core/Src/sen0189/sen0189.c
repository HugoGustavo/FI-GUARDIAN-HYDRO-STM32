#include <sen0189/sen0189.h>

sen0189* sen0189_init(ADC_HandleTypeDef* pin, uint32_t channel){
	sen0189* result = (sen0189*) malloc(sizeof(sen0189));
	result->pin = pin;
	result->channel = channel;
	return result;
}

void sen0189_destroy(sen0189* sen0189){
	if( sen0189 == NULL ) return;
	free(sen0189);
	sen0189 = NULL;
}

ADC_HandleTypeDef* sen0189_get_pin(sen0189* sen0189){
	return sen0189 == NULL ? NULL : sen0189->pin;
}

void sen0189_set_pin(sen0189* sen0189, ADC_HandleTypeDef* pin){
	if( sen0189 == NULL ) return;
	sen0189->pin = pin;
}

uint32_t sen0189_get_channel(sen0189* sen0189){
	return sen0189 == NULL ? 0 : sen0189->pin;
}

void sen0189_set_channel(sen0189* sen0189, uint32_t channel){
	if( sen0189 == NULL ) return;
	sen0189->channel = channel;
}

float sen0189_read(sen0189* sen0189){
	if( sen0189 == NULL ) return 0.0;
	int sensor_value = stm32_util_read_analog(sen0189_get_pin(sen0189), sen0189_get_channel(sen0189));
	return sensor_value * (5.0 / 1024.0);
}
