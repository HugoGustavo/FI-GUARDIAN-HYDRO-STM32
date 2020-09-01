#include <mqtt_client/bytes.h>

node* node_init(const unsigned char value, node* previous, node* next){
	node* result = (node*) malloc(sizeof(node));
	result->value = value;
	result->previous = previous;
	result->next = next;
	return result;
}

void node_destroy(node* node){
	if( node == NULL ) return;
	node->previous = NULL;
	node->next = NULL;
	free(node);
	node = NULL;
}

bytes* bytes_init(){
	bytes* result = (bytes*) malloc(sizeof(bytes));
	result->front = NULL;
	result->back = NULL;
	result->size = 0;
	return result;
}

void bytes_destroy(bytes* bytes){
	if( bytes == NULL ) return;

	node* next = NULL;
	node* actual = bytes->front;
	while( actual != NULL ){
		next = actual->next;
		node_destroy(actual);
		actual = next;
	}
	bytes->front = NULL;
	bytes->back = NULL;
	free(bytes);
	bytes = NULL;
}

unsigned char bytes_is_empty(bytes* bytes){
	return bytes == NULL || bytes->size == 0 ? 1 : 0;
}

unsigned char bytes_at(bytes* bytes, const unsigned int index){
	if( bytes == NULL || index >= bytes->size )
		return (unsigned char) 0;

	int position = index;
	node* current = bytes->front;
	while( position != 0 && current != NULL) {
		current = current->next;
		position--;
	}

	return current == NULL ? (unsigned char) 0 : current->value;
}

unsigned char bytes_at_front(bytes* bytes){
	if( bytes_is_empty(bytes) )
		return (unsigned char) 0;
	return bytes->front->value;
}

unsigned char bytes_at_back(bytes* bytes){
	if( bytes_is_empty(bytes) )
		return (unsigned char) 0;
	return bytes->back->value;
}

void bytes_push_back(bytes* bytes, const unsigned char value){
	node* node = node_init(value, bytes->back, NULL);
	if( bytes->front == NULL ){
		bytes->front = bytes->back = node;
	} else {
		bytes->back->next = node;
		bytes->back = node;
	}
	bytes->size++;
}

void bytes_pop_back(bytes* bytes){
	if( bytes_is_empty(bytes) ) return;

    if ( bytes->back == NULL ) return;

    if ( bytes->front == bytes->back ){
        node_destroy(bytes->front);
        bytes->front = bytes->back = NULL;
    } else {
        node* temp = bytes->back->previous;
        bytes->back->previous = NULL;
        bytes->back->next = NULL;
        temp->next = NULL;
        node_destroy(bytes->back);
        bytes->back = temp;
    }
    bytes->size--;
}

void bytes_push_front(bytes* bytes, const unsigned char value){
	if( bytes_is_empty(bytes) ) return;

	node* node = node_init(value, NULL, bytes->front);
	if ( bytes->front == NULL ){
		bytes->front = bytes->back = node;
	} else{
		bytes->front->previous = node;
		bytes->front = node;
	}

	bytes->size++;
}

void bytes_pop_front(bytes* bytes){
	if( bytes_is_empty(bytes) ) return;

	if ( bytes->front == NULL ) return;

	if ( bytes->front == bytes->back ){
		node_destroy(bytes->front);
		bytes->front = bytes->back = NULL;
	} else {
		node* temp = bytes->front->next;
		bytes->front->previous = NULL;
		bytes->front->next = NULL;
	    temp->previous = NULL;
	    node_destroy(bytes->front);
	    bytes->front = temp;
	}

	bytes->size--;
}

unsigned int bytes_get_size(bytes* bytes){
	return bytes_is_empty(bytes) ? 0 : bytes->size;
}

void bytes_concat(bytes* destiny, bytes* source){
	if ( bytes_is_empty(source) ) return;
	for(unsigned int i = 0; i < bytes_get_size(source); i++){
		bytes_push_back(destiny, bytes_at(source, i));
	}
}

unsigned char* bytes_to_array(bytes* bytes){
	if ( bytes_is_empty(bytes) ) return NULL;

	unsigned int size = bytes_get_size(bytes);
	unsigned char* result = (unsigned char*) malloc(size*sizeof(unsigned char));
	for(unsigned int i = 0; i < size; i++) result[i] = bytes_at(bytes, i);
	return result;
}

unsigned char bytes_equals(bytes* first, bytes* second){
	if( first == NULL && second == NULL ) return 1;
	if( first == NULL && second != NULL ) return 0;
	if( first != NULL && second == NULL ) return 0;

	if(bytes_get_size(first) != bytes_get_size(second)) return 0;

	for(unsigned int i = 0; i < bytes_get_size(first); i++)
		if ( bytes_at(first, i) != bytes_at(second, i) ) return 0;

	return 1;
}

char* bytes_to_string(bytes* bytes){
	if ( bytes_is_empty(bytes) ) return NULL;
	unsigned int size = bytes_get_size(bytes)+1;
	char* result = (char*) malloc(size*sizeof(char));
	for(unsigned int i = 0; i < size-1; i++) result[i] = bytes_at(bytes, i);
	result[size-1] = '\0';
	return result;
}
