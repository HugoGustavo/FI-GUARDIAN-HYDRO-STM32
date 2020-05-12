#include "../../Inc/mqtt_client/disconnect.h"


disconnect* disconnect_init(){
	disconnect* result = (disconnect*) malloc(sizeof(disconnect));
	if( result == NULL ) return NULL;
	result->control_packet = control_packet_init(CONTROL_PACKET_TYPE_DISCONNECT, CONTROL_PACKET_FLAG_DISCONNECT, 0x00);
	if( result->control_packet == NULL ){
		disconnect_destroy(result);
		return NULL;
	}

	control_packet_set_remaining_length(result->control_packet, 0x00);
	return result;
}

void disconnect_destroy(disconnect* disconnect){
	free(disconnect);
	disconnect = NULL;
}

bytes* disconnect_to_bytes(disconnect* disconnect){
	if( disconnect == NULL ) return NULL;
	return control_packet_to_bytes(disconnect->control_packet);
}

char* disconnect_to_string(disconnect* disconnect){
	if( disconnect == NULL ) return NULL;
	bytes* bytes = disconnect_to_bytes(disconnect);
	return bytes_to_string(bytes);
}
