#ifndef DISCONNECT_SERVICE_H
#define DISCONNECT_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/disconnect.h>
#include <mqtt_client/string_util.h>
#include <mqtt_client/control_packet_proxy.h>

typedef struct disconnect_service {
	control_packet_proxy* control_packet_proxy;
} disconnect_service;

disconnect_service* disconnect_service_init(control_packet_proxy* control_packet_proxy);

void disconnect_service_destroy(disconnect_service* disconnect_service);

disconnect* disconnect_service_create(disconnect_service* disconnect_service);

disconnect* disconnect_service_read(disconnect_service* disconnect_service);

void disconnect_service_write(disconnect_service* disconnect_service, disconnect* disconnect);

#endif
