#include "../../Inc/mqtt_client/session.h"


session* session_instance = NULL;

unsigned char SESSION_QOS_LEVEL_0 = 0x00;

unsigned char SESSION_QOS_LEVEL_1 = 0x01;

unsigned char SESSION_QOS_LEVEL_2 = 0x02;

session* session_get_instance(){
	if( session_instance == NULL ){
		session_instance = (session*) malloc(sizeof(session));
		session_instance->id = NULL;
		session_instance->clean = false;
		session_instance->host = NULL;
		session_instance->port = 1883;
		session_instance->keep_alive = 60;
		session_instance->qos = SESSION_QOS_LEVEL_0;
		session_instance->retain = false;
		session_instance->time_last_package = clock() / 1000;
		session_instance->connected = false;
		session_instance->username = NULL;
		session_instance->password = NULL;

		session_instance->unacknowledged_publish = NULL;
		session_instance->unacknowledged_pub_rel = NULL;
		session_instance->unacknowledged_pub_rec = NULL;

		session_instance->packet_identifier = 0;
		session_instance->last_packet_identifier = 0;
	}

	return session_instance;
}

void session_destroy(session* session){
	if( session == NULL ) return;
	session_reset(session);
	free(session);
	session = NULL;
}

char* session_get_id(session* session){
	return session == NULL ? NULL : session->id;
}

void session_set_id(session* session, char* id){
	if( session == NULL ) return;
	session->id = id;
}

bool session_is_clean(session* session){
	return session == NULL ? false : session->clean;
}

void session_set_clean(session* session, bool clean){
	if( session == NULL ) return;
	session->clean = clean;
}

char* session_get_host(session* session){
	return session == NULL ? NULL : session->host;
}

void session_set_host(session* session, char* host){
	if( session == NULL ) return;
	session->host = host;
}

unsigned int session_get_port(session* session){
	return session == NULL ? 1883 : session->port;
}

void session_set_port(session* session, unsigned int port){
	if( session == NULL ) return;
	session->port = port;
}

unsigned int session_get_keep_alive(session* session){
	return session == NULL ? 60 : session->keep_alive;
}

void session_set_keep_alive(session* session, unsigned int keep_alive){
	if( session == NULL ) return;
	session->keep_alive = keep_alive;
}

unsigned char session_get_qos(session* session){
	return session == NULL ? SESSION_QOS_LEVEL_0 : session->qos;
}

void session_set_qos(session* session, unsigned char qos){
	if( session == NULL ) return;
	session->qos = qos;
}

bool session_is_retain(session* session){
	return session == NULL ? false : session->retain;
}

void session_set_retain(session* session, bool retain){
	if ( session == NULL ) return;
	session->retain = retain;
}

unsigned long session_get_time_last_package(session* session){
	return session == NULL ? 0 : session->time_last_package;
}

void session_set_time_last_package(session* session, unsigned long time_last_package){
	if ( session == NULL ) return;
	session->time_last_package = time_last_package;
}

bool session_is_connected(session* session){
	return session == NULL ? false : session->connected;
}

void session_set_connected(session* session, bool connected){
	if ( session == NULL ) return;
	session->connected = connected;
}

char* session_get_username(session* session){
	return session == NULL ? NULL : session->username;
}

void session_set_username(session* session, char* username){
	if ( session == NULL ) return;
	session->username = username;
}

char* session_get_password(session* session){
	return session == NULL ? NULL : session->password;
}

void session_set_password(session* session, char* password){
	if( session == NULL ) return;
	session->password = password;
}

void session_signal_time_last_package(session* session){
	if ( session == NULL ) return;
	session->time_last_package = clock() / 1000;
}

bool session_is_expired(session* session){
	clock_t now = clock() / 1000;
	return (( now - session->time_last_package ) > session->keep_alive );
}

void session_set_unacknowledged_publish(session* session, publish* unacknowledged_publish){
	if( session == NULL || unacknowledged_publish == NULL ) return;
	session->unacknowledged_publish = unacknowledged_publish;
}

void session_set_unacknowledged_pub_rel(session* session, pub_rel* unacknowledged_pub_rel){
	if( session == NULL || unacknowledged_pub_rel == NULL ) return;
	session->unacknowledged_pub_rel = unacknowledged_pub_rel;
}

void session_set_unacknowledged_pub_rec(session* session, pub_rec* unacknowledged_pub_rec){
	if( session == NULL || unacknowledged_pub_rec == NULL ) return;
	session->unacknowledged_pub_rec = unacknowledged_pub_rec;
}

void session_confirm(session* session, unsigned int packet_identifier){
	if( session == NULL ) return;

    if( session->unacknowledged_publish != NULL && publish_get_packet_identifier(session->unacknowledged_publish) == packet_identifier )
    	session->unacknowledged_publish = NULL;

    if( session->unacknowledged_pub_rel != NULL && pub_rel_get_packet_identifier(session->unacknowledged_pub_rel) == packet_identifier )
        session->unacknowledged_pub_rel = NULL;

    if( session->unacknowledged_pub_rec != NULL && pub_rec_get_packet_identifier(session->unacknowledged_pub_rec) == packet_identifier )
    	session->unacknowledged_pub_rec = NULL;
}

unsigned int session_generate_packet_identifier(session* session){
	if( session == NULL ) return 0;
	unsigned int result = session->packet_identifier;
	session->packet_identifier = (session->packet_identifier + 1) % 65534;
	//if(session->packet_identifier == 0) session->packet_identifier = 1;
	return result;
}

unsigned int session_get_last_packet_identifier(session* session){
	if( session == NULL ) return 0;
	return session->packet_identifier == 0 ? session->packet_identifier - 1 : 65533;
}

void session_reset(session* session){
	if( session == NULL ) return;

	session->id                            = NULL;
	session->clean                         = true;
	session->host                          = NULL;
	session->port                          = 1883;
	session->keep_alive                    = 60;
	session->qos                           = SESSION_QOS_LEVEL_0;
	session->retain                        = NULL;
	session->time_last_package             = 0;
	session->connected                     = false;
	session->username                      = NULL;
	session->password                      = NULL;
	session->unacknowledged_publish        = NULL;
	session->unacknowledged_pub_rel        = NULL;
	session->unacknowledged_pub_rec        = NULL;
	session->packet_identifier             = 0;
}
