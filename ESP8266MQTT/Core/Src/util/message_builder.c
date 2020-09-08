#include <util/message_builder.h>

message_builder* instance = NULL;

message_builder* message_builder_get_instance(){
	if( instance == NULL ){
		instance = (message_builder*) malloc(sizeof(message_builder));
		instance->reply_host = NULL;
		instance->reply_port = NULL;
		instance->reply_channel = NULL;
		instance->method = NULL;
		instance->uri = NULL;
		instance->header = NULL;
		instance->body = map_string_init();
	}
	return instance;
}

message_builder* message_builder_set_reply_host(message_builder* message_builder, char* reply_host){
	if( message_builder == NULL ) return NULL;
	message_builder->reply_host = reply_host;
	return message_builder;
}

message_builder* message_builder_set_reply_port(message_builder* message_builder, char* reply_port){
	if( message_builder == NULL ) return NULL;
	message_builder->reply_port = reply_port;
	return message_builder;
}

message_builder* message_builder_set_reply_channel(message_builder* message_builder, char* reply_channel){
	if( message_builder == NULL ) return NULL;
	message_builder->reply_channel = reply_channel;
	return message_builder;
}

message_builder* message_builder_set_method(message_builder* message_builder, char* method){
	if( message_builder == NULL ) return NULL;
	message_builder->method = method;
	return message_builder;
}

message_builder* message_builder_set_uri(message_builder* message_builder, char* uri){
	if( message_builder == NULL ) return NULL;
	message_builder->uri = uri;
	return message_builder;
}

message_builder* message_builder_put_header(message_builder* message_builder, char* key, char* value){
	if( message_builder == NULL ) return NULL;
	map_string_put(message_builder->header, key, value);
	return message_builder;
}

message_builder* message_builder_put_body(message_builder* message_builder, char* key, char* value){
	if( message_builder == NULL ) return NULL;
	map_string_put(message_builder->body, key, value);
	return message_builder;
}

char* message_builder_build(message_builder* message_builder){
	if( message_builder == NULL ) return NULL;

	char* message = (char*) malloc(256*sizeof(char)); message[0] = '\0';
	message[0] = '{';
	message[1] = '\0';

	//strcat(message, "{");
	strcat(message, (char*) "\"replyHost\":\""); strcat(message, message_builder->reply_host); strcat(message, (char*) "\",");
	strcat(message, (char*) "\"replyPort\":"); strcat(message, message_builder->reply_port); strcat(message, (char*) ",");
	strcat(message, (char*) "\"replyChannel\":\""); strcat(message, message_builder->reply_channel); strcat(message, (char*) "\",");
	strcat(message, (char*) "\"method\":\""); strcat(message, message_builder->method); strcat(message, (char*) "\",");
	strcat(message, (char*) "\"uri\":\""); strcat(message, message_builder->uri); strcat(message, "\",");
	strcat(message, (char*) "\"header\":"); strcat(message, "{}"); strcat(message, (char*) ",");
	strcat(message, (char*) "\"body\":"); strcat(message, map_string_to_char(message_builder->body));
	strcat(message, (char*) "}");
	message[strlen(message)] = '\0';
	return message;
}

void message_builder_destroy(){
	if( instance == NULL ) return;

	//free(instance->reply_host);
	instance->reply_host = NULL;

	//free(instance->reply_port);
	instance->reply_port = NULL;

	//free(instance->reply_channel);
	instance->reply_channel = NULL;

	//free(instance->method);
	instance->method = NULL;

	//free(instance->uri);
	instance->uri = NULL;

	map_string_destroy(instance->header);
	instance->header = NULL;

	map_string_destroy(instance->body);
	instance->body = NULL;

	free(instance);
	instance = NULL;
}
