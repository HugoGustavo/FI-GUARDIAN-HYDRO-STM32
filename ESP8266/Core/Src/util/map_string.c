#include <util/map_string.h>

map_string* map_string_init(){
	map_string* result = (map_string*) malloc(sizeof(map_string));
	result->key = (char**) malloc(sizeof(char**));
	result->value = (char**) malloc(sizeof(char**));
	result->length = 4;
	result->index = 0;
	return result;
}

void map_string_destroy(map_string* map_string){
	if( map_string == NULL ) return;
	free(map_string->key);
	free(map_string->value);
	free(map_string);
	map_string = NULL;
}

void map_string_put(map_string* map_string, char* key, char* value){
	if( map_string == NULL ) return;

	if( map_string->index == map_string->length){
		map_string->length = map_string->length * 2;
		char** new_key = (char**) malloc(map_string->length*sizeof(char**));
		char** new_value = (char**) malloc(map_string->length*sizeof(char**));

		for(unsigned int i = 0; i < map_string->index; i++ ){
			new_key[i] = map_string->key[i];
			new_value[i] = map_string->value[i];
		}

		free(map_string->key);
		free(map_string->value);

		map_string->key = new_key;
		map_string->value = new_value;
	}

	for(unsigned int i = 0; i < map_string->index; i++){
		if( strcmp(map_string->key[i], key) == 0 ){
			map_string->value[i] = value;
			return;
		}
	}

	map_string->key[map_string->index] = key;
	map_string->value[map_string->index] = value;
	map_string->index++;
}

char* map_string_get(map_string* map_string, char* key){
	if( map_string == NULL ) return NULL;
	for(unsigned int i = 0; i < map_string->index; i++){
		if( strcmp(map_string->key[i], key) == 0 ){
			return map_string->value[i];
		}
	}
	return NULL;
}

void map_string_remove(map_string* map_string, char* key){
	if( map_string == NULL ) return;

	for(unsigned int i = 0; i < map_string->index; i++){
		if( strcmp(map_string->key[i], key) == 0 ){
			for(unsigned int j = i+1; j < map_string->index; j++){
				map_string->key[j-1] = map_string->key[j];
				map_string->value[j-1] = map_string->value[j];
			}
		}
	}
}

char*map_string_to_char(map_string* map_string){
	if( map_string == NULL ) return NULL;
	unsigned int number_of_entriers = map_string_number_of_entriers(map_string);
	unsigned int length_separtors = number_of_entriers * 5 + (number_of_entriers-1) + 2; // Para as aspas, virgulas, dois pontos, e chaves
	unsigned int number_of_chars = map_string_number_of_chars(map_string);
	char* result = (char*) malloc((length_separtors+number_of_chars+1) * sizeof(char));

	strcpy(result, "{");
	if( map_string->index != 0 ){
		for(unsigned int i = 0; i < map_string->index-1; i++){
			strcat(result, "\""); strcat(result, map_string->key[i]); strcat(result, "\":\""); strcat(result, map_string->value[i]); strcat(result, "\",");
		}
		strcat(result, "\""); strcat(result, map_string->key[map_string->index-1]); strcat(result, "\":\""); strcat(result, map_string->value[map_string->index-1]);  strcat(result, "\"");
	}
	strcat(result, "}");
	return result;
}


unsigned int map_string_number_of_chars(map_string* map_string){
	if( map_string == NULL ) return 0;

	unsigned int numberOfChars = 0;
	for(unsigned int i = 0; i < map_string->index; i++){
		numberOfChars += strlen(map_string->key[i]);
		numberOfChars += strlen(map_string->value[i]);
	}

	return numberOfChars;
}

unsigned int map_string_number_of_entriers(map_string* map_string){
	if( map_string == NULL ) return 0;
	return map_string->index+1;
}



