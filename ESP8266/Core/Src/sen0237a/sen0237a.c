#include <sen0237a/sen0237a.h>

sen0237a* sen0237a_init(ADC_HandleTypeDef* pin, uint32_t channel, bool mode_calibration){
	sen0237a* result = (sen0237a*) malloc(sizeof(sen0237a));

	result->pin 							= pin;
	result->channel						= channel;
	result->mode_calibration 			= mode_calibration;
	result->saturation_do_voltage 		= 1127.6;
	result->saturation_do_temperature 	= 25.0;
	result->average_voltage 				= 0.0;
	result->temperature 					= 0.0;
	result->index						= 0;

	for(int i = 0; i < 30; i++) result->readings[i] = 0;

	return result;
}

void sen0237a_destroy(sen0237a* sen0237a){
	if( sen0237a == NULL ) return;
	free(sen0237a);
	sen0237a = NULL;
}

bool sen0237a_is_mode_calibration(sen0237a* sen0237a){
	return sen0237a == NULL ? false : sen0237a->mode_calibration;
}

void sen0237a_set_mode_calibration(sen0237a* sen0237a, bool mode_calibration){
	if( sen0237a == NULL ) return;
	sen0237a->mode_calibration = mode_calibration;
}

unsigned int sen0237a_get_saturation_do_voltage(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->saturation_do_voltage;
}

void sen0237a_set_saturation_do_voltage(sen0237a* sen0237a, unsigned int saturation_do_voltage){
	if( sen0237a == NULL ) return;
	sen0237a->saturation_do_voltage = saturation_do_voltage;
}

unsigned int sen0237a_get_saturation_do_temperature(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->saturation_do_temperature;
}

void sen0237a_set_saturation_do_temperature(sen0237a* sen0237a, unsigned int saturation_do_temperature){
	if( sen0237a == NULL ) return;
	sen0237a->saturation_do_temperature = saturation_do_temperature;
}

float sen0237a_get_average_voltage(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->average_voltage;
}

void sen0237a_set_average_voltage(sen0237a* sen0237a, float average_voltage){
	if( sen0237a == NULL ) return;
	sen0237a->average_voltage = average_voltage;
}

float sen0237a_get_temperature(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->temperature;
}

void sen0237a_set_temperature(sen0237a* sen0237a, float temperature){
	if( sen0237a == NULL ) return;
	sen0237a->temperature = temperature;
}

ADC_HandleTypeDef* sen0237a_get_pin(sen0237a* sen0237a){
	return sen0237a == NULL ? NULL : sen0237a->pin;
}

uint32_t sen0237a_get_channel(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->pin;
}

void sen0237a_set_channel(sen0237a* sen0237a, uint32_t channel){
	if( sen0237a == NULL ) return;
	sen0237a->channel = channel;
}

void sen0237a_set_pin(sen0237a* sen0237a, ADC_HandleTypeDef* pin){
	if( sen0237a == NULL ) return;
	sen0237a->pin = pin;
}

int* sen0237a_get_readings(sen0237a* sen0237a){
	return sen0237a == NULL ? NULL : sen0237a->readings;
}

void sen0237a_set_readings(sen0237a* sen0237a, int readings[]){
	if( sen0237a == NULL ) return;
	for(int i = 0; i < 30; i++)
		sen0237a->readings[i] = readings[i];
}

int sen0237a_get_index(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->index;
}

void sen0237a_set_index(sen0237a* sen0237a, int index){
	if( sen0237a == NULL ) return;
	sen0237a->index = index;
}

float sen0237a_read(sen0237a* sen0237a){
	if ( ! sen0237a_is_mode_calibration(sen0237a) ){
		int index = sen0237a_get_index(sen0237a);
		int* readings = sen0237a_get_readings(sen0237a);
		readings[index] = stm32_util_read_analog(sen0237a_get_pin(sen0237a), sen0237a_get_channel(sen0237a));
		sen0237a_set_index(sen0237a, (index + 1 ) % 30);
		sen0237a_set_average_voltage(sen0237a, sen0237a_median(sen0237a) * (float) 5000 / 1024.0);
		float dissolved_oxygen_value = ( SEN0237A_SATURATION_VALUE + (int)(sen0237a_get_saturation_do_temperature(sen0237a)+0.5) ) * sen0237a_get_average_voltage(sen0237a) / sen0237a_get_saturation_do_voltage(sen0237a);
		return dissolved_oxygen_value;
	} else {
		sen0237a_do_calibration(sen0237a);
		return 0.0;
	}
}

void sen0237a_do_calibration(sen0237a* sen0237a){
	// Not implemented yet
}

int sen0237a_median(sen0237a* sen0237a){
	int readings_temp[30];
	int* readings = sen0237a_get_readings(sen0237a);
	for(int i = 0; i < 30; i++) readings_temp[i] = readings[i];

	// Ordering for calculating the median
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30 - 1; j++){
			if ( readings_temp[j] > readings_temp[j+1] ){
				int aux = readings_temp[j];
				readings_temp[j] = readings_temp[j+1];
				readings_temp[j+1] = aux;
			}
		}
	}

	int median = ( readings_temp[14] + readings_temp[15]) / 2;

	return median;
}
