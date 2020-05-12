#include "../../Inc/mqtt_client/ping_req.h"


ping_req* ping_req_init(){
	ping_req* result = (ping_req*) malloc(sizeof(ping_req));
	if( result == NULL ) return NULL;
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PINGREQ, CONTROL_PACKET_FLAG_PINGREQ, 0x00);
	if( result->control_packet == NULL )
		ping_req_destroy(result);
	return result;
}

void ping_req_destroy(ping_req* ping_req){
	if( ping_req == NULL ) return;
	free(ping_req);
	ping_req = NULL;
}

bytes* ping_req_to_bytes(ping_req* ping_req){
	if( ping_req == NULL ) return NULL;
	return control_packet_to_bytes(ping_req->control_packet);
}

char* ping_req_to_string(ping_req* ping_req){
	if( ping_req == NULL ) return NULL;
	bytes* bytes = ping_req_to_bytes(ping_req);
	return bytes_to_string(bytes);
}
