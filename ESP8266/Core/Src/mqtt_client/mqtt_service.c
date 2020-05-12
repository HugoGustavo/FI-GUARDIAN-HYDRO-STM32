#include "../../Inc/mqtt_client/mqtt_service.h"

unsigned char MQTT_SERVICE_QOS_LEVEL_0 = 0x00;

unsigned char MQTT_SERVICE_QOS_LEVEL_1 = 0x01;

unsigned char MQTT_SERVICE_QOS_LEVEL_2 = 0x02;


mqtt_service* mqtt_service_init(control_packet_proxy* control_packet_proxy, connack_service* connack_service, connect_service* connect_service, disconnect_service* disconnect_service, pub_ack_service* pub_ack_service, pub_comp_service* pub_comp_service, publish_service* publish_service, pub_rec_service* pub_rec_service, pub_rel_service* pub_rel_service){
	mqtt_service* result = (mqtt_service*) malloc(sizeof(mqtt_service));
	result->control_packet_proxy   = control_packet_proxy;
	result->connack_service        = connack_service;
	result->connect_service        = connect_service;
	result->disconnect_service     = disconnect_service;
	result->pub_ack_service        = pub_ack_service;
	result->pub_comp_service       = pub_comp_service;
	result->publish_service        = publish_service;
	result->pub_rec_service        = pub_rec_service;
	result->pub_rel_service        = pub_rel_service;
	return result;
}

void mqtt_service_destroy(mqtt_service* mqtt_service){
	control_packet_proxy_destroy(mqtt_service->control_packet_proxy);
	connack_service_destroy(mqtt_service->connack_service);
	connect_service_destroy(mqtt_service->connect_service);
	disconnect_service_destroy(mqtt_service->disconnect_service);
	pub_ack_service_destroy(mqtt_service->pub_ack_service);
	pub_comp_service_destroy(mqtt_service->pub_comp_service);
	publish_service_destroy(mqtt_service->publish_service);
	pub_rec_service_destroy(mqtt_service->pub_rec_service);
	pub_rel_service_destroy(mqtt_service->pub_rel_service);
	free(mqtt_service);
	mqtt_service = NULL;
}

void mqtt_service_connect(mqtt_service* mqtt_service, char* id, char* host, unsigned int port, unsigned int keep_alive, bool clean_session){
    session* session = session_get_instance();
    session_set_id(session, id);
    session_set_host(session, host);
    session_set_port(session, port);
    session_set_keep_alive(session, keep_alive);
    session_set_clean(session, clean_session);

    connect* connect = connect_service_create(mqtt_service->connect_service);
    connect_service_write(mqtt_service->connect_service, connect);
    connack* connack = connack_service_create(mqtt_service->connack_service);

    session_set_connected(session,  session_is_connected(session) && connack_is_connection_accepted(connack) );

    connack_destroy(connack);
    connect_destroy(connect);
}

void mqtt_service_publish(mqtt_service* mqtt_service, char* topic, char* payload, unsigned char qos, bool retain){
	if( mqtt_service == NULL || topic == NULL || payload == NULL ) return;

	session* session = session_get_instance();
	session_set_qos(session, qos);
	session_set_retain(session, retain);

	if( session_is_connected(session) ){
		publish* publish = publish_service_create(mqtt_service->publish_service);
		publish_set_payload(publish, payload);
		publish_set_topic_name(publish, topic);
		publish_service_write(mqtt_service->publish_service, publish);

		if ( session_get_qos(session) == PUBLISH_QOS_LEVEL_1 ){
			session_set_unacknowledged_publish(session, publish);
			pub_ack* pub_ack = pub_ack_service_create(mqtt_service->pub_ack_service);
			session_confirm(session, pub_ack_get_packet_identifier(pub_ack));

			pub_ack_destroy(pub_ack);
		} else if ( session_get_qos(session) == PUBLISH_QOS_LEVEL_2 ){
			session_set_unacknowledged_publish(session, publish);

			pub_rec* pub_rec = pub_rec_service_create(mqtt_service->pub_rec_service);
			session_confirm(session, pub_rec_get_packet_identifier(pub_rec));
			session_set_unacknowledged_pub_rec(session, pub_rec);

			pub_rel* pub_rel = pub_rel_service_create(mqtt_service->pub_rel_service);
			pub_rel_set_packet_identifier(pub_rel, publish_get_packet_identifier(publish));
			pub_rel_service_write(mqtt_service->pub_rel_service, pub_rel);

			pub_comp* pub_comp = pub_comp_service_create(mqtt_service->pub_comp_service);
			session_confirm(session, pub_comp_get_packet_identifier(pub_comp));

			pub_comp_destroy(pub_comp);
			pub_rel_destroy(pub_rel);
			pub_rec_destroy(pub_rec);
		}

		publish_destroy(publish);
	}
}

void mqtt_service_disconnect(mqtt_service* mqtt_service){
	if( mqtt_service == NULL ) return;

    disconnect* disconnect = disconnect_service_create(mqtt_service->disconnect_service);
    disconnect_service_write(mqtt_service->disconnect_service, disconnect);

    disconnect_destroy(disconnect);
}

void mqtt_service_wait_to_send(mqtt_service* mqtt_service, unsigned int milliseconds){
	if( mqtt_service == NULL ) return;
    HAL_Init();
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    HAL_IncTick();
    HAL_GetTick();
    HAL_Delay(milliseconds);
}
