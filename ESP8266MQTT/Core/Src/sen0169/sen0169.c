#include <sen0169/sen0169.h>

sen0169* sen0169_init(direct_memory_access* dma, uint32_t channel, float offset){
	sen0169* result 	= (sen0169*) malloc(sizeof(sen0169));
	result->channel 	= channel;
	result->offset 		= offset;
	for(register int i = 0; i < 40; i++) result->readings[i] = 0;
	result->index 		= 0;
	result->dma 		= dma;
	return result;
}

void sen0169_destroy(sen0169* sen0169){
	if( sen0169 == NULL ) return;
	sen0169->dma = NULL;
	free(sen0169);
	sen0169 = NULL;
}

uint32_t sen0169_get_channel(sen0169* sen0169){
	return sen0169 == NULL ? 0 : sen0169->channel;
}

void sen0169_set_channel(sen0169* sen0169, uint32_t channel){
	if( sen0169 == NULL ) return;
	sen0169->channel = channel;
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

void sen0169_set_readings(sen0169* sen0169, unsigned int readings[]){
	if( sen0169 == NULL ) return;
	for(register int i = 0; i < 30; i++)
		sen0169->readings[i] = readings[i];
}

unsigned int sen0169_get_index(sen0169* sen0169){
	return sen0169 == NULL ? 0 : sen0169->index;
}

void sen0169_set_index(sen0169* sen0169, const unsigned int index){
	if( sen0169 == NULL ) return;
	sen0169->index = index;
}

direct_memory_access* sen0169_get_dma(sen0169* sen0169){
	return sen0169 == NULL ? NULL : sen0169->dma;
}

void sen0169_set_dma(sen0169* sen0169, direct_memory_access* dma){
	if( sen0169 == NULL ) return;
	sen0169->dma = dma;
}

float sen0169_read(sen0169* sen0169){
	if( sen0169 == NULL ) return 0.0;
	unsigned int* readings = sen0169_get_readings(sen0169);
	readings[sen0169_get_index(sen0169)] = direct_memory_access_get_adc_value(sen0169_get_dma(sen0169), sen0169_get_channel(sen0169));
	sen0169_set_index(sen0169, ( sen0169_get_index(sen0169) + 1 ) % 40);
	float phValue = 3.5 * ( sen0169_average(sen0169) * 3.3 / 4096.0 ) + sen0169_get_offset(sen0169);
	return phValue;
}

float sen0169_average(sen0169* sen0169){
	if( sen0169 == NULL ) return 0.0;

	unsigned int* readings = sen0169_get_readings(sen0169);
	unsigned int index = sen0169_get_index(sen0169);
	long amount = 0;

	if( index < 5 ){
		for(register unsigned int i = 0; i < index; i++ ){
			amount += readings[i];
		}
		return (float) (amount / index);
	}

	unsigned int maximum, minimum;
	if( readings[0] < readings[1] ){
		minimum = readings[0]; maximum = readings[1];
	} else {
		minimum = readings[1]; maximum = readings[0];
	}

	for(register unsigned int i=2; i < index; i++){
		if( readings[i] < minimum) {
			amount += minimum; minimum = readings[i];
	    } else if( readings[i] > maximum ) {
	    	amount += maximum; maximum = readings[i];
	    } else {
		    amount += readings[i];
	    }
	}

	float average = (float) ( amount / (index-2) );
	return average;
}



