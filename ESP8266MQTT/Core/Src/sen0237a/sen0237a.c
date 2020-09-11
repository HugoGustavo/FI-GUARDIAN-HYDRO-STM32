#include <sen0237a/sen0237a.h>

sen0237a* sen0237a_init(direct_memory_access* dma, uint32_t channel, char mode_calibration, char points_for_calibration, uint32_t voltage_point_1, uint8_t temperature_point_1, uint32_t voltage_point_2, uint8_t temperature_point_2, uint32_t current_temperature){
	sen0237a* result = (sen0237a*) malloc(sizeof(sen0237a));

	result->dma 						= dma;
	result->channel						= channel;
	result->mode_calibration			= mode_calibration;
	result->points_for_calibration		= points_for_calibration;

	result->voltage_point_1				= voltage_point_1;
	result->temperature_point_1			= temperature_point_1;

	result->voltage_point_2				= voltage_point_2;
	result->temperature_point_2			= temperature_point_2;

	result->current_temperature			= current_temperature;

	result->table_reference[0] = 14460;
	result->table_reference[1] = 14220;
	result->table_reference[2] = 13820;
	result->table_reference[3] = 13440;
	result->table_reference[4] = 13090;
	result->table_reference[5] = 12740;
	result->table_reference[6] = 12420;
	result->table_reference[7] = 12110;
	result->table_reference[8] = 11810;
	result->table_reference[9] = 11530;
	result->table_reference[10] = 11260;
	result->table_reference[11] = 11010;
	result->table_reference[12] = 10770;
	result->table_reference[13] = 10530;
	result->table_reference[14] = 10300;
	result->table_reference[15] = 10080;
	result->table_reference[16] = 9860;
	result->table_reference[17] = 9660;
	result->table_reference[18] = 9460;
	result->table_reference[19] = 9270;
	result->table_reference[20] = 9080;
	result->table_reference[21] = 8900;
	result->table_reference[22] = 8730;
	result->table_reference[23] = 8570;
	result->table_reference[24] = 8410;
	result->table_reference[25] = 8250;
	result->table_reference[25] = 8110;
	result->table_reference[27] = 7960;
	result->table_reference[28] = 7820;
	result->table_reference[29] = 7690;
	result->table_reference[30] = 7560;
	result->table_reference[31] = 7430;
	result->table_reference[32] = 7300;
	result->table_reference[33] = 7180;
	result->table_reference[34] = 7070;
	result->table_reference[35] = 6950;
	result->table_reference[36] = 6840;
	result->table_reference[37] = 6730;
	result->table_reference[38] = 6630;
	result->table_reference[39] = 6530;
	result->table_reference[40] = 6410;

	return result;
}

void sen0237a_destroy(sen0237a* sen0237a){
	if( sen0237a == NULL ) return;
	sen0237a->dma = NULL;
	free(sen0237a);
	sen0237a = NULL;
}

uint32_t sen0237a_get_channel(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->channel;
}

void sen0237a_set_channel(sen0237a* sen0237a, uint32_t channel){
	if( sen0237a == NULL ) return;
	sen0237a->channel = channel;
}

char sen0237a_get_mode_calibration(sen0237a* sen0237a){
	return sen0237a == NULL ? 0x00 : sen0237a->mode_calibration;
}

void sen0237a_set_mode_calibration(sen0237a* sen0237a, char mode_calibration){
	sen0237a->mode_calibration = mode_calibration;
}

char sen0237a_get_points_for_calibration(sen0237a* sen0237a){
	return sen0237a == NULL ? 0x00 : sen0237a->points_for_calibration;
}

void sen0237a_set_points_for_calibration(sen0237a* sen0237a, char points_for_calibration){
	sen0237a->points_for_calibration = points_for_calibration;
}

float sen0237a_get_voltage_point_1(sen0237a* sen0237a){
	return sen0237a == NULL ? 0.0f : sen0237a->voltage_point_1;
}

void sen0237a_set_voltage_point_1(sen0237a* sen0237a, float voltage_point_1){
	if( sen0237a == NULL ) return;
	sen0237a->voltage_point_1 = voltage_point_1;
}

uint8_t sen0237a_get_temperature_point_1(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->temperature_point_1;
}

void sen0237a_set_temperature_point_1(sen0237a* sen0237a, uint8_t temperature_point_1){
	if( sen0237a == NULL ) return;
	sen0237a->temperature_point_1 = temperature_point_1;
}

float sen0237a_get_voltage_point_2(sen0237a* sen0237a){
	return sen0237a == NULL ? 0.0f : sen0237a->voltage_point_1;
}

void sen0237a_set_voltage_point_2(sen0237a* sen0237a, float voltage_point_2){
	if( sen0237a == NULL ) return;
	sen0237a->voltage_point_2 = voltage_point_2;
}

uint8_t sen0237a_get_temperature_point_2(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->temperature_point_1;
}

void sen0237a_set_temperature_point_2(sen0237a* sen0237a, uint8_t temperature_point_2){
	if( sen0237a == NULL ) return;
	sen0237a->temperature_point_2 = temperature_point_2;
}

uint32_t sen0237a_get_current_temperature(sen0237a* sen0237a){
	return sen0237a == NULL ? 0 : sen0237a->current_temperature;
}

void sen0237a_set_temperature(sen0237a* sen0237a, uint32_t current_temperature){
	if( sen0237a == NULL ) return;
	sen0237a->current_temperature = current_temperature;
}


direct_memory_access* sen0237a_get_dma(sen0237a* sen0237a){
	return sen0237a == NULL ? NULL : sen0237a->dma;
}

void sen0237a_set_dma(sen0237a* sen0237a, direct_memory_access* dma){
	if( sen0237a == NULL ) return;
	sen0237a->dma = dma;
}

float sen0237a_read(sen0237a* sen0237a){
	if ( sen0237a->mode_calibration != 0x00 ){
		float adc_raw = direct_memory_access_get_adc_value(sen0237a->dma, sen0237a->channel);
		float result = adc_raw * ( 3300.0 / 4096.0 );
		return result;
	}

	char points_for_calibration = sen0237a->points_for_calibration;
	uint8_t current_temperature = sen0237a_get_current_temperature(sen0237a);
	float adc_raw = direct_memory_access_get_adc_value(sen0237a->dma, sen0237a->channel);
	float adc_voltage = adc_raw * ( 3300.0 / 4096.0 );

	uint16_t saturation = 0;
	if( points_for_calibration == 0x01 ){
		saturation = (uint32_t) sen0237a->voltage_point_1 + ( (uint32_t) 35 * current_temperature ) - ( (uint32_t) sen0237a->temperature_point_1 * 35 );
	} else if ( points_for_calibration == 0x02 ){
		saturation = (int16_t)( (int8_t)current_temperature - sen0237a->temperature_point_2) * ( (uint16_t)sen0237a->voltage_point_1 - sen0237a->voltage_point_2 ) / ( (uint8_t)sen0237a->temperature_point_1 - sen0237a->temperature_point_2 ) + sen0237a->voltage_point_2;
	}

	uint16_t do_reference = sen0237a->table_reference[current_temperature];
	float result = (adc_voltage * do_reference / saturation);

	return result;
}
