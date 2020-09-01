#include <configuration/properties.h>

char*                   SMART_WATER_PROPERTIES_SMART_WATER_ID                       = (char*) "FI-GUARDIAN-HYDRO";
uint8_t* 	            SMART_WATER_PROPERTIES_SSID                                 = (uint8_t*) "LAPTOP-SE6C11TJ1937";
uint8_t* 	            SMART_WATER_PROPERTIES_PASSWORD_SSID                        = (uint8_t*) "5hB6;261";
char* 	            	SMART_WATER_PROPERTIES_API_GATEWAY_HOST 					= (char*) "192.168.137.1";
uint16_t 	            SMART_WATER_PROPERTIES_API_GATEWAY_PORT                     = (uint16_t) 1883;
char* 	            	SMART_WATER_PROPERTIES_API_GATEWAY_CHANNEL                  = (char*) "request";
char*                   SMART_WATER_PROPERTIES_REPLY_HOST                           = (char*) "192.168.137.1";
char*                   SMART_WATER_PROPERTIES_REPLY_PORT                           = (char*) "1883";
char*                   SMART_WATER_PROPERTIES_REPLY_CHANNEL                        = (char*) "response";
char*                   SMART_WATER_PROPERTIES_METHOD                               = (char*) "PUT";
char*                   SMART_WATER_PROPERTIES_URI                                  = (char*) "/api/v1/self/devices/datapoints/FI-GUARDIAN-HYDRO";
uint32_t                SMART_WATER_PROPERTIES_MEASUREMENT_CYCLE_IN_SECONDS		    = 1;
unsigned char 			QOS_LEVEL													= 0x00; // QOS_LEVEL_0 = 0x00, QOS_LEVEL_1 = 0x01, QOS_LEVEL_2 = 0x02

GPIO_TypeDef*           DS18B20_PROPERTIES_PORT                                     = NULL; // GPIOA
uint16_t                DS18B20_PROPERTIES_PIN                                      = GPIO_PIN_0; // GPIO_PIN_0;
char*            		DS18B20_PROPERTIES_LABEL									= (char*) "temperature";

uint32_t      			SEN0161_PROPERTIES_PIN                                      = 0; // ADC_CHANNEL_1
char*            		SEN0161_PROPERTIES_LABEL									= (char*) "ph";

uint32_t      			SEN0165_PROPERTIES_PIN                                      = 0;// ADC_CHANNEL_2
char*            		SEN0165_PROPERTIES_LABEL									= (char*) "orp";

uint32_t      			SEN0169_PROPERTIES_PIN                                      = 0;
char*            		SEN0169_PROPERTIES_LABEL									= (char*) "ph";

uint32_t      			SEN0189_PROPERTIES_PIN                                      = 0; // ADC_CHANNEL_3
char*                   SEN0189_PROPERTIES_LABEL									= (char*) "turbidity";

uint32_t      			SEN0237A_PROPERTIES_PIN                                    	= 0; // ADC_CHANNEL_12
bool                    SEN0237A_PROPERTIES_MODE_CALIBRATION                      	= false;
char* 					SEN0237A_PROPERTIES_LABEL									= (char*) "do";
