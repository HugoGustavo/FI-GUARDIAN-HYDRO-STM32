#ifndef PACKET_UTIL_H
#define PACKET_UTIL_H

#include <stdlib.h>
#include <stdbool.h>
#include <util/string_util.h>
#include <mqtt_client/bytes.h>

bytes* packet_util_build_bytes(char* input);

char* packet_util_build_string(bytes* bytes, unsigned int* from);

#endif
