#include<ds18b20/ds18b20.h>

ds18b20* ds18b20_init(GPIO_TypeDef* port, uint16_t pin){
	ds18b20* result = (ds18b20*) malloc(sizeof(ds18b20));
	result->port = port;
	result->pin = pin;
	return result;
}

uint8_t dsb18b20_is_presence(ds18b20* ds18b20){
	if( ds18b20 == NULL ) return 0;

	stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
	HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
	stm32_util_delay_in_microseconds(480);
	stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
	stm32_util_delay_in_microseconds(80);

	uint8_t result = 0;
	if( ! HAL_GPIO_ReadPin(ds18b20->port, ds18b20->pin) ) result = 1;
	stm32_util_delay_in_microseconds(400);
	return result;

}

void ds18b20_write(ds18b20* ds18b20, uint8_t data){
	if( ds18b20 == NULL ) return;

	stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
	for (int i=0; i<8; i++){
		if ( (data & (1<<i)) != 0 ){
			stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
			HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
			stm32_util_delay_in_microseconds(1);
			stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
			stm32_util_delay_in_microseconds(50);
		} else {
			stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
			HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
			stm32_util_delay_in_microseconds(50);
			stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
		}
	}
}

float ds18b20_read(ds18b20* ds18b20){
	if( ds18b20 == NULL ) return 0;

	dsb18b20_is_presence(ds18b20);
	stm32_util_delay_in_microseconds(1);
	ds18b20_write(ds18b20, 0xCC);
	ds18b20_write(ds18b20, 0x44);
	stm32_util_delay_in_microseconds(800);

	dsb18b20_is_presence(ds18b20);
	stm32_util_delay_in_microseconds(1);
	ds18b20_write(ds18b20, 0xCC);
	ds18b20_write(ds18b20, 0xBE);

	uint8_t value[] = {0,0};
	for(int j = 0; j < 2; j++){
		stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
		for (int i=0; i < 8; i++){
			stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
			HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
			stm32_util_delay_in_microseconds(2);
			stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
			if (HAL_GPIO_ReadPin(ds18b20->port, ds18b20->pin)) value[j] |= 1<<i;
			stm32_util_delay_in_microseconds(60);
		}
	}
	float result =  ( (value[1] << 8) | value[0] ) / 16.0;
	return result;
}
