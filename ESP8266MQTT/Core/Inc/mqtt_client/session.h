#ifndef SESSION_H
#define SESSION_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <util/logger.h>
#include <mqtt_client/pub_ack.h>
#include <mqtt_client/pub_rec.h>
#include <mqtt_client/pub_rel.h>
#include <mqtt_client/publish.h>

typedef struct __attribute__((__packed__)) session {
    char*			id;
    bool			clean;
    char*			host;
    unsigned int    port;
    unsigned int    keep_alive;
    unsigned char	qos;
    bool			retain;
    unsigned long   time_last_package;
    bool			connected;
    char*			username;
    char*			password;

    publish*		unacknowledged_publish;
    pub_rel*		unacknowledged_pub_rel;
    pub_rec*		unacknowledged_pub_rec;

    unsigned int	packet_identifier;
    unsigned int	last_packet_identifier;

} session;

extern unsigned char SESSION_QOS_LEVEL_0;

extern unsigned char SESSION_QOS_LEVEL_1;

extern unsigned char SESSION_QOS_LEVEL_2;

extern session* session_instance;

session* session_get_instance();

void session_destroy(session* session);

char* session_get_id(session* session);

void session_set_id(session* session, char* id);

bool session_is_clean(session* session);

void session_set_clean(session* session, bool clean);

char* session_get_host(session* session);

void session_set_host(session* session, char* host);

unsigned int session_get_port(session* session);

void session_set_port(session* session, unsigned int port);

unsigned int session_get_keep_alive(session* session);

void session_set_keep_alive(session* session, unsigned int keep_alive);

unsigned char session_get_qos(session* session);

void session_set_qos(session* session, unsigned char qos);

bool session_is_retain(session* session);

void session_set_retain(session* session, bool retain);

unsigned long session_get_time_last_package(session* session);

void session_set_time_last_package(session* session, unsigned long time_last_package);

bool session_is_connected(session* session);

void session_set_connected(session* session, bool connected);

char* session_get_username(session* session);

void session_set_username(session* session, char* username);

char* session_get_password(session* session);

void session_set_password(session* session, char* password);

void session_signal_time_last_package(session* session);

bool session_is_expired(session* session);

void session_set_unacknowledged_publish(session* session, publish* unacknowledged_publish);

void session_set_unacknowledged_pub_rel(session* session, pub_rel* unacknowledged_pub_rel);

void session_set_unacknowledged_pub_rec(session* session, pub_rec* unacknowledged_pub_rec);

void session_confirm(session* session, unsigned int packet_identifier);

unsigned int session_generate_packet_identifier(session* session);

unsigned int session_get_last_packet_identifier(session* session);

void session_reset(session* session);

#endif
