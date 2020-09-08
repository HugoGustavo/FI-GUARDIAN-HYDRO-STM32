#ifndef CONNECT_SERVICE_H
#define CONNECT_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/connect.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/control_packet_proxy.h>

typedef struct __attribute__((__packed__)) connect_service {
	control_packet_proxy* control_packet_proxy;
} connect_service;

connect_service* connect_service_init(control_packet_proxy* control_packet_proxy);

void connect_service_destroy(connect_service* connect_service);

connect* connect_service_create(connect_service* connect_service);

connect* connect_service_read(connect_service* connect_service);

void connect_service_write(connect_service* connect_service, connect* connect);

#endif
