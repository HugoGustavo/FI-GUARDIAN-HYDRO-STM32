#include "../../Inc/mqtt_client/mqtt_client.h"

unsigned char MQTT_CLIENT_QOS_LEVEL_0 = 0x00;

unsigned char MQTT_CLIENT_QOS_LEVEL_1 = 0x01;

unsigned char MQTT_CLIENT_QOS_LEVEL_2 = 0x02;


mqtt_client* mqtt_client_init(esp8266* esp8266){
	if( esp8266 == NULL ) return NULL;

	mqtt_client* result = (mqtt_client*) malloc(sizeof(mqtt_client));
	if ( result == NULL ) return NULL;

	result->wifi 					= wifi_init(esp8266, 1000);
	result->ping_req_service 		= ping_req_service_init(result->wifi);
	result->ping_resp_service		= ping_resp_service_init(result->wifi);
	result->control_packet_proxy 	= control_packet_proxy_init(result->wifi, result->ping_req_service, result->ping_resp_service, 3);
	result->connack_service			= connack_service_init(result->control_packet_proxy);
	result->connect_service			= connect_service_init(result->control_packet_proxy);
	result->disconnect_service		= disconnect_service_init(result->control_packet_proxy);
	result->pub_ack_service			= pub_ack_service_init(result->control_packet_proxy);
	result->pub_comp_service		= pub_comp_service_init(result->control_packet_proxy);
	result->publish_service			= publish_service_init(result->control_packet_proxy);
	result->pub_rec_service			= pub_rec_service_init(result->control_packet_proxy);
	result->pub_rel_service			= pub_rel_service_init(result->control_packet_proxy);
	result->mqtt_service			= mqtt_service_init(result->control_packet_proxy, result->connack_service, result->connect_service, result->disconnect_service, result->pub_ack_service, result->pub_comp_service, result->publish_service, result->pub_rec_service, result->pub_rel_service);

	if( result->wifi == NULL || result->ping_req_service == NULL || result->ping_resp_service == NULL ||
		result->control_packet_proxy == NULL || result->connack_service == NULL || result->connect_service == NULL ||
		result->disconnect_service == NULL || result->pub_ack_service == NULL || result->pub_comp_service == NULL ||
		result->publish_service == NULL || result->pub_rec_service == NULL || result->pub_rel_service == NULL ){

		mqtt_client_destroy(result);

		return NULL;
	}

	return result;
}

void mqtt_client_destroy(mqtt_client* mqtt_client){
	if ( mqtt_client == NULL ) return;

	wifi_destroy(mqtt_client->wifi);
	ping_req_service_destroy(mqtt_client->ping_req_service);
	ping_resp_service_destroy(mqtt_client->ping_resp_service);
	control_packet_proxy_destroy(mqtt_client->control_packet_proxy);
	connack_service_destroy(mqtt_client->connack_service);
	connect_service_destroy(mqtt_client->connect_service);
	disconnect_service_destroy(mqtt_client->disconnect_service);
	pub_ack_service_destroy(mqtt_client->pub_ack_service);
	pub_comp_service_destroy(mqtt_client->pub_comp_service);
	publish_service_destroy(mqtt_client->publish_service);
	pub_rec_service_destroy(mqtt_client->pub_rec_service);
	pub_rel_service_destroy(mqtt_client->pub_rel_service);
	mqtt_service_destroy(mqtt_client->mqtt_service);

	free(mqtt_client);
	mqtt_client = NULL;
}

void mqtt_client_connect(mqtt_client* mqtt_client, char* id, char* host, unsigned int port, unsigned int keep_alive, bool clean_session){
	if( mqtt_client == NULL ) return;
	mqtt_service_connect(mqtt_client->mqtt_service, id, host, port, keep_alive, clean_session);
}

void mqtt_client_publish(mqtt_client* mqtt_client, char* topic, char* payload, unsigned char qos, bool retain){
	if( mqtt_client == NULL ) return;
	mqtt_service_publish(mqtt_client->mqtt_service, topic, payload, qos, retain);
}

void mqtt_client_disconnect(mqtt_client* mqtt_client){
	if( mqtt_client == NULL ) return;
	mqtt_service_disconnect(mqtt_client->mqtt_service);
}
