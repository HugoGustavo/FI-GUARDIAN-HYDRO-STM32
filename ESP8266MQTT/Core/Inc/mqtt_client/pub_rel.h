#ifndef PUB_REL_H
#define PUB_REL_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/packet_util.h>
#include <mqtt_client/control_packet.h>

typedef struct __attribute__((__packed__)) pub_rel {
	control_packet* control_packet;
	unsigned int packet_identifier;
} pub_rel;

pub_rel* pub_rel_init(unsigned int packet_identifier);

void pub_rel_destroy(pub_rel* pub_rel);

unsigned int pub_rel_get_packet_identifier(pub_rel* pub_rel);

void pub_rel_set_packet_identifier(pub_rel* pub_rel, unsigned int packet_identifier);

bytes* pub_rel_to_bytes(pub_rel* pub_rel);

char* pub_rel_to_string(pub_rel* pub_rel);

#endif
