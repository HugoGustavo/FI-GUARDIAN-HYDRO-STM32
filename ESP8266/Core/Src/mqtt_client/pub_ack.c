#include "../../Inc/mqtt_client/pub_ack.h"


pub_ack* pub_ack_init(unsigned int packet_identifier){
	pub_ack* result = (pub_ack*) malloc(sizeof(pub_ack));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PUBACK, CONTROL_PACKET_FLAG_PUBACK, 0x00);
	result->packet_identifier = packet_identifier;
	return result;
}

void pub_ack_destroy(pub_ack* pub_ack){
	if( pub_ack == NULL ) return;

	pub_ack->control_packet = NULL;

	free(pub_ack);
	pub_ack = NULL;
}

unsigned int pub_ack_get_packet_identifier(pub_ack* pub_ack){
	return pub_ack == NULL ? 0 : pub_ack->packet_identifier;
}

void pub_ack_set_packet_identifier(pub_ack* pub_ack, unsigned int packet_identifier){
	if( pub_ack == NULL ) return;
	pub_ack->packet_identifier = packet_identifier;
}

bytes* pub_ack_to_bytes(pub_ack* pub_ack){
	if( pub_ack == NULL ) return NULL;

    bytes* packet_identifier = bytes_init();
    bytes_push_back( packet_identifier, (unsigned char) ( (0xFF00 & pub_ack->packet_identifier) >> 8 ) );
    bytes_push_back( packet_identifier, (unsigned char) ( 0x00FF & pub_ack->packet_identifier ) );

    bytes* result = control_packet_to_bytes(pub_ack->control_packet);
    bytes_concat(result, packet_identifier);
    bytes_destroy(packet_identifier);

    return result;
}

char* pub_ack_to_string(pub_ack* pub_ack){
	if( pub_ack == NULL ) return NULL;
	bytes* bytes = pub_ack_to_bytes(pub_ack);
	return bytes_to_string(bytes);
}
