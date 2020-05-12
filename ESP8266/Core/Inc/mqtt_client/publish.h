#ifndef PUBLISH_H
#define PUBLISH_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/packet_util.h>
#include <mqtt_client/control_packet.h>

typedef struct publish {
	control_packet* control_packet;
    bool    		dup;
    unsigned char   qos_level;
    bool    		retain;
    char* 			topic_name;
    unsigned short  packet_identifier;
    char* 			payload;
} publish;

extern unsigned char PUBLISH_QOS_LEVEL_0;

extern unsigned char PUBLISH_QOS_LEVEL_1;

extern unsigned char PUBLISH_QOS_LEVEL_2;

publish* publish_init(bool dup, unsigned char qos_level, bool retain);

void publish_destroy(publish* publish);

bool publish_is_dup(publish* publish);

void publish_set_dup(publish* publish, bool dup);

unsigned char publish_get_qos_level(publish* publish);

void publish_set_qos_level(publish* publish, unsigned char qos_level);

bool publish_is_retain(publish* publish);

void publish_set_retain(publish* publish, bool retain);

char* publish_get_topic_name(publish* publish);

void publish_set_topic_name(publish* publish, char* topic_name);

unsigned short publish_get_packet_identifier(publish* publish);

void publish_set_packet_identifier(publish* publish, unsigned short packet_identifier);

char* publish_get_payload(publish* publish);

void publish_set_payload(publish* publish, char* payload);

bytes* publish_to_bytes(publish* publish);

char* publish_to_string(publish* publish);

#endif
