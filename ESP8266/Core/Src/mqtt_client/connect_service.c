#include <mqtt_client/connect_service.h>

connect_service* connect_service_init(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	connect_service* result = (connect_service*) malloc(sizeof(connect_service));
	if( result == NULL ) return NULL;
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void connect_service_destroy(connect_service* connect_service){
	if( connect_service == NULL ) return;
	free(connect_service);
	connect_service = NULL;
}

connect* connect_service_create(connect_service* connect_service){
	if( connect_service == NULL ) return NULL;

	session* session 		= session_get_instance();
	bool has_username		= string_util_is_empty(session_get_username(session)) ? false : true;
	bool has_password       = string_util_is_empty(session_get_password(session)) ? false : true;
	bool is_id_empty        = string_util_is_empty(session_get_id(session));
	bool clean              = is_id_empty ? true : session_is_clean(session);
	unsigned int keep_alive = session_get_keep_alive(session);

	connect* connect = NULL;
	unsigned char qos = session_get_qos(session);
	if ( qos == CONNECT_QOS_LEVEL_0){
		connect = connect_init(has_username, has_password, false, CONNECT_QOS_LEVEL_0, false, clean, keep_alive);
	} else if ( qos == CONNECT_QOS_LEVEL_1 ){
		connect = connect_init(has_username, has_password, false, CONNECT_QOS_LEVEL_1, false, clean, keep_alive);
	} else if ( qos == CONNECT_QOS_LEVEL_2 ){
		connect = connect_init(has_username, has_password, false, CONNECT_QOS_LEVEL_2, false, clean, keep_alive);
	} else {
		connect = connect_init(has_username, has_password, false, CONNECT_QOS_LEVEL_0, false, clean, keep_alive);
	}

	if ( has_username ) connect_set_username(connect, session_get_username(session));
	if ( has_password ) connect_set_password(connect, session_get_password(session));
	if ( ! is_id_empty ) connect_set_client_identifier(connect, session_get_id(session));

	return connect;
}

connect* connect_service_read(connect_service* connect_service){
	if( connect_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(connect_service->control_packet_proxy);
	connect* connect = bytes_is_empty(bytes) ? NULL : assembler_build_to_connect(bytes);
	return connect;
}

void connect_service_write(connect_service* connect_service, connect* connect){
	if ( connect_service == NULL || connect == NULL ) return;
	session* session = session_get_instance();
	if ( ! session_is_connected(session) ){
		char* host = session_get_host(session);
		unsigned int port = session_get_port(session);
		control_packet_proxy_connect(connect_service->control_packet_proxy, host, port);
		bool connected = control_packet_proxy_is_connected(connect_service->control_packet_proxy);
		session_set_connected(session, connected);
	}
	bytes* bytes = connect_to_bytes(connect);
	control_packet_proxy_write(connect_service->control_packet_proxy, bytes);
}
