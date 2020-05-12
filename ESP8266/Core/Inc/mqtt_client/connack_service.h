#ifndef CONNACK_SERVICE_H
#define CONNACK_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/logger.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/connack.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/string_util.h>
#include <mqtt_client/control_packet_proxy.h>

typedef struct connack_service {
	control_packet_proxy* control_packet_proxy;
} connack_service;

connack_service* connack_service_init(control_packet_proxy* control_packet_proxy);

void connack_service_destroy(connack_service* connack_service);

connack* connack_service_create(connack_service* connack_service);

connack* connack_service_read(connack_service* connack_service);

void connack_service_write(connack_service* connack_service, connack* connack);

#endif
