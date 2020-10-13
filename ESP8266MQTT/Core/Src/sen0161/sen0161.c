#include <sen0161/sen0161.h>

sen0161* sen0161_init(uint32_t channel){
	sen0161* result = (sen0161*) malloc(sizeof(sen0161));
	result->channel = channel;
	for(register int i = 0; i < 12; i++) result->readings[i] = 0;
	result->index = 0;
	return result;
}

void sen0161_destroy(sen0161* sen0161){
	if( sen0161 == NULL ) return;
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

float sen0161_read(sen0161* sen0161){
	if( sen0161 == NULL ) return 0.0;

	/******************************** Find the linear coefficients ********************************************
		float ph_1 = 1.0;
		float voltage_1 = 4.5602;
		float ph_2 = 13.0;
		float voltage_2 = 4.4621;
		float alpha = (ph_1 - ph_2) / ( voltage_1 - voltage_2 );
		float beta = ph_1 - ( alpha*voltage_1 );
	**********************************************************************************************************/

	float raw_adc = stm32_util_read_analog(sen0161->channel);
	return raw_adc * 5.0 / 4096.0;
	sen0161->readings[sen0161->index++] = raw_adc;
	sen0161->index = sen0161->index % 12;

	float voltage = sen0161_average(sen0161) * 5.0 / 4096.0;
	float alpha = -122.323929;
	float beta = 558.821594;

	return alpha * voltage + beta;
}

float sen0161_average(sen0161* sen0161){
	if( sen0161 == NULL ) return 0.0;

	unsigned int amount = 0;
	unsigned int count = 0;
	unsigned int maximum, minimum;

	if( sen0161->readings[0] < sen0161->readings[1] ){
		minimum = sen0161->readings[0]; maximum = sen0161->readings[1];
	} else {
		minimum = sen0161->readings[1]; maximum = sen0161->readings[0];
	}

	for(register unsigned int i=2; i < 12; i++){
		if( sen0161->readings[i] == 0 ) continue;

		if( sen0161->readings[i] < minimum ) {
			amount += minimum; minimum = sen0161->readings[i];
	    } else if( sen0161->readings[i] > maximum ) {
	    	amount += maximum; maximum = sen0161->readings[i];
	    } else {
		    amount += sen0161->readings[i];
	    }
		count++;
	}

	float average = count == 0 ? 0 : (float) ( amount / count );
	return average;
}
