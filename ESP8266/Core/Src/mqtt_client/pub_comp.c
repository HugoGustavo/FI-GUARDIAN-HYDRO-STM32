#include "../../Inc/mqtt_client/pub_comp.h"

pub_comp* pub_comp_init(unsigned int packet_identifier){
	pub_comp* result = (pub_comp*) malloc(sizeof(pub_comp));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PUBCOMP, CONTROL_PACKET_FLAG_PUBCOMP, 0x00);
	result->packet_identifier = packet_identifier;
	return result;
}

void pub_comp_destroy(pub_comp* pub_comp){
	if( pub_comp == NULL ) return;
	free(pub_comp);
	pub_comp = NULL;
}

unsigned int pub_comp_get_packet_identifier(pub_comp* pub_comp){
	return pub_comp == NULL ? 0 : pub_comp->packet_identifier;
}

void pub_comp_set_packet_identifier(pub_comp* pub_comp, unsigned int packet_identifier){
	if( pub_comp == NULL ) return;
	pub_comp->packet_identifier = packet_identifier;
}

bytes* pub_comp_to_bytes(pub_comp* pub_comp){
	if( pub_comp == NULL ) return NULL;
	bytes* packet_identifier = bytes_init();
    bytes_push_back(packet_identifier, (unsigned char) ((0xFF00 & pub_comp->packet_identifier) >> 8 ) );
    bytes_push_back(packet_identifier, (unsigned char) (0x00FF & pub_comp->packet_identifier) );

    bytes* result = control_packet_to_bytes(pub_comp->control_packet);
    bytes_concat(result, packet_identifier);
    return result;
}

char* pub_comp_to_string(pub_comp* pub_comp){
	if( pub_comp == NULL ) return NULL;
	bytes* bytes = pub_comp_to_bytes(pub_comp);
	return bytes_to_string(bytes);
}
