#ifndef PUB_ACK_H
#define PUB_ACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/control_packet.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) pub_ack {
	control_packet* control_packet;
	unsigned int packet_identifier;
} pub_ack;

pub_ack* pub_ack_init(unsigned int packet_identifier);

void pub_ack_destroy(pub_ack* pub_ack);

unsigned int pub_ack_get_packet_identifier(pub_ack* pub_ack);

void pub_ack_set_packet_identifier(pub_ack* pub_ack, unsigned int packet_identifier);

bytes* pub_ack_to_bytes(pub_ack* pub_ack);

char* pub_ack_to_string(pub_ack* pub_ack);

#endif
