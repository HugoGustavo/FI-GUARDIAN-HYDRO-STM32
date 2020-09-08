#ifndef PUB_REC_H
#define PUB_REC_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/control_packet.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) pub_rec {
	control_packet* control_packet;
	unsigned int packet_identifier;
} pub_rec;


pub_rec* pub_rec_init(unsigned int packet_identifier);

void pub_rec_destroy(pub_rec* pub_rec);

unsigned int pub_rec_get_packet_identifier(pub_rec* pub_rec);

void pub_rec_set_packet_identifier(pub_rec* pub_rec, unsigned int packet_identifier);

bytes* pub_rec_to_bytes(pub_rec* pub_rec);

char* pub_rec_to_string(pub_rec* pub_rec);

#endif
