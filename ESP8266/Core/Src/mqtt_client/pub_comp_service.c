#include "../../Inc/mqtt_client/pub_comp_service.h"


pub_comp_service* pub_comp_service_init(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	pub_comp_service* result = (pub_comp_service*) malloc(sizeof(pub_comp_service));
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void pub_comp_service_destroy(pub_comp_service* pub_comp_service){
	if( pub_comp_service == NULL ) return;
	pub_comp_service->control_packet_proxy = NULL;
	free(pub_comp_service);
	pub_comp_service = NULL;
}

pub_comp* pub_comp_service_create(pub_comp_service* pub_comp_service){
	if( pub_comp_service == NULL ) return NULL;
    session* session = session_get_instance();
    unsigned int packet_identifier = session_get_last_packet_identifier(session);
    pub_comp* pub_comp = pub_comp_init(packet_identifier);
    return pub_comp;
}

pub_comp* pub_comp_service_read(pub_comp_service* pub_comp_service){
    if( pub_comp_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(pub_comp_service->control_packet_proxy);
    pub_comp* pub_comp = bytes_is_empty(bytes) ? NULL : assembler_build_to_pub_comp(bytes);
    bytes_destroy(bytes);
    return pub_comp;
}

void pub_comp_service_write(pub_comp_service* pub_comp_service, pub_comp* pub_comp){
	if( pub_comp_service == NULL || pub_comp == NULL ) return;
	bytes* bytes = pub_comp_to_bytes(pub_comp);
	control_packet_proxy_write(pub_comp_service->control_packet_proxy, bytes);
	bytes_destroy(bytes);
}
