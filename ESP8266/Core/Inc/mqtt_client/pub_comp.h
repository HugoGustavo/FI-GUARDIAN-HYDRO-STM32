#ifndef PUB_COMP_H
#define PUB_COMP_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/packet_util.h>
#include <mqtt_client/control_packet.h>

typedef struct pub_comp {
	control_packet* control_packet;
	unsigned int packet_identifier;
} pub_comp;

pub_comp* pub_comp_init(unsigned int packet_identifier);

void pub_comp_destroy(pub_comp* pub_comp);

unsigned int pub_comp_get_packet_identifier(pub_comp* pub_comp);

void pub_comp_set_packet_identifier(pub_comp* pub_comp, unsigned int packet_identifier);

bytes* pub_comp_to_bytes(pub_comp* pub_comp);

char* pub_comp_to_string(pub_comp* pub_comp);

#endif
