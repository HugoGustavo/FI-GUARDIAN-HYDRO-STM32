/*
 * app.c
 *
 *  Created on: Feb 27, 2020
 *      Author: skywalker
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <app.h>
#include <sen0165/sen0165.h>
#include <esp8266/esp8266.h>
#include <mqtt_client/mqtt_client.h>
#include <util/logger.h>

void app_init(void){
	SSD1306_Init();
	SDD1306_Clear_Screen();
	hw_uart_init();
}

esp8266* config_esp(void){
	esp8266* esp = esp8266_init();
	esp8266_joinAP(esp, (uint8_t*) "LAPTOP-SE6C11TJ1937", (uint8_t*) "5hB6;261");
	esp8266_enableMUX(esp);
	esp8266_createTCP(esp, (uint8_t*) "192.168.137.211", (uint16_t) 1883);
	return esp;
}

mqtt_client* config_mqtt_client(void){
	mqtt_client* mqtt_client = mqtt_client_init(config_esp());
	mqtt_client_connect(mqtt_client, (char*) "python_test", (char*) "192.168.137.211", 1883, 60, true);
	return mqtt_client;
}

void app_main(void){
	while( true ){
		hw_time_sleep(5000);
	}

}
