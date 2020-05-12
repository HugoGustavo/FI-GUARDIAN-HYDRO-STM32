#include <mqtt_client/control_packet.h>

const unsigned char CONTROL_PACKET_TYPE_CONNECT      = 0x10;
const unsigned char CONTROL_PACKET_TYPE_CONNACK      = 0x20;
const unsigned char CONTROL_PACKET_TYPE_PUBLISH      = 0x30;
const unsigned char CONTROL_PACKET_TYPE_PUBACK       = 0x40;
const unsigned char CONTROL_PACKET_TYPE_PUBREC       = 0x50;
const unsigned char CONTROL_PACKET_TYPE_PUBREL       = 0x60;
const unsigned char CONTROL_PACKET_TYPE_PUBCOMP      = 0x70;
const unsigned char CONTROL_PACKET_TYPE_SUBSCRIBE    = 0x80;
const unsigned char CONTROL_PACKET_TYPE_SUBACK       = 0x90;
const unsigned char CONTROL_PACKET_TYPE_UNSUBSCRIBE  = 0xA0;
const unsigned char CONTROL_PACKET_TYPE_UNSUBACK     = 0xB0;
const unsigned char CONTROL_PACKET_TYPE_PINGREQ      = 0xC0;
const unsigned char CONTROL_PACKET_TYPE_PINGRESP     = 0xD0;
const unsigned char CONTROL_PACKET_TYPE_DISCONNECT   = 0xE0;

const unsigned char CONTROL_PACKET_FLAG_CONNECT      = 0x00;
const unsigned char CONTROL_PACKET_FLAG_CONNACK      = 0x00;
const unsigned char CONTROL_PACKET_FLAG_PUBLISH      = 0x00;
const unsigned char CONTROL_PACKET_FLAG_PUBACK       = 0x00;
const unsigned char CONTROL_PACKET_FLAG_PUBREC       = 0x00;
const unsigned char CONTROL_PACKET_FLAG_PUBREL       = 0x02;
const unsigned char CONTROL_PACKET_FLAG_PUBCOMP      = 0x00;
const unsigned char CONTROL_PACKET_FLAG_SUBSCRIBE    = 0x02;
const unsigned char CONTROL_PACKET_FLAG_SUBACK       = 0x00;
const unsigned char CONTROL_PACKET_FLAG_UNSUBSCRIBE  = 0x02;
const unsigned char CONTROL_PACKET_FLAG_UNSUBACK     = 0x00;
const unsigned char CONTROL_PACKET_FLAG_PINGREQ      = 0x00;
const unsigned char CONTROL_PACKET_FLAG_PINGRESP     = 0x00;
const unsigned char CONTROL_PACKET_FLAG_DISCONNECT   = 0x00;

control_packet* control_packet_init(const unsigned char type, const unsigned char flags, const long int remaining_length){
	control_packet* result = (control_packet*) malloc(sizeof(control_packet));
	if ( result == NULL ) return NULL;
	result->type 				= type;
	result->flags 				= flags;
	result->remaining_length 	= remaining_length;

	return result;
}

void control_packet_destroy(control_packet* control_packet){
	if( control_packet == NULL ) return;
	free(control_packet);
	control_packet = NULL;
}

unsigned char control_packet_get_type(control_packet* control_packet){
	return control_packet == NULL ? (unsigned char) 0 : control_packet->type;
}

void control_packet_set_type(control_packet* control_packet, const unsigned char type){
	if( control_packet == NULL ) return;
	control_packet->type = type;
}

unsigned char control_packet_get_flags(control_packet* control_packet){
	return control_packet == NULL ? (unsigned char) 0 : control_packet->flags;
}

void control_packet_set_flags(control_packet* control_packet, const unsigned char flags){
	if( control_packet == NULL ) return;
	control_packet->flags = flags;
}

long int control_packet_get_remaining_length(control_packet* control_packet){
	return control_packet == NULL ? (long int) 0 : control_packet->remaining_length;
}

void control_packet_set_remaining_length(control_packet* control_packet, const long int remaining_length){
	if( control_packet == NULL ) return;
	control_packet->remaining_length = remaining_length;
}

bytes* control_packet_to_bytes(control_packet* control_packet){
	if( control_packet == NULL ) return NULL;

	bytes* result = bytes_init();
	bytes_push_back(result, (unsigned char) ( control_packet->type | control_packet->flags ));

	unsigned char encode_byte;
	long int remaining_length = control_packet->remaining_length;
	do {
		encode_byte = remaining_length % 128;
		remaining_length = remaining_length / 128;
		if( remaining_length ) encode_byte = encode_byte | 0x80;
		bytes_push_back(result, (unsigned char) encode_byte);
	} while ( remaining_length > 0 );

	return result;
}

char* control_packet_to_string(control_packet* control_packet){
	if( control_packet == NULL ) return NULL;
	bytes* bytes = control_packet_to_bytes(control_packet);
	return bytes_to_string(bytes);
}
