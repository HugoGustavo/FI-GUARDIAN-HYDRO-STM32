#ifndef PACKET_UTIL_H
#define PACKET_UTIL_H

#include <stdlib.h>
#include <stdbool.h>
#include <mqtt_client/bytes.h>
#include <mqtt_client/string_util.h>

bytes* packet_util_build_bytes(char* input);

char* packet_util_build_string(bytes* bytes, unsigned int* from);

#endif
