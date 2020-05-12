#ifndef CONTROL_PACKET_PROXY_H
#define CONTROL_PACKET_PROXY_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/wifi.h>
#include <util/logger.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/ping_req_service.h>
#include <mqtt_client/ping_resp_service.h>
#include <mqtt_client/session.h>
#include <mqtt_client/packet_util.h>

typedef struct control_packet_proxy{
	wifi* 				wifi;
	ping_req_service* 	ping_req_service;
	ping_resp_service* 	ping_resp_service;
	unsigned int 		connection_attempts;
} control_packet_proxy;

control_packet_proxy* control_packet_proxy_init(wifi* wifi, ping_req_service* ping_req_service, ping_resp_service* ping_resp_service, unsigned int connectio_attempts);

void control_packet_proxy_destroy(control_packet_proxy* control_packet_proxy);

void control_packet_proxy_connect(control_packet_proxy* control_packet_proxy, char* ip, unsigned int port);

void control_packet_proxy_disconnect(control_packet_proxy* control_packet_proxy);

bool control_packet_proxy_is_connected(control_packet_proxy* control_packet_proxy);

bytes* control_packet_proxy_read(control_packet_proxy* control_packet_proxy);

void control_packet_proxy_write(control_packet_proxy* control_packet_proxy, bytes* bytes);

#endif
