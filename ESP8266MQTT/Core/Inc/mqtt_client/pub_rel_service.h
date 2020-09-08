#ifndef PUB_REL_SERVICE_H
#define PUB_REL_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/pub_rel.h>
#include <mqtt_client/session.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/control_packet_proxy.h>

typedef struct __attribute__((__packed__)) pub_rel_service {
	control_packet_proxy* control_packet_proxy;
} pub_rel_service;

pub_rel_service* pub_rel_service_init(control_packet_proxy* control_packet_proxy);

void pub_rel_service_destroy(pub_rel_service* pub_rel_service);

pub_rel* pub_rel_service_create(pub_rel_service* pub_rel_service);

pub_rel* pub_rel_service_read(pub_rel_service* pub_rel_service);

void pub_rel_service_write(pub_rel_service* pub_rel_service, pub_rel* pub_rel);

#endif
