#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool string_util_is_empty(char* string);

char* string_util_get_null_as_empty(char* string);

char* string_util_get_empty_as_null(char* string);

char* string_util_left_trim(char* string, char mark);

char* string_util_right_trim(char* string, char mark);

char* string_util_trim(char* string, char mark);

char* string_util_concat(char* destiny, char* source);

size_t string_util_length(char* string);

char* string_util_build_empty_string(size_t length);

void string_util_copy(char* destiny, char* source, size_t length);

#endif
