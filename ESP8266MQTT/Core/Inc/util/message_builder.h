#ifndef MESSAGE_BUILDER_H_
#define MESSAGE_BUILDER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <util/map_string.h>
#include <util/logger.h>

typedef struct __attribute__((__packed__)) message_builder {
	char* reply_host;
	char* reply_port;
	char* reply_channel;
	char* method;
	char* uri;
	map_string* header;
	map_string* body;
} message_builder;

extern message_builder* instance;

message_builder* message_builder_get_instance();

message_builder* message_builder_set_reply_host(message_builder* message_builder, char* input);

message_builder* message_builder_set_reply_port(message_builder* message_builder, char* input);

message_builder* message_builder_set_reply_channel(message_builder* message_builder, char* input);

message_builder* message_builder_set_method(message_builder* message_builder, char* input);

message_builder* message_builder_set_uri(message_builder* message_builder, char* input);

message_builder* message_builder_put_header(message_builder* message_builder, char* key, char* value);

message_builder* message_builder_put_body(message_builder* message_builder, char* key, char* value);

char* message_builder_build(message_builder* message_builder);

void message_builder_destroy();

#endif


