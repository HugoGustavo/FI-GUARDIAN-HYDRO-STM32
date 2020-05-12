#include <sen0165/sen0165.h>

sen0165* sen0165_init(ADC_HandleTypeDef* pin){
	sen0165* result = (sen0165*) malloc(sizeof(sen0165));
	result->pin = pin;
	result->offset = 0.00;
	result->readings = (unsigned int*) malloc(40*sizeof(unsigned int));
	for(int i = 0; i < 40; i++) result->readings[i] = 0;
	result->index = 0;
	return result;
}

void sen0165_destroy(sen0165* sen0165){
	if( sen0165 == NULL ) return;
	free(sen0165);
	sen0165 = NULL;
}

ADC_HandleTypeDef* sen0165_get_pin(sen0165* sen0165){
	return sen0165 == NULL ? NULL : sen0165->pin;
}

void sen0165_set_pin(sen0165* sen0165, ADC_HandleTypeDef* pin){
	if( sen0165 == NULL ) return;
	sen0165->pin = pin;
}

float sen0165_get_offset(sen0165* sen0165){
	return sen0165 == NULL ? 0 : sen0165->offset;
}

void sen0165_set_offset(sen0165* sen0165, const float offset){
	if( sen0165 == NULL ) return;
	sen0165->offset = offset;
}

unsigned int* sen0165_get_readings(sen0165* sen0165){
	return sen0165 == NULL ? NULL : sen0165->readings;
}

void sen0165_set_readings(sen0165* sen0165, unsigned int* readings){
	if( sen0165 == NULL ) return;
	sen0165->readings = readings;
}

unsigned int sen0165_get_index(sen0165* sen0165){
	return sen0165 == NULL ? 0 : sen0165->index;
}

void sen0165_set_index(sen0165* sen0165, const unsigned int index){
	if( sen0165 == NULL ) return;
	sen0165->index = index;
}

float sen0165_read(sen0165* sen0165){
	if( sen0165 == NULL ) return 0.0;
	unsigned int* readings = sen0165_get_readings(sen0165);
	readings[sen0165_get_index(sen0165)] = stm32_util_read_analog(sen0165_get_pin(sen0165));
	sen0165_set_index(sen0165, ( sen0165_get_index(sen0165) + 1 ) % 40);
	float orpValue = ((30*(double)5.00*1000)-(75*sen0165_average(sen0165)*5.00*1000/1024))/75-sen0165_get_offset(sen0165);
	return orpValue;
}

float sen0165_average(sen0165* sen0165){
	if ( sen0165 == NULL ) return 0.0;

	unsigned int maximum, minimum;
	unsigned int* readings = sen0165_get_readings(sen0165);
	if( readings[0] < readings[1] ){
		minimum = readings[0]; maximum = readings[1];
	} else {
		minimum = readings[1]; maximum = readings[0];
	}

	int i;
	long amount = 0;
	for(i=2; i < sen0165_get_index(sen0165); i++){
		if( readings[i] < minimum) {
			amount += minimum; minimum = readings[i];
	    } else if( readings[i] > maximum ) {
	    	amount += maximum; maximum = readings[i];
	    } else {
	    	amount += readings[i];
	    }
	}

	float average = (float) amount / sen0165_get_index(sen0165);
	return average;
}
