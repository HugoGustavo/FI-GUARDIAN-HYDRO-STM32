#ifndef PUBLISH_SERVICE_H
#define PUBLISH_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/publish.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/control_packet_proxy.h>

typedef struct __attribute__((__packed__)) publish_service{
	control_packet_proxy* control_packet_proxy;
} publish_service;

publish_service* publish_service_init(control_packet_proxy* control_packet_proxy);

void publish_service_destroy(publish_service* publish_service);

publish* publish_service_create(publish_service* publish_service);

publish* publish_service_read(publish_service* publish_service);

void publish_service_write(publish_service* publish_service, publish* publish);

#endif
