#include <mqtt_client/assembler.h>

control_packet* assembler_build_to_control_packet(bytes* bytes){
	if( bytes == NULL ) return NULL;
	control_packet* result = (control_packet*) malloc(sizeof(control_packet));

	unsigned char typeAndFlags	= bytes_at(bytes, 0);
	result->type                = typeAndFlags & 0xF0;
	result->flags               = typeAndFlags & 0x0F;
	result->remaining_length    = bytes_at(bytes, 1);

	return result;
}

connack* assembler_build_to_connack(bytes* bytes){
	if( bytes == NULL ) return NULL;
	connack* result = (connack*) malloc(sizeof(connack));
	result->control_packet = assembler_build_to_control_packet(bytes);
	result->clean_session = bytes_at(bytes, 2) == 0x00 ? true : false;
	result->return_code = bytes_at(bytes, 3);
	return result;
}

connect* assembler_build_to_connect(bytes* bytes){
	if( bytes == NULL ) return NULL;
	connect* result = (connect*) malloc(sizeof(connect));
	result->control_packet = assembler_build_to_control_packet(bytes);

	unsigned int index = 2;

	// Protocol Name
	result->variable_header = bytes_init();
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );

	// Protocol Level
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)) );

	// Flags
	bytes_push_back( result->variable_header, (unsigned char) bytes_at(bytes, (index++)));

	// Keep Alive
	unsigned int msb_keep_alive = (unsigned int) (bytes_at(bytes, (index++)) << 8);
	unsigned int lsb_keep_alive = (unsigned int) bytes_at(bytes, (index++));
	result->keep_alive = msb_keep_alive + lsb_keep_alive;

	// Client Identifier
	result->client_identifier = packet_util_build_string(bytes, &index);

	// Flags
	unsigned char flags = bytes_at(result->variable_header, 7);
	if ( flags & ( 0x01 << 2 ) ){
		result->will_topic = packet_util_build_string(bytes, &index);
		if ( flags & ( 0x01 << 2 ) )
			result->will_message = packet_util_build_string(bytes, &index);
		if ( flags & ( 0x01 << 7 ) ){
			result->username = packet_util_build_string(bytes, &index);
			if ( flags & ( 0x01 << 6 ) )
				result->password = packet_util_build_string(bytes, &index);
		}
	}

	return result;
}

disconnect* assembler_build_to_disconnect(bytes* bytes){
	if( bytes == NULL ) return NULL;
	disconnect* result = (disconnect*) malloc(sizeof(disconnect));
	if( result == NULL ) return NULL;
	result->control_packet = assembler_build_to_control_packet(bytes);
	return result;
}

ping_req* assembler_build_to_ping_req(bytes* bytes){
	if( bytes == NULL ) return NULL;
	ping_req* result = (ping_req*) malloc(sizeof(ping_req));
	result->control_packet = assembler_build_to_control_packet(bytes);
	return result;
}

ping_resp* assembler_build_to_ping_resp(bytes* bytes){
	if( bytes == NULL ) return NULL;
	ping_resp* result = (ping_resp*) malloc(sizeof(ping_resp));
	result->control_packet = assembler_build_to_control_packet(bytes);
	return result;
}

pub_ack* assembler_build_to_pub_ack(bytes* bytes){
	if( bytes == NULL ) return NULL;
	pub_ack* result = (pub_ack*) malloc(sizeof(pub_ack));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PUBACK, CONTROL_PACKET_FLAG_PUBACK, 0);
	return result;
}

pub_comp* assembler_build_to_pub_comp(bytes* bytes){
	if( bytes == NULL ) return NULL;
	pub_comp* result = (pub_comp*) malloc(sizeof(pub_comp));
	result->control_packet = assembler_build_to_control_packet(bytes);
	unsigned int msb_packet_identifier = (unsigned int) (bytes_at(bytes, 2) << 8);
	unsigned int lsb_packet_identifier = (unsigned int) bytes_at(bytes, 3);
	result->packet_identifier = msb_packet_identifier + lsb_packet_identifier;
	return result;
}

publish* assembler_build_to_publish(bytes* bytes){
	if( bytes == NULL ) return NULL;

	publish* result 	= (publish*) malloc(sizeof(publish));
	result->dup       	= control_packet_get_flags(result->control_packet) & 0x08 ? true : false;
	result->qos_level 	= (unsigned char) ( (control_packet_get_flags(result->control_packet) & 0x06) >> 1 );
	result->retain    	= control_packet_get_flags(result->control_packet) & 0x01 ? true : false;

	unsigned int index = 2;
	result->topic_name = packet_util_build_string(bytes, &index);
	if( result->qos_level == PUBLISH_QOS_LEVEL_1 || result->qos_level == PUBLISH_QOS_LEVEL_2 ) {
		unsigned int msb_packet_identifier = (unsigned int) ( bytes_at(bytes,index++) << 8 );
		unsigned int lsb_packet_identifier = (unsigned int) bytes_at(bytes, index++);
		result->packet_identifier = msb_packet_identifier + lsb_packet_identifier;
	}

	result->payload = packet_util_build_string(bytes, &index);

	return result;
}

pub_rec* assembler_build_to_pub_rec(bytes* bytes){
	if( bytes == NULL ) return NULL;
	pub_rec* result = (pub_rec*) malloc(sizeof(pub_rec));
	result->control_packet = assembler_build_to_control_packet(bytes);
	unsigned int msb_packet_identifier = (unsigned int) ( bytes_at(bytes, 2) << 8 );
	unsigned int lsb_packet_identifier = (unsigned int) bytes_at(bytes, 3);
	result->packet_identifier = msb_packet_identifier + lsb_packet_identifier;
	return result;
}

pub_rel* assembler_build_to_pub_rel(bytes* bytes){
	if( bytes == NULL ) return NULL;
	pub_rel* result = (pub_rel*) malloc(sizeof(pub_rel));
	result->control_packet = assembler_build_to_control_packet(bytes);
	unsigned int msb_packet_identifier = (unsigned int) ( bytes_at(bytes, 2) << 8);
	unsigned int lsb_packet_identifier = (unsigned int) bytes_at(bytes, 3);
	result->packet_identifier = msb_packet_identifier + lsb_packet_identifier;
	return result;
}

