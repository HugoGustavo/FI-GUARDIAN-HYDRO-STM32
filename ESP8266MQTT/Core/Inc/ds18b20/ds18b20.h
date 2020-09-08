#ifndef DS18B20_H
#define DS18B20_H

#include <stdio.h>
#include <stdlib.h>
#include <stm32l433xx.h>
#include <util/stm32_util.h>
#include <util/dwt_delay.h>

typedef struct __attribute__((__packed__)) ds18b20 {
	GPIO_TypeDef* 	port;
	uint16_t 		pin;
} ds18b20;

ds18b20* ds18b20_init(GPIO_TypeDef* port, uint16_t pin);

void ds18b20_destroy(ds18b20* ds18b20);

uint8_t dsb18b20_is_presence(ds18b20* ds18b20);

void ds18b20_write(ds18b20* ds18b20, uint8_t data);

float ds18b20_read(ds18b20* ds18b20);

#endif
