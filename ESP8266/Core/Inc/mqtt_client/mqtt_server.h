#ifndef MQTT_SERVER_H
#define MQTT_SERVER_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/logger.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/pub_comp.h>
#include <mqtt_client/pub_rec.h>
#include <mqtt_client/pub_rel.h>
#include <mqtt_client/publish.h>
#include <mqtt_client/connack.h>
#include <mqtt_client/connect.h>
#include <mqtt_client/assembler.h>

typedef struct mqtt_server{
	connect* connect;
	connack* connack;
	publish* publish;
	pub_rec* pub_rec;
	pub_rel* pub_rel;
	pub_comp* pub_comp;
} mqtt_server;

mqtt_server* mqtt_server_init();

void mqtt_server_destroy(mqtt_server* mqtt_server);

void mqtt_server_request(mqtt_server* mqtt_server, bytes* bytes);

bytes* mqtt_server_response(mqtt_server* mqtt_server);

void reset(mqtt_server* mqtt_server);

#endif
