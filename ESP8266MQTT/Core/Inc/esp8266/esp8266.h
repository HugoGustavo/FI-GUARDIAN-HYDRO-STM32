#ifndef ESP8266_H
#define ESP8266_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "at.h"
#include "hw.h"
#include <util/logger.h>
#include <ssd1306/ssd1306_fonts.h>
#include <ssd1306/ssd1306.h>
#include "web.h"


typedef struct __attribute__((__packed__)) esp8266 {
	uint8_t* 	ssid;
	uint8_t* 	password;
	bool 		connected;
	uint8_t* 	ip;
	uint16_t 	port;
} esp8266;

esp8266* esp8266_init(void);

void esp8266_destroy(esp8266* esp8266);

void esp8266_turn_on(esp8266* esp8266);

void esp8266_turn_off(esp8266* esp);

void esp8266_reset(esp8266* esp8266);

void esp8266_setOprToStationSoftAP(esp8266* esp8266);

bool esp8266_joinAP(esp8266* esp8266, uint8_t* 	ssid, uint8_t* password);

bool esp8266_enableMUX(esp8266* esp8266);

bool esp8266_disableMUX(esp8266* esp8266);

bool esp8266_createTCP(esp8266* esp8266, uint8_t* ip, uint16_t port);

bool esp8266_releaseTCP(esp8266* esp8266);

uint32_t esp8266_recv(esp8266* esp8266);

bool esp8266_send(esp8266* esp8266, uint8_t* buffer,uint16_t buffer_size);

void esp8266_wait_for_sending(uint16_t timeoutInMilliseconds);

#endif
