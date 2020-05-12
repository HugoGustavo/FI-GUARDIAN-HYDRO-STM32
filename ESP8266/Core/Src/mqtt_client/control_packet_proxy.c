#include "../../Inc/mqtt_client/control_packet_proxy.h"

control_packet_proxy* control_packet_proxy_init(wifi* wifi, ping_req_service* ping_req_service, ping_resp_service* ping_resp_service, unsigned int connection_attempts){
	if( wifi == NULL || ping_req_service == NULL ||  ping_resp_service == NULL || connection_attempts == 0 ) return NULL;
	control_packet_proxy* result = (control_packet_proxy*) malloc(sizeof(control_packet_proxy));
	if( result == NULL ) return NULL;
	result->wifi = wifi;
	result->ping_req_service = ping_req_service;
	result->ping_resp_service = ping_resp_service;
	result->connection_attempts = connection_attempts;
	return result;
}

void control_packet_proxy_destroy(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return;
	free(control_packet_proxy);
	control_packet_proxy = NULL;
}

void control_packet_proxy_connect(control_packet_proxy* control_packet_proxy, char* ip, unsigned int port){
	if( control_packet_proxy == NULL ) return;
	wifi_connect(control_packet_proxy->wifi, ip, port);
}

void control_packet_proxy_disconnect(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return;
	wifi_disconnect(control_packet_proxy->wifi);
}

bool control_packet_proxy_is_connected(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return false;
	return wifi_is_connected(control_packet_proxy->wifi);
}

bytes* control_packet_proxy_read(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	return wifi_read(control_packet_proxy->wifi);
}

void control_packet_proxy_write(control_packet_proxy* control_packet_proxy, bytes* bytes){
	if(control_packet_proxy == NULL || bytes == NULL ) return;
	session* session = session_get_instance();
	if( session_is_expired(session) ){
		ping_req* ping_req = ping_req_service_create(control_packet_proxy->ping_req_service);
		ping_req_service_write(control_packet_proxy->ping_req_service, ping_req);

		ping_resp* ping_resp = ping_resp_service_read(control_packet_proxy->ping_resp_service);
		if( ping_resp == NULL ) return;
	}
	wifi_write(control_packet_proxy->wifi, bytes);
	session_signal_time_last_package(session);
}
