#include <sen0165/sen0165.h>

sen0165* sen0165_init(direct_memory_access* dma, uint32_t channel, float offset){
	sen0165* result = (sen0165*) malloc(sizeof(sen0165));
	result->channel = channel;
	result->offset = offset;
	result->voltage = 3.3;
	for(register int i = 0; i < 40; i++) result->readings[i] = 0;
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

float sen0165_get_voltage(sen0165* sen0165){
	return sen0165 == NULL ? 0 : sen0165->voltage;
}

void sen0165_set_voltage(sen0165* sen0165, const float voltage){
	if( sen0165 == NULL ) return;
	sen0165->voltage = voltage;
}

unsigned int* sen0165_get_readings(sen0165* sen0165){
	return sen0165 == NULL ? NULL : sen0165->readings;
}

void sen0165_set_readings(sen0165* sen0165, unsigned int readings[]){
	if( sen0165 == NULL ) return;
	for(register int i = 0; i < 40; i++)
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
	unsigned int* readings = sen0165_get_readings(sen0165);
	readings[sen0165_get_index(sen0165)] = direct_memory_access_get_adc_value(sen0165_get_dma(sen0165), sen0165_get_channel(sen0165));
	sen0165_set_index(sen0165, ( sen0165_get_index(sen0165) + 1 ) % 40);
	float orpValue = ( ( 30 * sen0165_get_voltage(sen0165) * 1000 ) - ( 75 * sen0165_average(sen0165) * sen0165_get_voltage(sen0165) * 1000 / 4096.0 ) ) / ( 75 - sen0165_get_offset(sen0165) );
	return orpValue;
}

float sen0165_average(sen0165* sen0165){
	if( sen0165 == NULL ) return 0.0;

	unsigned int* readings = sen0165_get_readings(sen0165);
	unsigned int index = sen0165_get_index(sen0165);
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

	for(unsigned int i=2; i < index; i++){
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
