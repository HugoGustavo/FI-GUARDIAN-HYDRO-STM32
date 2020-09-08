#ifndef DISCONNECT_H
#define DISCONNECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/packet_util.h>
#include <mqtt_client/control_packet.h>

typedef struct __attribute__((__packed__)) disconnect {
	control_packet* control_packet;
} disconnect;

disconnect* disconnect_init();

void disconnect_destroy(disconnect* disconnect);

bytes* disconnect_to_bytes(disconnect* disconnect);

char* disconnect_to_string(disconnect* disconnect);

#endif
