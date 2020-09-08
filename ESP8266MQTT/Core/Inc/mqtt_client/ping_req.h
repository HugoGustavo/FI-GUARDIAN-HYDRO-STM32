#ifndef PING_REQ_H
#define PING_REQ_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/control_packet.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) ping_req {
	control_packet* control_packet;
} ping_req;

ping_req* ping_req_init();

void ping_req_destroy(ping_req* ping_req);

bytes* ping_req_to_bytes(ping_req* ping_req);

char* ping_req_to_string(ping_req* ping_req);

#endif
