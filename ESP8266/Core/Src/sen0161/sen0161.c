#include <sen0161/sen0161.h>

sen0161* sen0161_init(ADC_HandleTypeDef* pin, uint32_t channel){
	sen0161* result = (sen0161*) malloc(sizeof(sen0161));
	result->pin = pin;
	result->channel = channel;
	result->offset = 0.00;
	for(int i = 0; i < 40; i++) result->readings[i] = 0;
	result->index = 0;
	return result;
}

void sen0161_destroy(sen0161* sen0161){
	if( sen0161 == NULL ) return;
	free(sen0161);
	sen0161 = NULL;
}

ADC_HandleTypeDef* sen0161_get_pin(sen0161* sen0161){
	return sen0161 == NULL ? NULL : sen0161->pin;
}

void sen0161_set_pin(sen0161* sen0161, ADC_HandleTypeDef* pin){
	if( sen0161 == NULL ) return;
	sen0161->pin = pin;
}

uint32_t sen0161_get_channel(sen0161* sen0161){
	return sen0161 == NULL ? 0 : sen0161->pin;
}

void sen0161_set_channel(sen0161* sen0161, uint32_t channel){
	if( sen0161 == NULL ) return;
	sen0161->channel = channel;
}

float sen0161_get_offset(sen0161* sen0161){
	return sen0161 == NULL ? 0 : sen0161->offset;
}

void sen0161_set_offset(sen0161* sen0161, const float offset){
	if( sen0161 == NULL ) return;
	sen0161->offset = offset;
}

unsigned int* sen0161_get_readings(sen0161* sen0161){
	return sen0161 == NULL ? NULL : sen0161->readings;
}

void sen0161_set_readings(sen0161* sen0161, unsigned int readings[]){
	if( sen0161 == NULL ) return;
	for(int i = 0; i < 40; i++)
		sen0161->readings[i] = readings[i];
}

unsigned int sen0161_get_index(sen0161* sen0161){
	return sen0161 == NULL ? 0 : sen0161->index;
}

void sen0161_set_index(sen0161* sen0161, const unsigned int index){
	if( sen0161 == NULL ) return;
	sen0161->index = index;
}

float sen0161_read(sen0161* sen0161){
	if( sen0161 == NULL ) return 0.0;
	unsigned int* readings = sen0161_get_readings(sen0161);
	readings[sen0161_get_index(sen0161)] = stm32_util_read_analog(sen0161_get_pin(sen0161), sen0161_get_channel(sen0161));
	sen0161_set_index(sen0161, ( sen0161_get_index(sen0161) + 1 ) % 40);
	float phValue = 3.5*(sen0161_average(sen0161)*5.0/1024) + sen0161_get_offset(sen0161);
	return phValue;
}

float sen0161_average(sen0161* sen0161){
	if ( sen0161 == NULL ) return 0.0;

	unsigned int maximum, minimum;
	unsigned int* readings = sen0161_get_readings(sen0161);
	if( readings[0] < readings[1] ){
		minimum = readings[0]; maximum = readings[1];
	} else {
		minimum = readings[1]; maximum = readings[0];
	}

	int i;
	long amount = 0;
	for(i=2; i < sen0161_get_index(sen0161); i++){
		if( readings[i] < minimum) {
			amount += minimum; minimum = readings[i];
	    } else if( readings[i] > maximum ) {
	    	amount += maximum; maximum = readings[i];
	    } else {
	    	amount += readings[i];
	    }
	}

	float average = (float) amount / sen0161_get_index(sen0161);
	return average;
}
