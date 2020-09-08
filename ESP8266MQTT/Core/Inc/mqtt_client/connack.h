#ifndef CONNACK_H
#define CONNACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/control_packet.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) connack {
	control_packet*	control_packet;
	bool 			clean_session;
	unsigned char 	return_code;
} connack;


extern const unsigned char CONNACK_RETURN_CODE_CONNECTION_ACCEPTED;

extern const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_UNACCEPTABLE_PROTOCOL_VERSION;

extern const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_IDENTIFIER_REJECTED;

extern const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_SERVER_UNAVAILABLE;

extern const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_BAD_USERNAME_OR_PASSWORD;

extern const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_NOT_AUTHORIZED;

connack* connack_init(const bool clean_session, const unsigned char return_code);

void connack_destroy(connack* connack);

bool connack_is_clean_session(connack* connack);

void connack_set_clean_session(connack* connack, const bool clean_session);

unsigned char connack_get_return_code(connack* connack);

void connack_set_return_code(connack* connack, const unsigned char return_code);

bool connack_is_connection_accepted(connack* connack);

bool connack_is_refused_unacceptable_protoco_version(connack* connack);

bool connack_is_refused_identifier_rejected(connack* connack);

bool connack_is_refused_server_unavailable(connack* connack);

bool connack_is_refused_bad_username_or_password(connack* connack);

bool connack_is_refused_not_authorized(connack* connack);

bytes* connack_to_bytes(connack* connack);

char* connack_to_string(connack* connack);

#endif
