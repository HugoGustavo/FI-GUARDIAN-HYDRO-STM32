#include "app.h"

/* VARIAVIES PRIVADAS */
esp8266* 				esp 				= NULL;
direct_memory_access*	dma					= NULL;
mqtt_client*			mqtt 				= NULL;
ds18b20*				sensor_ds18b20		= NULL;
sen0165*				sensor_sen0165		= NULL;
sen0169*				sensor_sen0169		= NULL;
sen0189*				sensor_sen0189		= NULL;
sen0237a*				sensor_sen0237a		= NULL;
char*					message				= NULL;

void app_init(ADC_HandleTypeDef* hadc){
	configure_delay();
	configure_ssd1306();
	configure_init_screen();
	configure_esp();
	configure_dma(hadc);

	configure_ds18b20();
	configure_sen0165();
	configure_sen0169();
	configure_sen0189();
	configure_sen0237a();

	configure_mqtt_client();
}

void configure_delay(void){
	DWT_Init();
}

void configure_ssd1306(void){
	SSD1306_Init();
	SDD1306_Clear_Screen();
}

void configure_init_screen(void){
	SSD1306_Write_Centered_String((uint8_t*) "FI-GUARDIAN", (uint8_t) 2);
	SSD1306_Write_Centered_String((uint8_t*) "SMART WATER", (uint8_t) 3);
	SSD1306_Write_Centered_String((uint8_t*) "powered by UFU & VM9", (uint8_t) 5);
	stm32_util_delay_in_seconds(8);
	SDD1306_Clear_Screen();
}

void configure_esp(void){
	logger_info(logger_get_instance(), (char*) "Configurando ESP8266");
	esp = esp8266_init();
	esp8266_setOprToStationSoftAP(esp);
	esp8266_enableMUX(esp);
	esp8266_joinAP(esp, SMART_WATER_PROPERTIES_SSID, SMART_WATER_PROPERTIES_PASSWORD_SSID);
	esp8266_createTCP(esp, (uint8_t*) SMART_WATER_PROPERTIES_API_GATEWAY_HOST, SMART_WATER_PROPERTIES_API_GATEWAY_PORT);
}

void configure_dma(ADC_HandleTypeDef* hadc){
	if( hadc != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando DMA");
		dma = direct_memory_access_init(hadc, 4);
		direct_memory_access_start(dma);
	}
}

void configure_ds18b20(void){
	if( DS18B20_PROPERTIES_PORT != NULL ){
		logger_info(logger_get_instance(), (char*) "Configurando DS18B20");
		sensor_ds18b20 = ds18b20_init(DS18B20_PROPERTIES_PORT, DS18B20_PROPERTIES_PIN);
	}
}

void configure_sen0165(void){
	if( SEN0165_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0165");
		sensor_sen0165 = sen0165_init(dma, SEN0165_PROPERTIES_PIN, SEN0165_PROPERTIES_OFFSET);
	}
}

void configure_sen0169(void){
	if( SEN0169_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0169");
		sensor_sen0169 = sen0169_init(dma, SEN0169_PROPERTIES_PIN);
	}

}

void configure_sen0189(void){
	if( SEN0189_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0189");
		sensor_sen0189 = sen0189_init(dma, SEN0189_PROPERTIES_PIN);
	}
}

void configure_sen0237a(void){
	if( SEN0237A_PROPERTIES_PIN != 0 ){
		logger_info(logger_get_instance(), (char*) "Configurando SEN0237A");
		sensor_sen0237a = sen0237a_init(dma,
				SEN0237A_PROPERTIES_PIN,
				SEN0237A_PROPERTIES_IS_MODE_CALIBRATION,
				SEN0237A_PROPERTIES_POINTS_CALIBRATION,
				SEN0237A_PROPERTIES_VOLTAGE_POINT_1,
				SEN0237A_PROPERTIES_TEMPERATURE_POINT_1,
				SEN0237A_PROPERTIES_VOLTAGE_POINT_2,
				SEN0237A_PROPERTIES_TEMPERATURE_POINT_2);
	}
}

void configure_mqtt_client(void){
	logger_info(logger_get_instance(), (char*) "Conectando ao Gateway");
	mqtt = mqtt_client_init(esp);
	mqtt_client_connect(mqtt, SMART_WATER_PROPERTIES_SMART_WATER_ID, SMART_WATER_PROPERTIES_API_GATEWAY_HOST, SMART_WATER_PROPERTIES_API_GATEWAY_PORT, 60, true);
}

void app_measure(void){
	logger_clean(logger_get_instance());

	message_builder* builder = message_builder_get_instance();
	message_builder_instance = message_builder_set_reply_host(builder, SMART_WATER_PROPERTIES_REPLY_HOST);
	message_builder_instance = message_builder_set_reply_port(builder, SMART_WATER_PROPERTIES_REPLY_PORT);
	message_builder_instance = message_builder_set_reply_channel(builder, SMART_WATER_PROPERTIES_REPLY_CHANNEL);
	message_builder_instance = message_builder_set_method(builder, SMART_WATER_PROPERTIES_METHOD);
	message_builder_instance = message_builder_set_uri(builder, SMART_WATER_PROPERTIES_URI);

	char* buffer_ds18b20 = NULL;
	char* buffer_sen0165 = NULL;
	char* buffer_sen0169 = NULL;
	char* buffer_sen0189 = NULL;
	char* buffer_sen0237a = NULL;


	if( sensor_ds18b20 != NULL ){
		float temperature = ds18b20_read(sensor_ds18b20);
		buffer_ds18b20 = (char*) malloc(10*sizeof(char));
		gcvt(temperature, 6, buffer_ds18b20);
		message_builder_instance = message_builder_put_body(builder, DS18B20_PROPERTIES_LABEL, buffer_ds18b20);

		char* property_value = string_util_property(DS18B20_PROPERTIES_LABEL, buffer_ds18b20);
		logger_info(logger_get_instance(), property_value);
		free(property_value);
		property_value = NULL;
	}

	if( sensor_sen0165 != NULL ){
		float orp = sen0165_read(sensor_sen0165);
		buffer_sen0165 = (char*) malloc(10*sizeof(char));
		gcvt(orp, 6, buffer_sen0165);
		message_builder_instance = message_builder_put_body(builder, SEN0165_PROPERTIES_LABEL, buffer_sen0165);

		char* property_value = string_util_property(SEN0165_PROPERTIES_LABEL, buffer_sen0165);
		logger_info(logger_get_instance(), property_value);
		free(property_value);
		property_value = NULL;
	}

	if( sensor_sen0169 != NULL ){
		float ph = sen0169_read(sensor_sen0169);
		buffer_sen0169 = (char*) malloc(10*sizeof(char));
		gcvt(ph, 6, buffer_sen0169);
		message_builder_instance = message_builder_put_body(builder, SEN0169_PROPERTIES_LABEL, buffer_sen0169);

		char* property_value = string_util_property(SEN0169_PROPERTIES_LABEL, buffer_sen0169);
		logger_info(logger_get_instance(), property_value);
		free(property_value);
		property_value = NULL;
	}

	if( sensor_sen0189 != NULL ){
		float turbidity = sen0189_read(sensor_sen0189);
		buffer_sen0189 = (char*) malloc(10*sizeof(char));
		gcvt(turbidity, 6, buffer_sen0189);
		message_builder_instance = message_builder_put_body(builder, SEN0189_PROPERTIES_LABEL, buffer_sen0189);

		char* property_value = string_util_property(SEN0189_PROPERTIES_LABEL, buffer_sen0189);
		logger_info(logger_get_instance(), property_value);
		free(property_value);
		property_value = NULL;
	}

	if( sensor_sen0237a != NULL && sensor_ds18b20 != NULL){
		sen0237a_set_current_temperature(sensor_sen0237a, (uint32_t) ceil(ds18b20_read(sensor_ds18b20)));
		float dissolved_oxygen = sen0237a_read(sensor_sen0237a);
		buffer_sen0237a = (char*) malloc(10*sizeof(char));
		gcvt(dissolved_oxygen, 6, buffer_sen0237a);
		message_builder_instance = message_builder_put_body(builder, SEN0237A_PROPERTIES_LABEL, buffer_sen0237a);

		char* property_value = string_util_property(SEN0237A_PROPERTIES_LABEL, buffer_sen0237a);
		logger_info(logger_get_instance(), property_value);
		free(property_value);
		property_value = NULL;
	}

	message = message_builder_build(message_builder_instance);

	if( buffer_ds18b20 != NULL ) free(buffer_ds18b20);
	if( buffer_sen0165 != NULL ) free(buffer_sen0165);
	if( buffer_sen0169 != NULL ) free(buffer_sen0169);
	if( buffer_sen0189 != NULL ) free(buffer_sen0189);
	if( buffer_sen0237a != NULL ) free(buffer_sen0237a);

	buffer_ds18b20 = NULL;
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
	direct_memory_access_restart(dma);
}

void app_destroy(void){
	mqtt_client_disconnect(mqtt);
	esp8266_destroy(esp);
	mqtt_client_destroy(mqtt);
	ds18b20_destroy(sensor_ds18b20);
	sen0165_destroy(sensor_sen0165);
	sen0169_destroy(sensor_sen0169);
	sen0189_destroy(sensor_sen0189);
	sen0237a_destroy(sensor_sen0237a);

	esp 				= NULL;
	mqtt 				= NULL;
	sensor_ds18b20		= NULL;
	sensor_sen0165		= NULL;
	sensor_sen0169		= NULL;
	sensor_sen0189		= NULL;
	sensor_sen0237a		= NULL;
	message				= NULL;
}

