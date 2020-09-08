#ifndef PUB_COMP_SERVICE_H
#define PUB_COMP_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/pub_comp.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/control_packet_proxy.h>

typedef struct __attribute__((__packed__)) pub_comp_service{
	control_packet_proxy* control_packet_proxy;
} pub_comp_service;

pub_comp_service* pub_comp_service_init(control_packet_proxy* control_packet_proxy);

void pub_comp_service_destroy(pub_comp_service* pub_comp_service);

pub_comp* pub_comp_service_create(pub_comp_service* pub_comp_service);

pub_comp* pub_comp_service_read(pub_comp_service* pub_comp_service);

void pub_comp_service_write(pub_comp_service* pub_comp_service, pub_comp* pub_comp);

#endif
