#ifndef MAP_STRING_H
#define MAP_STRING_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAP_STRING_LENGTH 			06
#define MAP_STRING_MAX_INPUT_SIZE 	12

typedef struct __attribute__((__packed__)) map_string {
	char key[MAP_STRING_LENGTH][MAP_STRING_MAX_INPUT_SIZE];
	char value[MAP_STRING_LENGTH][MAP_STRING_MAX_INPUT_SIZE];
	unsigned int index;
} map_string;

map_string* map_string_init();

void map_string_destroy(map_string* map_string);

void map_string_put(map_string* map_string, char key[], char value[]);

char* map_string_get(map_string* map_string, char key[]);

void map_string_remove(map_string* map_string, char key[]);

char* map_string_to_char(map_string* map_string);

unsigned int map_string_number_of_chars(map_string* map_string);

unsigned int map_string_number_of_entries(map_string* map_string);

#endif
