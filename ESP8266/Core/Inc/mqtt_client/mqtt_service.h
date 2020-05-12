#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stm32l4xx_hal.h>
#include <stm32l433xx.h>
#include <util/logger.h>
#include <esp8266/esp8266.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/string_util.h>
#include <mqtt_client/pub_ack_service.h>
#include <mqtt_client/pub_rec_service.h>
#include <mqtt_client/pub_rel_service.h>
#include <mqtt_client/publish_service.h>
#include <mqtt_client/connack_service.h>
#include <mqtt_client/connect_service.h>
#include <mqtt_client/pub_comp_service.h>
#include <mqtt_client/disconnect_service.h>

typedef struct mqtt_service {
	control_packet_proxy* 	control_packet_proxy;
	connack_service* 		connack_service;
	connect_service* 		connect_service;
	disconnect_service* 	disconnect_service;
	pub_ack_service* 		pub_ack_service;
	pub_comp_service* 		pub_comp_service;
	publish_service* 		publish_service;
	pub_rec_service* 		pub_rec_service;
	pub_rel_service* 		pub_rel_service;
} mqtt_service;

extern unsigned char MQTT_SERVICE_QOS_LEVEL_0;

extern unsigned char MQTT_SERVICE_QOS_LEVEL_1;

extern unsigned char MQTT_SERVICE_QOS_LEVEL_2;

mqtt_service* mqtt_service_init(control_packet_proxy* control_packet_proxy, connack_service* connack_service, connect_service* connect_service, disconnect_service* disconnect_service, pub_ack_service* pub_ack_service, pub_comp_service* pub_comp_service, publish_service* publish_service, pub_rec_service* pub_rec_service, pub_rel_service* pub_rel_service);

void mqtt_service_destroy(mqtt_service* mqtt_service);

void mqtt_service_connect(mqtt_service* mqtt_service, char* id, char* host, unsigned int port, unsigned int keep_alive, bool clean_session);

void mqtt_service_publish(mqtt_service* mqtt_service, char* topic, char* payload, unsigned char qos, bool retain);

void mqtt_service_disconnect(mqtt_service* mqtt_service);

void mqtt_service_wait_to_send(mqtt_service* mqtt_service, unsigned int mseconds);

#endif
