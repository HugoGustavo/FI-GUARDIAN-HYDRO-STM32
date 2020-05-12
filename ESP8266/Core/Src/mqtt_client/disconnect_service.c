#include "../../Inc/mqtt_client/disconnect_service.h"


disconnect_service* disconnect_service_init(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	disconnect_service* result = (disconnect_service*) malloc(sizeof(disconnect_service));
	if( result == NULL ) return NULL;
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void disconnect_service_destroy(disconnect_service* disconnect_service){
	if( disconnect_service == NULL ) return;
	free(disconnect_service);
	disconnect_service = NULL;
}

disconnect* disconnect_service_create(disconnect_service* disconnect_service){
	if( disconnect_service == NULL ) return NULL;
	return disconnect_init();
}

disconnect* disconnect_service_read(disconnect_service* disconnect_service){
	if( disconnect_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(disconnect_service->control_packet_proxy);
	disconnect* disconnect = bytes_is_empty(bytes) ? NULL : disconnect_init(bytes);
	return disconnect;
}

void disconnect_service_write(disconnect_service* disconnect_service, disconnect* disconnect){
	if( disconnect_service == NULL || disconnect == NULL ) return;
	bytes* bytes = disconnect_to_bytes(disconnect);
	control_packet_proxy_write(disconnect_service->control_packet_proxy, bytes);
	control_packet_proxy_disconnect(disconnect_service->control_packet_proxy);
	session* session = session_get_instance();
	session_reset(session);
}
