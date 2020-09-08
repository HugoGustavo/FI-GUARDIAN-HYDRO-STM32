#ifndef CONTROL_PACKET_H
#define CONTROL_PACKET_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) control_packet {
	unsigned char   type;
	unsigned char   flags;
	long int        remaining_length;
} control_packet;

extern const unsigned char CONTROL_PACKET_TYPE_CONNECT;
extern const unsigned char CONTROL_PACKET_TYPE_CONNACK;
extern const unsigned char CONTROL_PACKET_TYPE_PUBLISH;
extern const unsigned char CONTROL_PACKET_TYPE_PUBACK;
extern const unsigned char CONTROL_PACKET_TYPE_PUBREC;
extern const unsigned char CONTROL_PACKET_TYPE_PUBREL;
extern const unsigned char CONTROL_PACKET_TYPE_PUBCOMP;
extern const unsigned char CONTROL_PACKET_TYPE_SUBSCRIBE;
extern const unsigned char CONTROL_PACKET_TYPE_SUBACK;
extern const unsigned char CONTROL_PACKET_TYPE_UNSUBSCRIBE;
extern const unsigned char CONTROL_PACKET_TYPE_UNSUBACK;
extern const unsigned char CONTROL_PACKET_TYPE_PINGREQ;
extern const unsigned char CONTROL_PACKET_TYPE_PINGRESP;
extern const unsigned char CONTROL_PACKET_TYPE_DISCONNECT;

extern const unsigned char CONTROL_PACKET_FLAG_CONNECT;
extern const unsigned char CONTROL_PACKET_FLAG_CONNACK;
extern const unsigned char CONTROL_PACKET_FLAG_PUBLISH;
extern const unsigned char CONTROL_PACKET_FLAG_PUBACK;
extern const unsigned char CONTROL_PACKET_FLAG_PUBREC;
extern const unsigned char CONTROL_PACKET_FLAG_PUBREL;
extern const unsigned char CONTROL_PACKET_FLAG_PUBCOMP;
extern const unsigned char CONTROL_PACKET_FLAG_SUBSCRIBE;
extern const unsigned char CONTROL_PACKET_FLAG_SUBACK;
extern const unsigned char CONTROL_PACKET_FLAG_UNSUBSCRIBE;
extern const unsigned char CONTROL_PACKET_FLAG_UNSUBACK;
extern const unsigned char CONTROL_PACKET_FLAG_PINGREQ;
extern const unsigned char CONTROL_PACKET_FLAG_PINGRESP;
extern const unsigned char CONTROL_PACKET_FLAG_DISCONNECT;

control_packet* control_packet_init(const unsigned char type, const unsigned char flags, const long int remaining_length);

unsigned char control_packet_get_type(control_packet* control_packet);
        
void control_packet_set_type(control_packet* control_packet, const unsigned char type);
        
unsigned char control_packet_get_flags(control_packet* control_packet);
    
void control_packet_set_flags(control_packet* control_packet, const unsigned char flags);

long int control_packet_get_remaining_length(control_packet* control_packet);

void control_packet_set_remaining_length(control_packet* control_packet, const long int remaining_length);

bytes* control_packet_to_bytes(control_packet* control_packet);

char* control_packet_to_string(control_packet* control_packet);

#endif
