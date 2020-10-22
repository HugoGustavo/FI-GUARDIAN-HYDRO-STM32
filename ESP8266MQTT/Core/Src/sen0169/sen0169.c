#include <sen0169/sen0169.h>

sen0169* sen0169_init(uint32_t channel){
	sen0169* result 	= (sen0169*) malloc(sizeof(sen0169));
	result->channel 	= channel;
	for(register int i = 0; i < 12; i++) result->readings[i] = 0;
	result->index 		= 0;
	return result;
}

void sen0169_destroy(sen0169* sen0169){
	if( sen0169 == NULL ) return;
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

float sen0169_read(sen0169* sen0169){
	if( sen0169 == NULL ) return 0.0;

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

	float raw_adc = stm32_util_read_analog(sen0169->channel);
	sen0169->readings[sen0169->index] = raw_adc;
	float voltagem 	= sen0169_average(sen0169) * 5.0 / 4096.0;
	sen0169->index = (sen0169->index + 1) % 12;

	// Utilizou-se ajuste de lagrange
	float a0 = +1.00000000;
	float a1 = +4.46371788;
	float a2 = -0.35719982;
	float ph = a0 + ( a1 * voltagem ) + ( a2 * pow(voltagem, 2) );

	return ph;
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



