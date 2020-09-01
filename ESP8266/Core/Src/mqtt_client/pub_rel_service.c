#include "../../Inc/mqtt_client/pub_rel_service.h"

pub_rel_service* pub_rel_service_init(control_packet_proxy* control_packet_proxy){
	pub_rel_service* result = (pub_rel_service*) malloc(sizeof(pub_rel_service));
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void pub_rel_service_destroy(pub_rel_service* pub_rel_service){
	if( pub_rel_service == NULL ) return;
	pub_rel_service->control_packet_proxy = NULL;
	free(pub_rel_service);
	pub_rel_service = NULL;
}

pub_rel* pub_rel_service_create(pub_rel_service* pub_rel_service){
	if( pub_rel_service == NULL ) return NULL;
	session* session = session_get_instance();
	unsigned int packet_identifier = session_get_last_packet_identifier(session);
	pub_rel* result= pub_rel_init(packet_identifier);
	return result;
}

pub_rel* pub_rel_service_read(pub_rel_service* pub_rel_service){
	if( pub_rel_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(pub_rel_service->control_packet_proxy);
	pub_rel* pub_rel = bytes_is_empty(bytes) ? NULL : assembler_build_to_pub_rel(bytes);
	bytes_destroy(bytes);
	return pub_rel;
}

void pub_rel_service_write(pub_rel_service* pub_rel_service, pub_rel* pub_rel){
	if ( pub_rel_service == NULL ||  pub_rel == NULL ) return;
	bytes* bytes = pub_rel_to_bytes(pub_rel);
	control_packet_proxy_write(pub_rel_service->control_packet_proxy, bytes);
	bytes_destroy(bytes);
}
