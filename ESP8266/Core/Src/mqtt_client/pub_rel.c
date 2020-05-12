#include "../../Inc/mqtt_client/pub_rel.h"

pub_rel* pub_rel_init(unsigned int packet_identifier){
	pub_rel* result = (pub_rel*) malloc(sizeof(pub_rel));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PUBREL, CONTROL_PACKET_FLAG_PUBREL, 0x02);
	result->packet_identifier = packet_identifier;

	return result;
}

void pub_rel_destroy(pub_rel* pub_rel){
	if( pub_rel == NULL ) return;
	free(pub_rel);
	pub_rel = NULL;
}

unsigned int pub_rel_get_packet_identifier(pub_rel* pub_rel){
	return pub_rel == NULL ? 0 : pub_rel->packet_identifier;
}

void pub_rel_set_packet_identifier(pub_rel* pub_rel, unsigned int packet_identifier){
	if( pub_rel == NULL ) return;
	pub_rel->packet_identifier = packet_identifier;
}

bytes* pub_rel_to_bytes(pub_rel* pub_rel){
	if( pub_rel == NULL ) return NULL;

    bytes* packet_identifier = bytes_init();
    unsigned char msb_packet_identifier = (unsigned char) ( (0xFF00 & pub_rel->packet_identifier) >> 8 );
    unsigned char lsb_packet_identifier = (unsigned char) ( 0x00FF & pub_rel->packet_identifier);
    bytes_push_back(packet_identifier, msb_packet_identifier);
    bytes_push_back(packet_identifier, lsb_packet_identifier);

    bytes* result = control_packet_to_bytes(pub_rel->control_packet);
    bytes_concat(result, packet_identifier);
    return result;
}

char* pub_rel_to_string(pub_rel* pub_rel){
	if( pub_rel == NULL ) return NULL;
	bytes* bytes = pub_rel_to_bytes(pub_rel);
	char* result = bytes_to_string(bytes);
	return result;
}
