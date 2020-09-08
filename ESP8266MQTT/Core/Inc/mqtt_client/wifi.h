#ifndef WIFI_H
#define WIFI_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/logger.h>
#include <esp8266/esp8266.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/mqtt_server.h>
#include <mqtt_client/packet_util.h>

typedef struct __attribute__((__packed__)) wifi {
    bool            connected;
    esp8266*        esp8266;
    unsigned int    timeout;
    uint8_t         buffer[4096];
    uint32_t        length;
    bytes*          received;
    mqtt_server*    mqtt_server;

} wifi;

wifi* wifi_init(esp8266* esp8266, unsigned int timeout);

void wifi_destroy(wifi* wifi);

void wifi_connect(wifi* wifi, char* ip, unsigned int port);

void wifi_disconnect(wifi* wifi);

bool wifi_is_connected(wifi* wifi);

bytes* wifi_read(wifi* wifi);

void wifi_write(wifi* wifi, bytes* bytes);

#endif
