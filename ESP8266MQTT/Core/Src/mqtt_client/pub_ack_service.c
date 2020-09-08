#include "../../Inc/mqtt_client/pub_ack_service.h"


pub_ack_service* pub_ack_service_init(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	pub_ack_service* result = (pub_ack_service*) malloc(sizeof(pub_ack_service));
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void pub_ack_service_destroy(pub_ack_service* pub_ack_service){
	if( pub_ack_service == NULL ) return;
	pub_ack_service->control_packet_proxy = NULL;
	free(pub_ack_service);
	pub_ack_service = NULL;
}

pub_ack* pub_ack_service_create(pub_ack_service* pub_ack_service){
	if( pub_ack_service == NULL ) return NULL;
	session* session = session_get_instance();
	unsigned int packet_identifier = session_get_last_packet_identifier(session);
	pub_ack* pub_ack = pub_ack_init(packet_identifier);
	return pub_ack;
}

pub_ack* pub_ack_service_read(pub_ack_service* pub_ack_service){
	if( pub_ack_service == NULL ) return NULL;
    bytes* bytes = control_packet_proxy_read(pub_ack_service->control_packet_proxy);
    pub_ack* pub_ack = bytes_is_empty(bytes) ? NULL : assembler_build_to_pub_ack(bytes);
    bytes_destroy(bytes);
    return pub_ack;
}

void pub_ack_service_write(pub_ack_service* pub_ack_service, pub_ack* pub_ack){
    if ( pub_ack_service == NULL || pub_ack == NULL ) return;
    bytes* bytes = pub_ack_to_bytes(pub_ack);
    control_packet_proxy_write(pub_ack_service->control_packet_proxy, bytes);
    bytes_destroy(bytes);
}
