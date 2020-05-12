#ifndef PING_RESP_SERVICE_H
#define PING_RESP_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/wifi.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/ping_resp.h>
#include <mqtt_client/string_util.h>

typedef struct ping_resp_service{
	wifi* wifi;
} ping_resp_service;

ping_resp_service* ping_resp_service_init(wifi* wifi);

void ping_resp_service_destroy(ping_resp_service* ping_resp_service);

ping_resp* ping_resp_service_create(ping_resp_service* ping_resp_service);

ping_resp* ping_resp_service_read(ping_resp_service* ping_resp_service);

void ping_resp_service_write(ping_resp_service* ping_resp_service, ping_resp* ping_resp);

#endif
