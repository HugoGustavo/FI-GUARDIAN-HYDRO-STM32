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
float			valor 				= 0.01;

void app_init(ADC_HandleTypeDef* hadc1){
	configure_delay();
	configure_esp();
	configure_ds18b20();
	configure_mqtt_client();
	configure_sen0161(hadc1);
	configure_sen0165(hadc1);
	configure_sen0169(hadc1);
	configure_sen0189(hadc1);
	configure_sen0237a(hadc1);
}

void configure_delay(void){
	DWT_Init();
}

void configure_esp(void){
	logger_info(logger_get_instance(), (char*) "Configurando ESP8266");
	esp = esp8266_init();
	esp8266_setOprToStationSoftAP(esp);
	esp8266_enableMUX(esp);
	esp8266_joinAP(esp, SMART_WATER_PROPERTIES_SSID, SMART_WATER_PROPERTIES_PASSWORD_SSID);
	esp8266_createTCP(esp, (uint8_t*) SMART_WATER_PROPERTIES_API_GATEWAY_HOST, SMART_WATER_PROPERTIES_API_GATEWAY_PORT);
}

void configure_mqtt_client(void){
	logger_info(logger_get_instance(), (char*) "Conectando ao Gateway");
	mqtt = mqtt_client_init(esp);
	mqtt_client_connect(mqtt, SMART_WATER_PROPERTIES_SMART_WATER_ID, SMART_WATER_PROPERTIES_API_GATEWAY_HOST, SMART_WATER_PROPERTIES_API_GATEWAY_PORT, 60, true);
}

void configure_ds18b20(void){
	if( DS18B20_PROPERTIES_PORT != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando DS18B20");
		sensor_ds18b20 = ds18b20_init(DS18B20_PROPERTIES_PORT, DS18B20_PROPERTIES_PIN);
	}
}

void configure_sen0161(ADC_HandleTypeDef* hadc1){
	if( hadc1 != NULL && SEN0161_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0161");
		sensor_sen0161 = sen0161_init(hadc1, SEN0161_PROPERTIES_PIN);
	}
}

void configure_sen0165(ADC_HandleTypeDef* hadc1){
	if( hadc1 != NULL && SEN0165_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0165");
		sensor_sen0165 = sen0165_init(hadc1, SEN0165_PROPERTIES_PIN);
	}
}

void configure_sen0169(ADC_HandleTypeDef* hadc1){
	if( hadc1 != NULL && SEN0169_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0169");
		sensor_sen0169 = sen0169_init(hadc1, SEN0169_PROPERTIES_PIN);
	}

}

void configure_sen0189(ADC_HandleTypeDef* hadc1){
	if( hadc1 != NULL && SEN0189_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0189");
		sensor_sen0189 = sen0189_init(hadc1, SEN0189_PROPERTIES_PIN);
	}
}

void configure_sen0237a(ADC_HandleTypeDef* hadc1){
	if( hadc1 != NULL && SEN0237A_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0237A");
		sensor_sen0237a = sen0237a_init(hadc1, SEN0237A_PROPERTIES_PIN, SEN0237A_PROPERTIES_MODE_CALIBRATION);
	}
}

void app_measure(void){
	message_builder* message_builder_instance = message_builder_get_instance();
	message_builder_instance = message_builder_set_reply_host(message_builder_instance, SMART_WATER_PROPERTIES_REPLY_HOST);
	message_builder_instance = message_builder_set_reply_port(message_builder_instance, SMART_WATER_PROPERTIES_REPLY_PORT);
	message_builder_instance = message_builder_set_reply_channel(message_builder_instance, SMART_WATER_PROPERTIES_REPLY_CHANNEL);
	message_builder_instance = message_builder_set_method(message_builder_instance, SMART_WATER_PROPERTIES_METHOD);
	message_builder_instance = message_builder_set_uri(message_builder_instance, SMART_WATER_PROPERTIES_URI);

	char* buffer_ds18b20 = NULL;
	char* buffer_sen0161 = NULL;
	char* buffer_sen0165 = NULL;
	char* buffer_sen0169 = NULL;
	char* buffer_sen0189 = NULL;
	char* buffer_sen0237a = NULL;


	if( sensor_ds18b20 != NULL || 1 ){
		//float temperature = ds18b20_read(sensor_ds18b20);
		float temperature = valor; valor += 1.0;
		buffer_ds18b20 = (char*) malloc(10*sizeof(char));
		gcvt(temperature, 6, buffer_ds18b20);
		message_builder_instance = message_builder_put_body(message_builder_instance, DS18B20_PROPERTIES_LABEL, buffer_ds18b20);
	}

	if( sensor_sen0161 != NULL || 1){
		//float ph = sen0161_read(sensor_sen0161);
		float ph = valor; valor += 1.0;
		buffer_sen0161 = (char*) malloc(10*sizeof(char));
		gcvt(ph, 6, buffer_sen0161);
		message_builder_instance = message_builder_put_body(message_builder_instance, SEN0161_PROPERTIES_LABEL, buffer_sen0161);
	}

	if( sensor_sen0165 != NULL || 1){
		//float orp = sen0165_read(sensor_sen0165);
		float orp = valor; valor += 1.0;
		buffer_sen0165 = (char*) malloc(10*sizeof(char));
		gcvt(orp, 6, buffer_sen0165);
		message_builder_instance = message_builder_put_body(message_builder_instance, SEN0165_PROPERTIES_LABEL, buffer_sen0165);
	}

	/*
	if( sensor_sen0169 != NULL ){
		float ph = sen0169_read(sensor_sen0169);
		buffer_sen0169 = (char*) malloc(10*sizeof(char));
		stm32_util_float_to_char(ph, buffer_sen0169);
		message_builder_instance = message_builder_put_body(message_builder_instance, SEN0169_PROPERTIES_LABEL, buffer_sen0169);
	}
	*/
	if( sensor_sen0189 != NULL || 1){
		//float turbidity = sen0189_read(sensor_sen0189);
		float turbidity = valor; valor += 1.0;
		buffer_sen0189 = (char*) malloc(10*sizeof(char));
		gcvt(turbidity, 6, buffer_sen0189);
		message_builder_instance = message_builder_put_body(message_builder_instance, SEN0189_PROPERTIES_LABEL, buffer_sen0189);
	}

	if( sensor_sen0237a != NULL || 1){
		//float dissolved_oxygen = sen0237a_read(sensor_sen0237a);
		float dissolved_oxygen = valor; valor += 1.0;
		buffer_sen0237a = (char*) malloc(10*sizeof(char));
		gcvt(dissolved_oxygen, 6, buffer_sen0237a);
		message_builder_instance = message_builder_put_body(message_builder_instance, SEN0237A_PROPERTIES_LABEL, buffer_sen0237a);
	}

	message = message_builder_build(message_builder_instance);

	if( buffer_ds18b20 != NULL ) free(buffer_ds18b20);
	if( buffer_sen0161 != NULL ) free(buffer_sen0161);
	if( buffer_sen0165 != NULL ) free(buffer_sen0165);
	if( buffer_sen0169 != NULL ) free(buffer_sen0169);
	if( buffer_sen0189 != NULL ) free(buffer_sen0189);
	if( buffer_sen0237a != NULL ) free(buffer_sen0237a);

	buffer_ds18b20 = NULL;
	buffer_sen0161 = NULL;
	buffer_sen0165 = NULL;
	buffer_sen0169 = NULL;
	buffer_sen0189 = NULL;
	buffer_sen0237a = NULL;

	message_builder_destroy();
}

void app_send(void){
	unsigned char MQTT_QOS_LEVEL = QOS_LEVEL == 0x00 || QOS_LEVEL == 0x01 || QOS_LEVEL == 0x02 ? QOS_LEVEL : 0x00;
	mqtt_client_publish(mqtt, (char*) SMART_WATER_PROPERTIES_API_GATEWAY_CHANNEL, (char*) message, MQTT_QOS_LEVEL, false);
	if( message != NULL ) free(message);
	message = NULL;
}

void app_wait(void){
	stm32_util_delay_in_seconds(SMART_WATER_PROPERTIES_MEASUREMENT_CYCLE_IN_SECONDS);
}

void app_destroy(void){
	mqtt_client_disconnect(mqtt);
	esp8266_destroy(esp);
	mqtt_client_destroy(mqtt);
	ds18b20_destroy(sensor_ds18b20);
	sen0161_destroy(sensor_sen0161);
	sen0165_destroy(sensor_sen0165);
	sen0169_destroy(sensor_sen0169);
	sen0189_destroy(sensor_sen0189);
	sen0237a_destroy(sensor_sen0237a);

	esp 				= NULL;
	mqtt 				= NULL;
	sensor_ds18b20		= NULL;
	sensor_sen0161		= NULL;
	sensor_sen0165		= NULL;
	sensor_sen0169		= NULL;
	sensor_sen0189		= NULL;
	sensor_sen0237a		= NULL;
	message				= NULL;
}

