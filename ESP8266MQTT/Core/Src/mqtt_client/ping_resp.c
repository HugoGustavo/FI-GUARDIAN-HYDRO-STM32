#include "../../Inc/mqtt_client/ping_resp.h"


ping_resp* ping_resp_init(){
	ping_resp* result = (ping_resp*) malloc(sizeof(ping_resp));
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_PINGRESP, CONTROL_PACKET_FLAG_PINGRESP, 0x00);
	return result;
}

void ping_resp_destroy(ping_resp* ping_resp){
	if( ping_resp == NULL ) return;

	ping_resp->control_packet = NULL;

	free(ping_resp);
	ping_resp = NULL;
}

bytes* ping_resp_to_bytes(ping_resp* ping_resp){
	if( ping_resp == NULL ) return NULL;
	bytes* bytes = control_packet_to_bytes(ping_resp->control_packet);
	return bytes;
}

char* ping_resp_to_string(ping_resp* ping_resp){
	if( ping_resp == NULL ) return NULL;
	bytes* bytes = ping_resp_to_bytes(ping_resp);
	return bytes_to_string(bytes);
}
