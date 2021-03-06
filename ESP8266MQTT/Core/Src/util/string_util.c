#include <util/string_util.h>

bool string_util_is_empty(char* string){
	if( string == NULL ) return true;
	return strlen(string) == 0;
}

char* string_util_get_null_as_empty(char* string){
	if( string_util_is_empty(string) ) return (char*) "\0";
	return string;
}

char* string_util_get_empty_as_null(char* string){
	if( string_util_is_empty(string) ) return NULL;
	return string;
}

char* string_util_left_trim(char *s, char mark){
    while(*s == mark) s++;
    return s;
}

char* string_util_right_trim(char *s, char mark){
    char* back = s + strlen(s);
    while((*--back) == mark);
    *(back+1) = '\0';
    return s;
}

char* string_util_trim(char* string, char mark){
    return string_util_right_trim(string_util_left_trim(string, mark), mark);
}

char* string_util_property(char* name, char* value){
	unsigned int length = strlen(name) + strlen(value) + 2;
	char* result = (char*) malloc(length*sizeof(char));
	strcpy(result, name);
	strcat(result, (char*) ":");
	strcat(result, value);
	return result;
}

char* string_util_concat(char* destiny, char* source){
	size_t size_destiny = strlen(destiny);
	size_t size_source = strlen(source);
	size_t size = size_destiny + size_source + 1;

	char* result = (char*) malloc(size*sizeof(char));
	for(register size_t i = 0; i < size; i++) result[i] = '\0';
	strcpy(result, destiny);
	strcpy(&result[size_destiny], source);

	return result;
}

size_t string_util_length(char* string){
	return strlen(string);
}

char* string_util_build_empty_string(size_t length){
	char* result = (char*) malloc((length+1)*sizeof(char));
	for(register size_t i = 0; i < length; i++) result[i] = '\0';
	return result;
}


void string_util_copy(char* destiny, char* source, size_t length){
	strncpy(destiny, source, length);
}
