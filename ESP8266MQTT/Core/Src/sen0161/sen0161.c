#include <sen0161/sen0161.h>

sen0161* sen0161_init(direct_memory_access* dma, uint32_t channel, float offset){
	sen0161* result = (sen0161*) malloc(sizeof(sen0161));
	result->channel = channel;
	result->offset = offset;
	for(register int i = 0; i < 12; i++) result->readings[i] = 0;
	result->index = 0;
	result->dma = dma;
	return result;
}

void sen0161_destroy(sen0161* sen0161){
	if( sen0161 == NULL ) return;
	sen0161->dma = NULL;
	free(sen0161);
	sen0161 = NULL;
}

uint32_t sen0161_get_channel(sen0161* sen0161){
	return sen0161 == NULL ? 0 : sen0161->channel;
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
	for(register int i = 0; i < 12; i++)
		sen0161->readings[i] = readings[i];
}

unsigned int sen0161_get_index(sen0161* sen0161){
	return sen0161 == NULL ? 0 : sen0161->index;
}

void sen0161_set_index(sen0161* sen0161, const unsigned int index){
	if( sen0161 == NULL ) return;
	sen0161->index = index;
}

direct_memory_access* sen0161_get_dma(sen0161* sen0161){
	return sen0161 == NULL ? NULL : sen0161->dma;
}

void sen0161_set_dma(sen0161* sen0161, direct_memory_access* dma){
	if( sen0161 == NULL ) return;
	sen0161->dma = dma;
}

float sen0161_read(sen0161* sen0161){
	if( sen0161 == NULL ) return 0.0;

	float raw_adc = direct_memory_access_get_adc_value(sen0161->dma, sen0161->channel) ;
	sen0161->readings[sen0161->index] = raw_adc;
	sen0161->index = ( sen0161->index + 1 ) % 12;

	float phValue = 3.5 * ( sen0161_average(sen0161) * 5.0 / 4096.0 ) + sen0161->offset;
	return phValue;
}

float sen0161_average(sen0161* sen0161){
	if( sen0161 == NULL ) return 0.0;

	long amount = 0;
	if( sen0161->index < 5 ){
		for(register unsigned int i = 0; i < sen0161->index; i++ ){
			amount += sen0161->readings[i];
		}
		return (float) (amount / sen0161->index);
	}

	unsigned int maximum, minimum;
	if( sen0161->readings[0] < sen0161->readings[1] ){
		minimum = sen0161->readings[0]; maximum = sen0161->readings[1];
	} else {
		minimum = sen0161->readings[1]; maximum = sen0161->readings[0];
	}

	for(register unsigned int i=2; i < sen0161->index; i++){
		if( sen0161->readings[i] < minimum) {
			amount += minimum; minimum = sen0161->readings[i];
	    } else if( sen0161->readings[i] > maximum ) {
	    	amount += maximum; maximum = sen0161->readings[i];
	    } else {
		    amount += sen0161->readings[i];
	    }
	}

	float average = (float) ( amount / (sen0161->index-2) );
	return average;
}
