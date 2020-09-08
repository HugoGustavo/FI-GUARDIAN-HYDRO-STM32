#ifndef PING_RESP_H
#define PING_RESP_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/control_packet.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) ping_resp {
	control_packet* control_packet;
} ping_resp;

ping_resp* ping_resp_init();

void ping_resp_destroy(ping_resp* ping_resp);

bytes* ping_resp_to_bytes(ping_resp* ping_resp);

char* ping_resp_to_string(ping_resp* ping_resp);

#endif
