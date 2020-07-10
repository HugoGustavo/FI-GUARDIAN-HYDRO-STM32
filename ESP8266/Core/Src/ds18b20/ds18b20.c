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
	HAL_Delay(480);
	stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
	HAL_Delay(80);

	uint8_t result = 0;
	if( ! HAL_GPIO_ReadPin(ds18b20->port, ds18b20->pin) ) result = 1;
	HAL_Delay(400);
	return result;

}

void ds18b20_write(ds18b20* ds18b20, uint8_t data){
	if( ds18b20 == NULL ) return;

	stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
	for (int i=0; i<8; i++){
		if ( (data & (1<<i)) != 0 ){
			stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
			HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
			HAL_Delay(1);
			stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
			HAL_Delay(50);
		} else {
			stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
			HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
			HAL_Delay(50);
			stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
		}
	}
}

float ds18b20_read(ds18b20* ds18b20){
	if( ds18b20 == NULL ) return 0;

	dsb18b20_is_presence(ds18b20);
	HAL_Delay(1);
	ds18b20_write(ds18b20, 0xCC);
	ds18b20_write(ds18b20, 0x44);
	HAL_Delay(800);

	dsb18b20_is_presence(ds18b20);
	HAL_Delay(1);
	ds18b20_write(ds18b20, 0xCC);
	ds18b20_write(ds18b20, 0xBE);

	uint8_t value[] = {0,0};
	stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
	for(int j = 0; j < 2; j++){
		for (int i=0; i<8; i++){
			stm32_util_set_pin_output(ds18b20->port, ds18b20->pin);
			HAL_GPIO_WritePin(ds18b20->port, ds18b20->pin, 0);
			HAL_Delay(2);
			stm32_util_set_pin_input(ds18b20->port, ds18b20->pin);
			if (HAL_GPIO_ReadPin(ds18b20->port, ds18b20->pin)) value[j] |= 1<<i;
			HAL_Delay(60);
		}
	}
	float result =  ((value[1] << 8) | value[0]) / 16.0;
	return result;
}

void ds18b20_delay(uint32_t us){
	hw_time_sleep(us);
}
