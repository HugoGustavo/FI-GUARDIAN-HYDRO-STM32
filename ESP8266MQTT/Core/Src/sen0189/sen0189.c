#include <sen0189/sen0189.h>

sen0189* sen0189_init(uint32_t channel){
	sen0189* result = (sen0189*) malloc(sizeof(sen0189));
	result->channel = channel;
	return result;
}

void sen0189_destroy(sen0189* sen0189){
	if( sen0189 == NULL ) return;
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

float sen0189_read(sen0189* sen0189){
	if( sen0189 == NULL ) return 0.0;

	float raw_adc = stm32_util_read_analog(sen0189->channel);
	return raw_adc * 5.0 / 4096.0;

	float voltage = stm32_util_read_analog(sen0189->channel) * ( 5000.0 / 4096.0 );
	return voltage / 1000;
    voltage = voltage > 3004.74 ? 3004.74 : voltage;

    float sensor_value = sqrtf(1346605265-448160*voltage);
	sensor_value = (sensor_value / 22408.0) + (57423.0/22408.0);

	return sensor_value;
}
