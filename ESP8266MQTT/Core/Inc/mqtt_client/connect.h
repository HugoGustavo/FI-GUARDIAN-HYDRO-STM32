#ifndef CONNECT_H
#define CONNECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/packet_util.h>
#include <mqtt_client/control_packet.h>

typedef struct __attribute__((__packed__)) connect {
	control_packet* control_packet;
	bytes*  		variable_header;
	unsigned short  keep_alive;
	char*			client_identifier;
	char* 			will_topic;
	char* 			will_message;
	char* 			username;
	char* 			password;
} connect;

extern const unsigned char CONNECT_QOS_LEVEL_0;

extern const unsigned char CONNECT_QOS_LEVEL_1;

extern const unsigned char CONNECT_QOS_LEVEL_2;

connect* connect_init(const bool username, const bool password, const bool will_retain, const unsigned char will_QoS, const bool will_flag, const bool clean_session, const unsigned int keep_alive);

void connect_destroy(connect* connect);

bytes* connect_get_variable_header(connect* connect);

void connect_set_variable_header(connect* connect, bytes* variable_header);

unsigned int connect_get_keep_alive(connect* connect);

void connect_set_keep_alive(connect* connect, const unsigned int keep_alive);

char* connect_get_client_identifier(connect* connect);

void connect_set_client_identifier(connect* connect, char* clientIdentifier);

char* connect_get_will_topic(connect* connect);

void connect_set_will_topic(connect* connect, char* willTopic);

char* connect_get_will_message(connect* connect);

void connect_set_will_message(connect* connect, char* willMessage);

char* connect_get_username(connect* connect);

void connect_set_username(connect* connect, char* username);

char* connect_get_password(connect* connect);

void connect_set_password(connect* connect, char* password);

bytes* connect_to_bytes(connect* connect);

char* connect_to_string(connect* connect);

#endif
