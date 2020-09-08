#ifndef PING_REQ_SERVICE_H
#define PING_REQ_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/wifi.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/session.h>
#include <mqtt_client/ping_req.h>
#include <mqtt_client/assembler.h>

typedef struct __attribute__((__packed__)) ping_req_service{
	wifi* wifi;
} ping_req_service;

ping_req_service* ping_req_service_init(wifi* wifi);

void ping_req_service_destroy(ping_req_service* ping_req_service);

ping_req* ping_req_service_create(ping_req_service* ping_req_service);

ping_req* ping_req_service_read(ping_req_service* ping_req_service);

void ping_req_service_write(ping_req_service* ping_req_service, ping_req* ping_req);

#endif
