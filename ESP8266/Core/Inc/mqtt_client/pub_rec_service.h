#ifndef PUB_REC_SERVICE_H
#define PUB_REC_SERVICE_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/pub_rec.h>
#include <mqtt_client/session.h>
#include <mqtt_client/session.h>
#include <mqtt_client/assembler.h>
#include <mqtt_client/control_packet_proxy.h>
#include <mqtt_client/string_util.h>

typedef struct pub_rec_service{
	control_packet_proxy* control_packet_proxy;
} pub_rec_service;

pub_rec_service* pub_rec_service_init(control_packet_proxy* control_packet_proxy);

void pub_rec_service_destroy(pub_rec_service* pub_rec_service);

pub_rec* pub_rec_service_create(pub_rec_service* pub_rec_service);

pub_rec* pub_rec_service_read(pub_rec_service* pub_rec_service);
        
void pub_rec_service_write(pub_rec_service* pub_rec_service, pub_rec* pub_rec);

#endif
