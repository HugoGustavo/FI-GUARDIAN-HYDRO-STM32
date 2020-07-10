#include "app.h"

/* VARIAVIES PRIVADAS */
esp8266* 		esp 				= NULL;
mqtt_client*	mqtt 				= NULL;
ds18b20*		sensor_ds18b20		= NULL;
sen0161*		sensor_sen0161		= NULL;
sen0165*		sensor_sen0165		= NULL;
sen0169*		sensor_sen0169		= NULL;
sen0189*		sensor_sen0189		= NULL;
sen0237a*		sensor_sen0237a		= NULL;
char*			message				= NULL;

void app_init(void){
	configure_esp();
	configure_mqtt_client();
	configure_ds18b20();
	configure_sen0161();
	configure_sen0165();
	configure_sen0169();
	configure_sen0189();
	configure_sen0237a();
}

void configure_esp(void){
	logger_info(logger_get_instance(), (char*) "Configurando ESP8266");
	esp = esp8266_init();
	esp8266_setOprToStationSoftAP(esp);
	esp8266_enableMUX(esp);
	esp8266_joinAP(esp, SMART_WATER_PROPERTIES_SSID, SMART_WATER_PROPERTIES_PASSWORD_SSID);
	esp8266_createTCP(esp, (uint8_t*) SMART_WATER_PROPERTIES_API_GATEWAY_ADDRESS, SMART_WATER_PROPERTIES_API_GATEWAY_PORT);
}

void configure_mqtt_client(void){
	logger_info(logger_get_instance(), (char*) "Conectando ao Gateway");
	mqtt = mqtt_client_init(esp);
	mqtt_client_connect(mqtt, SMART_WATER_PROPERTIES_SMART_WATER_ID, SMART_WATER_PROPERTIES_API_GATEWAY_ADDRESS, SMART_WATER_PROPERTIES_API_GATEWAY_PORT, 60, true);
}

void configure_ds18b20(void){
	if( DS18B20_PROPERTIES_PORT != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando DS18B20");
		sensor_ds18b20 = ds18b20_init(DS18B20_PROPERTIES_PORT, DS18B20_PROPERTIES_PIN);
	}
}

void configure_sen0161(void){
	if( SEN0161_PROPERTIES_PIN != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0161");
		sensor_sen0161 = sen0161_init(SEN0161_PROPERTIES_PIN);
	}
}

void configure_sen0165(void){
	if( SEN0165_PROPERTIES_PIN != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0165");
		sensor_sen0165 = sen0165_init(SEN0165_PROPERTIES_PIN);
	}
}

void configure_sen0169(void){
	if( SEN0169_PROPERTIES_PIN != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0169");
		sensor_sen0169 = sen0169_init(SEN0169_PROPERTIES_PIN);
	}

}

void configure_sen0189(void){
	if( SEN0189_PROPERTIES_PIN != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0189");
		sensor_sen0189 = sen0189_init(SEN0189_PROPERTIES_PIN);
	}
}

void configure_sen0237a(void){
	if( SEN0237A_PROPERTIES_PIN != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0237A");
		sensor_sen0237a = sen0237a_init(SEN0237A_PROPERTIES_PIN, SEN0237A_PROPERTIES_MODE_CALIBRATION);
	}
}

void app_measure(void){
	message_builder* message_builder_instance = message_builder_get_instance();
	message_builder_instance = message_builder_set_reply_host(message_builder_instance, SMART_WATER_PROPERTIES_REPLY_HOST);
	message_builder_instance = message_builder_set_reply_port(message_builder_instance, SMART_WATER_PROPERTIES_REPLY_PORT);
	message_builder_instance = message_builder_set_reply_channel(message_builder_instance, SMART_WATER_PROPERTIES_REPLY_CHANNEL);
	message_builder_instance = message_builder_set_method(message_builder_instance, SMART_WATER_PROPERTIES_METHOD);
	message_builder_instance = message_builder_set_uri(message_builder_instance, SMART_WATER_PROPERTIES_URI);

	if( sensor_ds18b20 != NULL){
		float temperature = ds18b20_read(sensor_ds18b20);
		char* buffer = (char*) malloc(8*sizeof(char)); buffer[0] = '\0';
		gcvt(temperature, 2, buffer);
		message_builder_put_body(message_builder_instance, DS18B20_PROPERTIES_LABEL, buffer);
	}

	if( sensor_sen0161 != NULL ){
		float ph = sen0161_read(sensor_sen0161);
		char* buffer = (char*) malloc(8*sizeof(char)); buffer[0] = '\0';
		gcvt(ph, 2, buffer);
		message_builder_put_body(message_builder_instance, SEN0161_PROPERTIES_LABEL, buffer);
	}

	if( sensor_sen0165 != NULL ){
		float orp = sen0165_read(sensor_sen0165);
		char* buffer = (char*) malloc(8*sizeof(char)); buffer[0] = '\0';
		gcvt(orp, 2, buffer);
		message_builder_put_body(message_builder_instance, SEN0165_PROPERTIES_LABEL, buffer);
	}

	if( sensor_sen0169 != NULL ){
		float ph = sen0169_read(sensor_sen0169);
		char* buffer = (char*) malloc(8*sizeof(char)); buffer[0] = '\0';
		gcvt(ph, 2, buffer);
		message_builder_put_body(message_builder_instance, SEN0169_PROPERTIES_LABEL, buffer);
	}

	if( sensor_sen0189 != NULL ){
		float turbidity = sen0189_read(sensor_sen0189);
		char* buffer = (char*) malloc(8*sizeof(char)); buffer[0] = '\0';
		gcvt(turbidity, 2, buffer);
		message_builder_put_body(message_builder_instance, SEN0189_PROPERTIES_LABEL, buffer);
	}

	if( sensor_sen0237a != NULL ){
		float dissolved_oxygen = sen0189_read(sensor_sen0189);
		char* buffer = (char*) malloc(8*sizeof(char)); buffer[0] = '\0';
		gcvt(dissolved_oxygen, 2, buffer);
		message_builder_put_body(message_builder_instance, SEN0237A_PROPERTIES_LABEL, buffer);
	}

	message = message_builder_build(message_builder_instance);
}

void app_send(void){
	unsigned char MQTT_QOS_LEVEL = QOS_LEVEL == 0x00 || QOS_LEVEL == 0x01 || QOS_LEVEL == 0x02 ? QOS_LEVEL : 0x00;
	mqtt_client_publish(mqtt, (char*) "request", (char*) message, MQTT_QOS_LEVEL, false);
	free(message);
	message = NULL;
}

void app_wait(void){
	//HAL_Delay(SMART_WATER_PROPERTIES_MEASUREMENT_CYCLE_IN_MILLISECONDS);
}


