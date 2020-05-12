#include "../../Inc/mqtt_client/pub_rec.h"


pub_rec* pub_rec_init(unsigned int packet_identifier){
	pub_rec* result = (pub_rec*) malloc(sizeof(pub_rec));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PUBREC, CONTROL_PACKET_FLAG_PUBREC, 0x00);
	result->packet_identifier = packet_identifier;
	return result;
}

void pub_rec_destroy(pub_rec* pub_rec){
	if( pub_rec == NULL ) return;
	free(pub_rec);
	pub_rec = NULL;
}

unsigned int pub_rec_get_packet_identifier(pub_rec* pub_rec){
	return pub_rec == NULL ? 0 : pub_rec->packet_identifier;
}

void pub_rec_set_packet_identifier(pub_rec* pub_rec, unsigned int packet_identifier){
	if( pub_rec == NULL ) return;
	pub_rec->packet_identifier = packet_identifier;
}

bytes* pub_rec_to_bytes(pub_rec* pub_rec){
    bytes* packet_identifier = bytes_init();
    bytes_push_back(packet_identifier, (unsigned char) ( (0xFF00 & pub_rec->packet_identifier) >> 8 ) );
    bytes_push_back(packet_identifier, (unsigned char) ( 0x00FF & pub_rec->packet_identifier) );

    bytes* result = control_packet_to_bytes(pub_rec->control_packet);
    bytes_concat(result, packet_identifier);
    return result;
}

char* pub_rec_to_string(pub_rec* pub_rec){
	if( pub_rec == NULL ) return NULL;
	bytes* bytes = pub_rec_to_bytes(pub_rec);
	return bytes_to_string(bytes);
}
