#include "../../Inc/mqtt_client/publish_service.h"


publish_service* publish_service_init(control_packet_proxy* control_packet_proxy){
	if( control_packet_proxy == NULL ) return NULL;
	publish_service* result = (publish_service*) malloc(sizeof(publish_service));
	if( result == NULL ) return NULL;
	result->control_packet_proxy = control_packet_proxy;
	return result;
}

void publish_service_destroy(publish_service* publish_service){
	if( publish_service == NULL ) return;
	free(publish_service);
	publish_service = NULL;
}

publish* publish_service_create(publish_service* publish_service){
	 bool           dup         = false;
	 session*       session     = session_get_instance();
	 unsigned char	qos         = session_get_qos(session);
	 bool           retain      = session_is_retain(session);

	 publish* publish = NULL;
	 if( qos == PUBLISH_QOS_LEVEL_0 ){
		 publish = publish_init(dup, PUBLISH_QOS_LEVEL_0, retain);
	 } else if ( qos == PUBLISH_QOS_LEVEL_1 ){
		 publish = publish_init(dup, PUBLISH_QOS_LEVEL_1, retain);
		 publish_set_packet_identifier(publish, session_generate_packet_identifier(session));
	 } else if ( qos == PUBLISH_QOS_LEVEL_2 ){
 		 publish = publish_init(dup, PUBLISH_QOS_LEVEL_2, retain);
 		 publish_set_packet_identifier(publish, session_generate_packet_identifier(session));
	 } else {
		 publish = publish_init(dup, PUBLISH_QOS_LEVEL_0, retain);
	 }

	 return publish;
}

publish* publish_service_read(publish_service* publish_service){
	if( publish_service == NULL ) return NULL;
	bytes* bytes = control_packet_proxy_read(publish_service->control_packet_proxy);
	publish* publish = bytes_is_empty(bytes) ? NULL : assembler_build_to_publish(bytes);
	return publish;
}

void publish_service_write(publish_service* publish_service, publish* publish){
	if ( publish_service == NULL ||  publish == NULL ) return;
	bytes* bytes = publish_to_bytes(publish);
	control_packet_proxy_write(publish_service->control_packet_proxy, bytes);
}

