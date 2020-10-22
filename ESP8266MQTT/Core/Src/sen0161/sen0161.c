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
		Placa sem bateria
		ph 01 = 0.00000000 V
		ph 07 = 1.06933594 V
		ph 14 = 4.67895508 V

		Placa com bateria

		ph 01 = 0 V
		ph 07 = 1.53198242 V
		ph 14 = 4.62158203 V

		Utilizou-se ajuste lagrange
	 **********************************************************************************************************/

	float raw_adc = stm32_util_read_analog(sen0161->channel);
	sen0161->readings[sen0161->index] = raw_adc;
	float voltagem 	= sen0161_average(sen0161) * 5.0 / 4096.0;
	sen0161->index = (sen0161->index + 1) % 12;

	// Utilizou-se ajuste de lagrange
	float a0 = +1.00000000;
	float a1 = +4.46371788;
	float a2 = -0.35719982;
	float ph = a0 + ( a1 * voltagem ) + ( a2 * pow(voltagem, 2) );

	return ph;
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
