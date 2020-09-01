#include "../../Inc/mqtt_client/packet_util.h"

bytes* packet_util_build_bytes(char* input){
	bytes* result = bytes_init();

	unsigned int length = string_util_length(input);
	unsigned char msb_length = (unsigned char) ( (0xFF00 & length) >> 8 );
	unsigned char lsb_length = (unsigned char) ( 0x00FF & length );
	bytes_push_back(result, msb_length);
	bytes_push_back(result, lsb_length);

	for(int i = 0; i < length; i++)
		bytes_push_back(result, (unsigned char) input[i] );

	return result;
}



char* packet_util_build_string(bytes* bytes, unsigned int* from){
	unsigned int msb_length = (unsigned int) ( bytes_at(bytes, *from) << 8);
	unsigned int lsb_length = (unsigned int) (bytes_at(bytes, (*from)+1));
	unsigned int length = msb_length + lsb_length;

	char* field = string_util_build_empty_string(length+1);

	for( unsigned int i = 0; i < length; i++ )
		field[i] = (char) bytes_at(bytes, *from + i + 2);

	*from = *from + length + 2;
	return field;
}
