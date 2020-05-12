#ifndef PUB_ACK_SERVICE_H
#define PUB_ACK_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/pub_ack.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/string_util.h>
#include <mqtt_client/control_packet_proxy.h>


typedef struct pub_ack_service{
	control_packet_proxy* control_packet_proxy;
} pub_ack_service;

pub_ack_service* pub_ack_service_init(control_packet_proxy* control_packet_proxy);

void pub_ack_service_destroy(pub_ack_service* pub_ack_service);

pub_ack* pub_ack_service_create(pub_ack_service* pub_ack_service);

pub_ack* pub_ack_service_read(pub_ack_service* pub_ack_service);

void pub_ack_service_write(pub_ack_service* pub_ack_service, pub_ack* pub_ack);

#endif
