#include "../../Inc/mqtt_client/pub_rec_service.h"


pub_rec_service* pub_rec_service_init(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	pub_rec_service* result = (pub_rec_service*) malloc(sizeof(pub_rec_service));
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void pub_rec_service_destroy(pub_rec_service* pub_rec_service){
	if( pub_rec_service == NULL ) return;
	free(pub_rec_service);
	pub_rec_service = NULL;
}

pub_rec* pub_rec_service_create(pub_rec_service* pub_rec_service){
	if( pub_rec_service == NULL ) return NULL;
    session* session = session_get_instance();
    unsigned int packet_identifier = session_get_last_packet_identifier(session);
    pub_rec* result = pub_rec_init(packet_identifier);
    return result;
}

pub_rec* pub_rec_service_read(pub_rec_service* pub_rec_service){
	if( pub_rec_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(pub_rec_service->control_packet_proxy);
	pub_rec* pub_rec = bytes_is_empty(bytes) ? NULL : assembler_build_to_pub_rec(bytes);
    return pub_rec;
}
        
void pub_rec_service_write(pub_rec_service* pub_rec_service, pub_rec* pub_rec){
    if ( pub_rec == NULL ) return;
    bytes* bytes = pub_rec_to_bytes(pub_rec);
    control_packet_proxy_write(pub_rec_service->control_packet_proxy, bytes);
}
