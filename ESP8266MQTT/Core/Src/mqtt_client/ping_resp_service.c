#include "../../Inc/mqtt_client/ping_resp_service.h"


ping_resp_service* ping_resp_service_init(wifi* wifi){
	if( wifi == NULL ) return NULL;
	ping_resp_service* result = (ping_resp_service*) malloc(sizeof(ping_resp_service));
	result->wifi = wifi;
	return result;
}

void ping_resp_service_destroy(ping_resp_service* ping_resp_service){
	if( ping_resp_service == NULL ) return;
	ping_resp_service->wifi = NULL;
	free(ping_resp_service);
	ping_resp_service = NULL;
}

ping_resp* ping_resp_service_create(ping_resp_service* ping_resp_service){
	if( ping_resp_service == NULL ) return NULL;
	return ping_resp_init();
}

ping_resp* ping_resp_service_read(ping_resp_service* ping_resp_service){
	if( ping_resp_service == NULL ) return NULL;
    bytes* bytes = wifi_read(ping_resp_service->wifi);
    ping_resp* ping_resp = bytes_is_empty(bytes)? NULL : ping_resp_init(bytes);
    return ping_resp;
}

void ping_resp_service_write(ping_resp_service* ping_resp_service, ping_resp* ping_resp){
	if( ping_resp == NULL ) return;
	bytes* bytes = ping_resp_to_bytes(ping_resp);
	wifi_write(ping_resp_service->wifi, bytes);
	bytes_destroy(bytes);
}
