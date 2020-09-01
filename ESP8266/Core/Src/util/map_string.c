#include <util/map_string.h>

map_string* map_string_init(){
	map_string* result = (map_string*) malloc(sizeof(map_string));
	for(int i = 0; i < MAP_STRING_LENGTH; i++){
		result->key[i][0] = '\0';
		result->value[i][0] = '\0';
	}
	result->index = 0;
	return result;
}

void map_string_destroy(map_string* map_string){
	if( map_string == NULL ) return;

	for(int i = 0; i < MAP_STRING_LENGTH; i++){
		map_string->key[i][0] = '\0';
		map_string->value[i][0] = '\0';
	}

	free(map_string);
	map_string = NULL;
}

void map_string_put(map_string* map_string, char key[], char value[]){
	if( map_string == NULL || map_string->index == MAP_STRING_LENGTH || key == NULL) return;
	strcpy(map_string->key[map_string->index], key);
	strcpy(map_string->value[map_string->index], value);
	map_string->index++;
}

char* map_string_get(map_string* map_string, char key[]){
	if( map_string == NULL || key == NULL ) return NULL;
	for(unsigned int i = 0; i < map_string->index; i++){
		if( strcmp(map_string->key[i], key ) == 0 ){
			return map_string->value[i];
		}
	}
	return NULL;
}

void map_string_remove(map_string* map_string, char key[]){
	if( map_string == NULL || key == NULL ) return;

	for(unsigned int i = 0; i < map_string->index; i++){
		if( strcmp(map_string->key[i], key) == 0 ){
			for(unsigned int j = i+1; j < map_string->index; j++){
				strcpy(map_string->key[j-1], map_string->key[j]);
				strcpy(map_string->value[j-1], map_string->value[j]);
			}
			map_string->index--;
			break;
		}
	}
}

char* map_string_to_char(map_string* map_string){
	if( map_string == NULL ) return NULL;
	unsigned int number_of_entries = map_string_number_of_entries(map_string);
	unsigned int length_separtors = number_of_entries * 5 + (number_of_entries-1) + 2; // Para as aspas, virgulas, dois pontos, e chaves
	unsigned int number_of_chars = map_string_number_of_chars(map_string);
	char* result = (char*) malloc((length_separtors+number_of_chars+1) * sizeof(char));

	strcpy(result, "{");
	if( map_string->index != 0 ){
		for(unsigned int i = 0; i < map_string->index-1; i++){
			strcat(result, "\""); strcat(result, map_string->key[i]); strcat(result, "\":");
			int is_number = atof(map_string->value[i]) != 0.0 ? 1 : 0;
			if( is_number ){
				strcat(result, map_string->value[i]); strcat(result, ",");
			} else {
				strcat(result, "\""); strcat(result, map_string->value[i]); strcat(result, "\",");
			}
		}

		strcat(result, "\""); strcat(result, map_string->key[map_string->index-1]); strcat(result, "\":");
		int is_number = atof(map_string->value[map_string->index-1]) != 0.0 ? 1 : 0;
		if( is_number ){
			strcat(result, map_string->value[map_string->index-1]);
		} else {
			strcat(result, "\""); strcat(result, map_string->value[map_string->index-1]); strcat(result, "\"");
		}
	}
	strcat(result, "}");
	return result;
}


unsigned int map_string_number_of_chars(map_string* map_string){
	if( map_string == NULL ) return 0;

	unsigned int number_of_chars = 0;
	for(unsigned int i = 0; i < map_string->index; i++){
		number_of_chars += strlen(map_string->key[i]);
		number_of_chars += strlen(map_string->value[i]);
	}

	return number_of_chars;
}

unsigned int map_string_number_of_entries(map_string* map_string){
	if( map_string == NULL ) return 0;
	return map_string->index;
}



