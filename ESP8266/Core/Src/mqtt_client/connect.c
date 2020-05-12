#include <mqtt_client/connect.h>


const unsigned char CONNECT_QOS_LEVEL_0 = 0x00;

const unsigned char CONNECT_QOS_LEVEL_1 = 0x01;

const unsigned char CONNECT_QOS_LEVEL_2 = 0x02;


connect* connect_init(const bool username, const bool password, const bool will_retain, const unsigned char will_QoS, const bool will_flag, const bool clean_session, const unsigned int keep_alive){
	connect* result = (connect*) malloc(sizeof(connect));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_CONNECT, CONTROL_PACKET_FLAG_CONNECT, 0x00);

	result->variable_header = bytes_init();
	bytes_push_back( result->variable_header, (unsigned char) 0 );
	bytes_push_back( result->variable_header, (unsigned char) 4 );
	bytes_push_back( result->variable_header, (unsigned char) 'M' );
	bytes_push_back( result->variable_header, (unsigned char) 'Q' );
	bytes_push_back( result->variable_header, (unsigned char) 'T' );
	bytes_push_back( result->variable_header, (unsigned char) 'T' );
	bytes_push_back( result->variable_header, (unsigned char) 4 );

	// Connect Flag bits
	unsigned char flags = (unsigned char) 0;
	flags = flags | ( (username ? 0x01 : 0x00) << 7 ); // User Name Flag
	flags = flags | ( (password ? 0x01 : 0x00) << 6 ); // Password Flag
	flags = flags | ( (will_retain ? 0x01 : 0x00) << 5 ); // Will Retain
	flags = flags | ( (will_QoS & 0x03) << 3 ); // Will QoS
	flags = flags | ( (will_flag ? 0x01 : 0x00) << 2 ); // Will Flag
	flags = flags | ( (clean_session ? 0x01 : 0x00) << 1 ); // Clean Session

	// Condition of will_flag
	if ( ! will_flag ){
		flags = flags | ( 0x00 << 5 ); // Will Retain
	    flags = flags | ( 0x00 << 3 ); // Will QoS
	}

	if ( ! username ){
		flags = flags | ( 0x00 << 6 ); // Password Flag
	}

	bytes_push_back( result->variable_header, flags);
	result->keep_alive = keep_alive;

	return result;
}

void connect_destroy(connect* connect){
	if(connect == NULL) return;
	control_packet_destroy(connect->control_packet);
	connect->control_packet = NULL;
	free(connect);
	connect = NULL;
}

bytes* connect_get_variable_header(connect* connect){
	return connect == NULL ? NULL : connect->variable_header;
}

void connect_set_variable_header(connect* connect, bytes* variable_header){
	if( connect == NULL) return;
	connect->variable_header = variable_header;
}

unsigned int connect_get_keep_alive(connect* connect){
	return connect == NULL ? 0 : connect->keep_alive;
}

void connect_set_keep_alive(connect* connect, const unsigned int keep_alive){
	if( connect == NULL) return;
	connect->keep_alive = keep_alive;
}

char* connect_get_client_identifier(connect* connect){
	return connect == NULL ? NULL : connect->client_identifier;
}

void connect_set_client_identifier(connect* connect, char* client_identifier){
	if( connect == NULL) return;
	connect->client_identifier = client_identifier;
}

char* connect_get_will_topic(connect* connect){
	return connect == NULL ? NULL : connect->will_topic;
}

void connect_set_will_topic(connect* connect, char* will_topic){
	if( connect == NULL) return;
	connect->will_topic = will_topic;
}

char* connect_get_will_message(connect* connect){
	return connect == NULL ? NULL : connect->will_message;
}

void connect_set_will_message(connect* connect, char* will_message){
	if( connect == NULL) return;
	connect->will_message = will_message;
}

char* connect_get_username(connect* connect){
	return connect == NULL ? NULL : connect->username;
}

void connect_set_username(connect* connect, char* username){
	if( connect == NULL) return;
	connect->username = username;
}

char* connect_get_password(connect* connect){
	return connect == NULL ? NULL : connect->password;
}

void connect_set_password(connect* connect, char* password){
	if( connect == NULL) return;
	connect->password = password;
}

bytes* connect_to_bytes(connect* connect){
	if( connect == NULL) return NULL;

	bytes* payload = bytes_init();

	char* client_identifier = connect_get_client_identifier(connect);
	if ( ! string_util_is_empty(client_identifier) ){
		if ( string_util_length(client_identifier) >= 24 ){ // Deve ter no maximo 23 caracteres
			char* client_identifier_sub_string = string_util_build_empty_string(23);
			string_util_copy(client_identifier_sub_string, client_identifier, 23);
			bytes* client_identifier_bytes = packet_util_build_bytes(client_identifier_sub_string);
			bytes_concat(payload, client_identifier_bytes);
		} else {
			bytes* client_identifier_bytes = packet_util_build_bytes(client_identifier);
			bytes_concat(payload, client_identifier_bytes);
		}
	}


	unsigned char flags = bytes_at(connect->variable_header, 7);
	if ( ( flags & ( 0x01 << 2 ) ) && ! string_util_is_empty(connect->will_topic) ){
		bytes* will_topic_bytes = packet_util_build_bytes(connect->will_topic);
		bytes_concat(payload, will_topic_bytes);
	}

	if ( ( flags & ( 0x01 << 2 ) ) && ! string_util_is_empty(connect->will_message) ){
		bytes* will_message_bytes = packet_util_build_bytes(connect->will_message);
		bytes_concat(payload, will_message_bytes);
	}

	if ( ( flags & ( 0x01 << 7 ) ) && ! string_util_is_empty(connect->username) ){
		bytes* username_bytes = packet_util_build_bytes(connect->username);
		bytes_concat(payload, username_bytes);
	    if ( ( flags & ( 0x01 << 6 ) ) && ! string_util_is_empty(connect->password) ){
	    	bytes* password_bytes = packet_util_build_bytes(connect->password);
	    	bytes_concat(payload, password_bytes);
	    }
	}

	long int remaining_length = bytes_get_size(connect->variable_header) + bytes_get_size(payload) + sizeof(connect->keep_alive);
	control_packet_set_remaining_length(connect->control_packet, remaining_length);

	bytes* result = control_packet_to_bytes(connect->control_packet);
	bytes_concat(result, connect->variable_header);
	bytes_push_back( result, (unsigned char) ( (connect->keep_alive & 0xFF00) >> 8) );
	bytes_push_back( result, (unsigned char) ( (connect->keep_alive & 0x00FF) ) );
	bytes_concat( result, payload);
	return result;
}

char* connect_to_string(connect* connect){
	if( connect == NULL ) return NULL;
	bytes* connect_bytes = connect_to_bytes(connect);
	char* result = bytes_to_string(connect_bytes);
	return result;
}

