#include <sen0169/sen0169.h>

sen0169* sen0169_init(ADC_HandleTypeDef* pin){
	sen0169* result = (sen0169*) malloc(sizeof(sen0169));
	result->pin = pin;
	result->offset = 0.00;
	result->readings = (unsigned int*) malloc(40*sizeof(unsigned int));
	for(int i = 0; i < 40; i++) result->readings[i] = 0;
	result->index = 0;
	return result;
}

void sen0169_destroy(sen0169* sen0169){
	if( sen0169 == NULL ) return;
	free(sen0169);
	sen0169 = NULL;
}

ADC_HandleTypeDef* sen0169_get_pin(sen0169* sen0169){
	return sen0169 == NULL ? NULL : sen0169->pin;
}

void sen0169_set_pin(sen0169* sen0169, ADC_HandleTypeDef* pin){
	if( sen0169 == NULL ) return;
	sen0169->pin = pin;
}

float sen0169_get_offset(sen0169* sen0169){
	return sen0169 == NULL ? 0 : sen0169->offset;
}

void sen0169_set_offset(sen0169* sen0169, const float offset){
	if( sen0169 == NULL ) return;
	sen0169->offset = offset;
}

unsigned int* sen0169_get_readings(sen0169* sen0169){
	return sen0169 == NULL ? NULL : sen0169->readings;
}

void sen0169_set_readings(sen0169* sen0169, unsigned int* readings){
	if( sen0169 == NULL ) return;
	sen0169->readings = readings;
}

unsigned int sen0169_get_index(sen0169* sen0169){
	return sen0169 == NULL ? 0 : sen0169->index;
}

void sen0169_set_index(sen0169* sen0169, const unsigned int index){
	if( sen0169 == NULL ) return;
	sen0169->index = index;
}

float sen0169_read(sen0169* sen0169){
	if( sen0169 == NULL ) return 0.0;
	unsigned int* readings = sen0169_get_readings(sen0169);
	readings[sen0169_get_index(sen0169)] = stm32_util_read_analog(sen0169_get_pin(sen0169));
	sen0169_set_index(sen0169, ( sen0169_get_index(sen0169) + 1 ) % 40);
	float phValue = 3.5*(sen0169_average(sen0169)*5.0/1024) + sen0169_get_offset(sen0169);
	return phValue;
}

float sen0169_average(sen0169* sen0169){
	if ( sen0169 == NULL ) return 0.0;

	unsigned int maximum, minimum;
	unsigned int* readings = sen0169_get_readings(sen0169);
	if( readings[0] < readings[1] ){
		minimum = readings[0]; maximum = readings[1];
	} else {
		minimum = readings[1]; maximum = readings[0];
	}

	int i;
	long amount = 0;
	for(i=2; i < sen0169_get_index(sen0169); i++){
		if( readings[i] < minimum) {
			amount += minimum; minimum = readings[i];
	    } else if( readings[i] > maximum ) {
	    	amount += maximum; maximum = readings[i];
	    } else {
	    	amount += readings[i];
	    }
	}

	float average = (float) amount / sen0169_get_index(sen0169);
	return average;
}



