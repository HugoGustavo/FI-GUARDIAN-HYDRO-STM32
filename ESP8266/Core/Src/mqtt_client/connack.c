#include "../../Inc/mqtt_client/connack.h"


const unsigned char CONNACK_RETURN_CODE_CONNECTION_ACCEPTED                              = 0x00;

const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_UNACCEPTABLE_PROTOCOL_VERSION = 0x01;

const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_IDENTIFIER_REJECTED           = 0x02;

const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_SERVER_UNAVAILABLE            = 0x03;

const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_BAD_USERNAME_OR_PASSWORD      = 0x04;

const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_NOT_AUTHORIZED                = 0x05;

connack* connack_init(const bool clean_session, const unsigned char return_code){
	connack* result = (connack*) malloc(sizeof(connack));
	result->clean_session      	= clean_session;
	result->return_code        	= return_code;
	return result;
}

void connack_destroy(connack* connack){
	if( connack == NULL ) return;

	connack->control_packet = NULL;
	free(connack);
	connack = NULL;
}

bool connack_is_clean_session(connack* connack){
	return connack == NULL ? false : connack->clean_session;
}

void connack_set_clean_session(connack* connack, const bool clean_session){
	if( connack == NULL ) return;
	connack->clean_session = clean_session;
}

unsigned char connack_get_return_code(connack* connack){
	return connack == NULL ? (unsigned char) 0 : connack->return_code;
}

void connack_set_return_code(connack* connack, const unsigned char return_code){
	if( connack == NULL ) return;
	connack->return_code = return_code;
}

bool connack_is_connection_accepted(connack* connack){
	return connack == NULL ? false : connack->return_code == CONNACK_RETURN_CODE_CONNECTION_ACCEPTED;
}

bool connack_is_refused_unacceptable_protoco_version(connack* connack){
	return connack == NULL ? false : connack->return_code == CONNACK_RETURN_CODE_CONNECTION_REFUSED_UNACCEPTABLE_PROTOCOL_VERSION;
}

bool connack_is_refused_identifier_rejected(connack* connack){
	return connack == NULL ? false : connack->return_code == CONNACK_RETURN_CODE_CONNECTION_REFUSED_IDENTIFIER_REJECTED;
}

bool connack_is_refused_server_unavailable(connack* connack){
	return connack == NULL ? false : connack->return_code == CONNACK_RETURN_CODE_CONNECTION_REFUSED_SERVER_UNAVAILABLE;
}

bool connack_is_refused_bad_username_or_password(connack* connack){
	return connack == NULL ? false : connack->return_code == CONNACK_RETURN_CODE_CONNECTION_REFUSED_BAD_USERNAME_OR_PASSWORD;
}

bool connack_is_refused_not_authorized(connack* connack){
	return connack == NULL ? false : connack->return_code == CONNACK_RETURN_CODE_CONNECTION_REFUSED_NOT_AUTHORIZED;
}

bytes* connack_to_bytes(connack* connack){
	if( connack == NULL ) return NULL;
	bytes* result = connack_to_bytes(connack);
	bytes_push_back(result, (unsigned char) ( connack->clean_session ? 0x00 : 0x01 ));
	bytes_push_back(result, connack->return_code);
	return result;
}

char* connack_to_string(connack* connack){
	if( connack == NULL ) return NULL;
	bytes* bytes = connack_to_bytes(connack);
	char* result = bytes_to_string(bytes);
	return result;
}
