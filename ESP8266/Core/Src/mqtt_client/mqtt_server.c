#include "../../Inc/mqtt_client/mqtt_server.h"

mqtt_server* mqtt_server_init(){
	mqtt_server* result = (mqtt_server*) malloc(sizeof(mqtt_server));
	result->connect 	= NULL;
	result->connack 	= NULL;
	result->publish 	= NULL;
	result->pub_rec 	= NULL;
	result->pub_rel 	= NULL;
	result->pub_comp 	= NULL;

	return result;
}

void mqtt_server_destroy(mqtt_server* mqtt_server){
	if( mqtt_server == NULL ) return;

	connect_destroy(mqtt_server->connect);
	mqtt_server->connect = NULL;

	connack_destroy(mqtt_server->connack);
	mqtt_server->connack = NULL;

	publish_destroy(mqtt_server->publish);
	mqtt_server->publish = NULL;

	pub_rec_destroy(mqtt_server->pub_rec);
	mqtt_server->pub_rec = NULL;

	pub_rel_destroy(mqtt_server->pub_rel);
	mqtt_server->pub_rel = NULL;

	pub_comp_destroy(mqtt_server->pub_comp);
	mqtt_server->pub_comp = NULL;

	free(mqtt_server);
	mqtt_server = NULL;
}

void mqtt_server_request(mqtt_server* mqtt_server, bytes* bytes){
	if( mqtt_server == NULL || bytes == NULL) return;

	if( mqtt_server->connect == NULL ){
		mqtt_server->connect = assembler_build_to_connect(bytes);
	} else if ( mqtt_server->publish == NULL ){
		mqtt_server->publish = assembler_build_to_publish(bytes);
	} else {
		mqtt_server->pub_rel = assembler_build_to_pub_rel(bytes);
	}
}

bytes* mqtt_server_response(mqtt_server* mqtt_server){
	if( mqtt_server == NULL ) return NULL;

	bytes* result = NULL;
    if( mqtt_server->connack == NULL ){
    	mqtt_server->connack = connack_init(false, CONNACK_RETURN_CODE_CONNECTION_ACCEPTED);
    	result = connack_to_bytes(mqtt_server->connack);
    } else if ( mqtt_server->pub_rec == NULL ){
    	mqtt_server->pub_rec = pub_rec_init(publish_get_packet_identifier(mqtt_server->publish));
    	result = pub_rec_to_bytes(mqtt_server->pub_rec);
    } else if ( mqtt_server->pub_comp == NULL ){
    	mqtt_server->pub_comp = pub_comp_init(pub_rec_get_packet_identifier(mqtt_server->pub_rec));
    	result = pub_comp_to_bytes(mqtt_server->pub_comp);
    }

    return result;
}

void reset(mqtt_server* mqtt_server){
	if( mqtt_server == NULL ) return;
	connect_destroy(mqtt_server->connect);
	connack_destroy(mqtt_server->connack);
	publish_destroy(mqtt_server->publish);
	pub_rec_destroy(mqtt_server->pub_rec);
	pub_rel_destroy(mqtt_server->pub_rel);
	pub_comp_destroy(mqtt_server->pub_comp);
}
