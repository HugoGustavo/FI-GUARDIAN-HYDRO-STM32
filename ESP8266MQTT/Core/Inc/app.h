#ifndef INC_APP_H
#define INC_APP_H

#define RAND_MAX 0x7ff

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dma/direct_memory_access.h>
#include <stm32l4xx_hal.h>
#include <util/dwt_delay.h>
#include <esp8266/esp8266.h>
#include <ds18b20/ds18b20.h>
#include <sen0161/sen0161.h>
#include <sen0165/sen0165.h>
#include <sen0169/sen0169.h>
#include <sen0189/sen0189.h>
#include <view/init_screen.h>
#include <sen0237a/sen0237a.h>
#include <util/message_builder.h>
#include <mqtt_client/mqtt_client.h>
#include <configuration/properties.h>

void app_init(ADC_HandleTypeDef* hadc1);

void configure_init_screen(void);

void configure_delay(void);

void configure_ssd1306();

void configure_esp(void);

void configure_dma(ADC_HandleTypeDef* hadc1);

void configure_ds18b20(void);

void configure_sen0161(void);

void configure_sen0165(void);

void configure_sen0169(void);

void configure_sen0189(void);

void configure_sen0237a(void);

void configure_mqtt_client(void);

void app_measure(void);

void app_send(void);

void app_wait(void);

void app_destroy(void);

#endif /* INC_APP_H_ */
