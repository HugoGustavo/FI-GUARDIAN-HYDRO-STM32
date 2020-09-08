#include "../../Inc/mqtt_client/connack_service.h"

connack_service* connack_service_init(control_packet_proxy* control_packet_proxy){
	if(control_packet_proxy == NULL) return NULL;
	connack_service* result = (connack_service*) malloc(sizeof(connack_service));
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void connack_service_destroy(connack_service* connack_service){
	if( connack_service == NULL ) return;
	connack_service->control_packet_proxy = NULL;
	free(connack_service);
	connack_service = NULL;
}

connack* connack_service_create(connack_service* connack_service){
	if( connack_service == NULL ) return NULL;
	session* session = session_get_instance();
	bool clean_session = session_is_clean(session);
	connack* result = connack_init(clean_session, CONNACK_RETURN_CODE_CONNECTION_ACCEPTED);
	return result;
}

connack* connack_service_read(connack_service* connack_service){
	if( connack_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(connack_service->control_packet_proxy);
	connack* result = bytes_is_empty(bytes) ? NULL : assembler_build_to_connack(bytes);
	bytes_destroy(bytes);
	return result;
}

void connack_service_write(connack_service* connack_service, connack* connack){
	if( connack_service == NULL || connack == NULL ) return;
	bytes* bytes = connack_to_bytes(connack);
	control_packet_proxy_write(connack_service->control_packet_proxy, bytes);
	bytes_destroy(bytes);
}
