#ifndef BYTES_H
#define BYTES_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	unsigned char value;
	struct node* previous;
	struct node* next;
} node;

node* node_init(const unsigned char value, node* previous, node* next);

void node_destroy(node* node);

typedef struct __attribute__((__packed__)) bytes {
	struct node* front;
	struct node* back;
    unsigned int size;
} bytes;

bytes* bytes_init();

void bytes_destroy(bytes* bytes);

unsigned char bytes_is_empty(bytes* bytes);

unsigned char bytes_at(bytes* bytes, const unsigned int index);
        
unsigned char bytes_at_front(bytes* bytes);
        
unsigned char bytes_at_back(bytes* bytes);
        
void bytes_push_back(bytes* bytes, const unsigned char value);
        
void bytes_pop_back(bytes* bytes);
        
void bytes_push_front(bytes* bytes, const unsigned char value);
        
void bytes_pop_front(bytes* bytes);
        
unsigned int bytes_get_size(bytes* bytes);
        
void bytes_concat(bytes* destiny, bytes* source);
        
unsigned char* bytes_to_array(bytes* bytes);
        
unsigned char bytes_equals(bytes* first, bytes* second);

char* bytes_to_string(bytes* bytes);

#endif
