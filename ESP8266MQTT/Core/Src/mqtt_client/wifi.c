#include "../../Inc/mqtt_client/wifi.h"

wifi* wifi_init(esp8266* esp8266, unsigned int timeout){
	wifi* result = (wifi*) malloc(sizeof(wifi));

	result->connected     = esp8266->connected;
	result->esp8266       = esp8266;
	result->timeout       = timeout;
	result->received      = NULL;
	result->mqtt_server   = NULL;

	return result;
}

void wifi_destroy(wifi* wifi){
	if( wifi == NULL ) return;
	wifi->esp8266 = NULL;
	bytes_destroy(wifi->received);
	wifi->received = NULL;
	wifi->mqtt_server = NULL;
	free(wifi);
	wifi = NULL;
}

void wifi_connect(wifi* wifi, char* ip, unsigned int port){
	if( wifi == NULL ) return;

	if ( wifi->mqtt_server != NULL ){
		wifi->connected = true;
		return;\
	}
	wifi->connected = esp8266_createTCP(wifi->esp8266, (uint8_t*) ip, (uint16_t) port);
}

void wifi_disconnect(wifi* wifi){
	if( wifi == NULL ) return;

    if ( wifi->mqtt_server != NULL ) {
    	wifi->connected = false;
        return;
    }

    esp8266_releaseTCP(wifi->esp8266);
    wifi->connected = false;
}

bool wifi_is_connected(wifi* wifi){
	return wifi == NULL ? false : wifi->connected;
}

bytes* wifi_read(wifi* wifi){
	if( wifi == NULL ) return NULL;
	return bytes_init();
}

void wifi_write(wifi* wifi, bytes* bytes){
    if( ! wifi->connected || bytes == NULL || bytes_is_empty(bytes) ) return;

    if( wifi->mqtt_server != NULL ){
        mqtt_server_request(wifi->mqtt_server, bytes);
        return;
    }

    uint8_t* array = bytes_to_array(bytes);
    uint16_t size = bytes_get_size(bytes);
    esp8266_send(wifi->esp8266, array, size);
    free(array);
    array = NULL;
}
