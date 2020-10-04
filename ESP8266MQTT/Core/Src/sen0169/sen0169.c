#include <sen0169/sen0169.h>

sen0169* sen0169_init(direct_memory_access* dma, uint32_t channel){
	sen0169* result 	= (sen0169*) malloc(sizeof(sen0169));
	result->channel 	= channel;
	for(register int i = 0; i < 12; i++) result->readings[i] = 0;
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

unsigned int* sen0169_get_readings(sen0169* sen0169){
	return sen0169 == NULL ? NULL : sen0169->readings;
}

void sen0169_set_readings(sen0169* sen0169, unsigned int readings[]){
	if( sen0169 == NULL ) return;
	for(register int i = 0; i < 12; i++)
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

	/******************************** Find the linear coefficients ********************************************
		float ph_1 = 1.0;
		float voltage_1 = 4.5602;
		float ph_2 = 13.0;
		float voltage_2 = 4.4621;
		float alpha = (ph_1 - ph_2) / ( voltage_1 - voltage_2 );
		float beta = ph_1 - ( alpha*voltage_1 );
	**********************************************************************************************************/

	float raw_adc = direct_memory_access_get_adc_value(sen0169->dma, sen0169->channel);
	sen0169->readings[sen0169->index] = raw_adc;
	sen0169->index = (sen0169->index + 1) % 12;

	float voltage 	= sen0169_average(sen0169)* 5.0 / 4096.0;
	float alpha 	= -122.323929;
	float beta 		= 558.821594;

	return alpha * voltage + beta;
}

float sen0169_average(sen0169* sen0169){
	if( sen0169 == NULL ) return 0.0;

	unsigned int amount = 0;
	unsigned int count = 0;
	unsigned int maximum, minimum;

	if( sen0169->readings[0] < sen0169->readings[1] ){
		minimum = sen0169->readings[0]; maximum = sen0169->readings[1];
	} else {
		minimum = sen0169->readings[1]; maximum = sen0169->readings[0];
	}

	for(register unsigned int i=2; i < 12; i++){
		if( sen0169->readings[i] == 0 ) continue;

		if( sen0169->readings[i] < minimum ) {
			amount += minimum; minimum = sen0169->readings[i];
	    } else if( sen0169->readings[i] > maximum ) {
	    	amount += maximum; maximum = sen0169->readings[i];
	    } else {
		    amount += sen0169->readings[i];
	    }
		count++;
	}

	float average = count == 0 ? 0 : (float) ( amount / count );
	return average;
}



