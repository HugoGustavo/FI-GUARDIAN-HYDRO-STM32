#include <sen0165/sen0165.h>

sen0165* sen0165_init(direct_memory_access* dma, uint32_t channel, float offset){
	sen0165* result = (sen0165*) malloc(sizeof(sen0165));
	result->channel = channel;
	result->offset = offset;
	for(register int i = 0; i < 12; i++) result->readings[i] = 0;
	result->index = 0;
	result->dma = dma;
	return result;
}

void sen0165_destroy(sen0165* sen0165){
	if( sen0165 == NULL ) return;
	sen0165->dma = NULL;
	free(sen0165);
	sen0165 = NULL;
}

uint32_t sen0165_get_channel(sen0165* sen0165){
	return sen0165 == NULL ? 0 : sen0165->channel;
}

void sen0165_set_channel(sen0165* sen0165, uint32_t channel){
	if( sen0165 == NULL ) return;
	sen0165->channel = channel;
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

void sen0165_set_readings(sen0165* sen0165, unsigned int readings[]){
	if( sen0165 == NULL ) return;
	for(register int i = 0; i < 12; i++)
		sen0165->readings[i] = readings[i];
}

unsigned int sen0165_get_index(sen0165* sen0165){
	return sen0165 == NULL ? 0 : sen0165->index;
}

void sen0165_set_index(sen0165* sen0165, const unsigned int index){
	if( sen0165 == NULL ) return;
	sen0165->index = index;
}

direct_memory_access* sen0165_get_dma(sen0165* sen0165){
	return sen0165 == NULL ? NULL : sen0165->dma;
}

void sen0165_set_dma(sen0165* sen0165, direct_memory_access* dma){
	if( sen0165 == NULL ) return;
	sen0165->dma = dma;
}

float sen0165_read(sen0165* sen0165){
	if( sen0165 == NULL ) return 0.0;

	float raw_adc = direct_memory_access_get_adc_value(sen0165->dma, sen0165->channel) ;
	sen0165->readings[sen0165->index] = raw_adc;
	sen0165->index = ( sen0165->index + 1 ) % 12;

	float orpValue = ( ( 30 * 5.0 * 1000 ) - ( 75 * sen0165_average(sen0165) * 5.0 * 1000 / 4096.0 ) ) / 75 + sen0165->offset;
	return orpValue;
}

float sen0165_average(sen0165* sen0165){
	if( sen0165 == NULL ) return 0.0;

	long amount = 0;
	if( sen0165->index < 5 ){
		for(register unsigned int i = 0; i < sen0165->index; i++ ){
			amount += sen0165->readings[i];
		}
		return (float) (amount / sen0165->index);
	}

	unsigned int maximum, minimum;
	if( sen0165->readings[0] < sen0165->readings[1] ){
		minimum = sen0165->readings[0]; maximum = sen0165->readings[1];
	} else {
		minimum = sen0165->readings[1]; maximum = sen0165->readings[0];
	}

	for(register unsigned int i=2; i < sen0165->index; i++){
		if( sen0165->readings[i] < minimum) {
			amount += minimum; minimum = sen0165->readings[i];
	    } else if( sen0165->readings[i] > maximum ) {
	    	amount += maximum; maximum = sen0165->readings[i];
	    } else {
		    amount += sen0165->readings[i];
	    }
	}

	float average = (float) ( amount / (sen0165->index-2) );
	return average;
}
