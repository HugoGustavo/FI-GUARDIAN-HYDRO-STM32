/*
 * assembler.h
 *
 *  Created on: 6 de abr de 2020
 *      Author: hugog
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdbool.h>
#include <mqtt_client/connack.h>
#include <mqtt_client/connect.h>
#include <mqtt_client/disconnect.h>
#include <mqtt_client/ping_req.h>
#include <mqtt_client/ping_resp.h>
#include <mqtt_client/pub_ack.h>
#include <mqtt_client/pub_comp.h>
#include <mqtt_client/publish.h>
#include <mqtt_client/pub_rec.h>
#include <mqtt_client/pub_rel.h>
#include <mqtt_client/control_packet.h>

#include <mqtt_client/packet_util.h>

control_packet* assembler_build_to_control_packet(bytes* bytes);

connack* assembler_build_to_connack(bytes* bytes);

connect* assembler_build_to_connect(bytes* bytes);

disconnect* assembler_build_to_disconnect(bytes* bytes);

ping_req* assembler_build_to_ping_req(bytes* bytes);

ping_resp* assembler_build_to_ping_resp(bytes* bytes);

pub_ack* assembler_build_to_pub_ack(bytes* bytes);

pub_comp* assembler_build_to_pub_comp(bytes* bytes);

publish* assembler_build_to_publish(bytes* bytes);

pub_rec* assembler_build_to_pub_rec(bytes* bytes);

pub_rel* assembler_build_to_pub_rel(bytes* bytes);

#endif
