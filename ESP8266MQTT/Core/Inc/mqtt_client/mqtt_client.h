#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <esp8266/esp8266.h>
#include <mqtt_client/wifi.h>
#include <mqtt_client/session.h>
#include <mqtt_client/mqtt_server.h>
#include <mqtt_client/mqtt_service.h>
#include <mqtt_client/pub_ack_service.h>
#include <mqtt_client/pub_rec_service.h>
#include <mqtt_client/pub_rel_service.h>
#include <mqtt_client/publish_service.h>
#include <mqtt_client/connack_service.h>
#include <mqtt_client/connect_service.h>
#include <mqtt_client/pub_comp_service.h>
#include <mqtt_client/ping_resp_service.h>
#include <mqtt_client/ping_req_service.h>
#include <mqtt_client/control_packet_proxy.h>
#include <mqtt_client/disconnect_service.h>


typedef struct __attribute__((__packed__)) mqtt_client{
	wifi* 					wifi;
	ping_req_service* 		ping_req_service;
	ping_resp_service* 		ping_resp_service;
	control_packet_proxy* 	control_packet_proxy;
	connack_service* 		connack_service;
	connect_service* 		connect_service;
	disconnect_service* 	disconnect_service;
	pub_ack_service* 		pub_ack_service;
	pub_comp_service* 		pub_comp_service;
	publish_service* 		publish_service;
	pub_rec_service* 		pub_rec_service;
	pub_rel_service* 		pub_rel_service;
	mqtt_service* 			mqtt_service;
} mqtt_client;

extern unsigned char MQTT_CLIENT_QOS_LEVEL_0;

extern unsigned char MQTT_CLIENT_QOS_LEVEL_1;

extern unsigned char MQTT_CLIENT_QOS_LEVEL_2;

mqtt_client* mqtt_client_init(esp8266* esp8266);

void mqtt_client_destroy(mqtt_client* mqtt_client);

void mqtt_client_connect(mqtt_client* mqtt_client, char* id, char* host, unsigned int port, unsigned int keep_alive, bool clean_session);

void mqtt_client_publish(mqtt_client* mqtt_client, char* topic, char* payload, unsigned char qos, bool retain);

void mqtt_client_disconnect(mqtt_client* mqtt_client);

#endif
