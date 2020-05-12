#include "../../Inc/mqtt_client/ping_req_service.h"


ping_req_service* ping_req_service_init(wifi* wifi){
	if( wifi == NULL ) return NULL;
	ping_req_service* result = (ping_req_service*) malloc(sizeof(ping_req_service));
	if( result == NULL ) return NULL;
	result->wifi = wifi;
	return result;
}

void ping_req_service_destroy(ping_req_service* ping_req_service){
	if( ping_req_service == NULL ) return;
	free(ping_req_service);
	ping_req_service = NULL;
}

ping_req* ping_req_service_create(ping_req_service* ping_req_service){
	if( ping_req_service == NULL ) return NULL;
	return ping_req_init();
}

ping_req* ping_req_service_read(ping_req_service* ping_req_service){
	if( ping_req_service == NULL ) return NULL;
    bytes* bytes = wifi_read(ping_req_service->wifi);
    ping_req* ping_req = bytes_is_empty(bytes)? NULL : ping_req_init(bytes);
    return ping_req;
}

void ping_req_service_write(ping_req_service* ping_req_service, ping_req* ping_req){
	if( ping_req == NULL ) return;
	wifi_write(ping_req_service->wifi, ping_req_to_bytes(ping_req));
}
