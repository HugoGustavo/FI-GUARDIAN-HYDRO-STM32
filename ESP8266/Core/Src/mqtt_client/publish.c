#include "../../Inc/mqtt_client/publish.h"

unsigned char PUBLISH_QOS_LEVEL_0 = 0x00;

unsigned char PUBLISH_QOS_LEVEL_1 = 0x01;

unsigned char PUBLISH_QOS_LEVEL_2 = 0x02;

publish* publish_init(bool dup, unsigned char qos_level, bool retain){
	publish* result = (publish*) malloc(sizeof(publish));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PUBLISH, CONTROL_PACKET_FLAG_PUBLISH, 0x00);

	result->qos_level         = qos_level;
	result->dup               = result->qos_level == 0x00 ? false : dup;
    result->retain            = retain;
    result->topic_name        = NULL;
    result->packet_identifier = 0;
    result->payload           = NULL;
    control_packet_set_flags(result->control_packet, 0x00);
    control_packet_set_flags(result->control_packet, result->dup == true ? (0x01 << 3) : control_packet_get_flags(result->control_packet) );
    control_packet_set_flags(result->control_packet, control_packet_get_flags(result->control_packet) | ( (result->qos_level & 0x03) << 1 ) );
    control_packet_set_flags(result->control_packet, result->retain ? control_packet_get_flags(result->control_packet) | 0x01 : control_packet_get_flags(result->control_packet));

    return result;
}

void publish_destroy(publish* publish){
	if( publish == NULL ) return;

	publish->control_packet = NULL;
	publish->topic_name = NULL;
	publish->payload = NULL;

	free(publish);
	publish = NULL;
}

bool publish_is_dup(publish* publish){
	return publish == NULL ? false : publish->dup;
}

void publish_set_dup(publish* publish, bool dup){
	if( publish == NULL ) return;
	publish->dup = dup;
}

unsigned char publish_get_qos_level(publish* publish){
	return publish == NULL ? (unsigned char) '\0' : publish->qos_level;
}

void publish_set_qos_level(publish* publish, unsigned char qos_level){
	if( publish == NULL ) return;
	publish->qos_level = qos_level;
}

bool publish_is_retain(publish* publish){
	return publish == NULL ? false : publish->retain;
}

void publish_set_retain(publish* publish, bool retain){
	if( publish == NULL ) return;
	publish->retain = retain;
}

char* publish_get_topic_name(publish* publish){
	return publish == NULL ? NULL : publish->topic_name;
}

void publish_set_topic_name(publish* publish, char* topic_name){
	if( publish == NULL ) return;
	publish->topic_name = topic_name;
}

unsigned short publish_get_packet_identifier(publish* publish){
	return publish == NULL ? 0 : publish->packet_identifier;
}

void publish_set_packet_identifier(publish* publish, unsigned short packet_identifier){
	if( publish == NULL ) return;
	publish->packet_identifier = packet_identifier;
}

char* publish_get_payload(publish* publish){
	return publish == NULL ? NULL : publish->payload;
}

void publish_set_payload(publish* publish, char* payload){
	if( publish == NULL ) return;
	publish->payload = payload;
}

bytes* publish_to_bytes(publish* publish){
	if( publish == NULL ) return NULL;

	bytes* variable_header = bytes_init();
	if( ! string_util_is_empty(publish->topic_name) ){
		bytes* topic_name_field = packet_util_build_bytes(publish->topic_name);
		bytes_concat(variable_header, topic_name_field);
		bytes_destroy(topic_name_field);
	}

	if( publish->qos_level == PUBLISH_QOS_LEVEL_1 || publish->qos_level == PUBLISH_QOS_LEVEL_2 ) {
		bytes* packet_identifier_field = bytes_init();
	    unsigned char msb_packet_identifier = (unsigned char) ( (0xFF00 & publish->packet_identifier) >> 8 );
	    unsigned char lsb_packet_identifier = (unsigned char) ( 0x00FF & publish->packet_identifier);
	    bytes_push_back(packet_identifier_field, msb_packet_identifier);
	    bytes_push_back(packet_identifier_field, lsb_packet_identifier);
	    bytes_concat(variable_header, packet_identifier_field);
	    bytes_destroy(packet_identifier_field);
	}

	// The length of the payload can be calculated by subtracting the length of the variable header from the Remaining Length field that is in the Fixed Header
	// so there's no need to add the field size
	bytes* payload = bytes_init();
	if ( ! string_util_is_empty(publish->payload) ){
		unsigned int length = string_util_length(publish->payload);
		for(register int i = 0; i < length; i++) bytes_push_back(payload, (unsigned char) publish->payload[i] );
		//bytes_concat(payload, packet_util_build_bytes(publish->payload));
	}

	control_packet_set_remaining_length(publish->control_packet, (long int) bytes_get_size(variable_header) + bytes_get_size(payload) );

	bytes* result = control_packet_to_bytes(publish->control_packet);
	bytes_concat(result, variable_header);
	bytes_concat(result, payload);

	bytes_destroy(variable_header);
	bytes_destroy(payload);

	return result;
}

char* publish_to_string(publish* publish){
	if( publish == NULL ) return NULL;
	bytes* bytes = publish_to_bytes(publish);
	return bytes_to_string(bytes);
}
