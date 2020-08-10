#include <configuration/properties.h>

char*                   SMART_WATER_PROPERTIES_SMART_WATER_ID                       = (char*) "python_test";
uint8_t* 	            SMART_WATER_PROPERTIES_SSID                                 = (uint8_t*) "LAPTOP-SE6C11TJ1937";
uint8_t* 	            SMART_WATER_PROPERTIES_PASSWORD_SSID                        = (uint8_t*) "5hB6;261";
char* 	            	SMART_WATER_PROPERTIES_API_GATEWAY_HOST 					= (char*) "192.168.137.211";
uint16_t 	            SMART_WATER_PROPERTIES_API_GATEWAY_PORT                     = (uint16_t) 1883;
char* 	            	SMART_WATER_PROPERTIES_API_GATEWAY_CHANNEL                  = (char*) "request";
char*                   SMART_WATER_PROPERTIES_REPLY_HOST                           = (char*) "192.168.137.211";
char*                   SMART_WATER_PROPERTIES_REPLY_PORT                           = (char*) "1883";
char*                   SMART_WATER_PROPERTIES_REPLY_CHANNEL                        = (char*) "response";
char*                   SMART_WATER_PROPERTIES_METHOD                               = (char*) "PUT";
char*                   SMART_WATER_PROPERTIES_URI                                  = (char*) "/api/v1/self/devices/datapoints/python_test";
uint32_t                SMART_WATER_PROPERTIES_MEASUREMENT_CYCLE_IN_MILLISECONDS    = 0;
unsigned char 			QOS_LEVEL													= 0x00; // QOS_LEVEL_0 = 0x00, QOS_LEVEL_1 = 0x01, QOS_LEVEL_2 = 0x02

GPIO_TypeDef*           DS18B20_PROPERTIES_PORT                                     = NULL;
uint16_t                DS18B20_PROPERTIES_PIN                                      = 0;
char*            		DS18B20_PROPERTIES_LABEL									= "temperature";

ADC_HandleTypeDef*      SEN0161_PROPERTIES_PIN                                      = NULL;
char*            		SEN0161_PROPERTIES_LABEL									= "ph";

ADC_HandleTypeDef*      SEN0165_PROPERTIES_PIN                                      = NULL;
char*            		SEN0165_PROPERTIES_LABEL									= "orp";

ADC_HandleTypeDef*      SEN0169_PROPERTIES_PIN                                      = NULL;
char*            		SEN0169_PROPERTIES_LABEL									= "ph";

ADC_HandleTypeDef*      SEN0189_PROPERTIES_PIN                                      = NULL;
char*                   SEN0189_PROPERTIES_LABEL									= "turbidity";

ADC_HandleTypeDef*      SEN0237A_PROPERTIES_PIN                                    	= NULL;
bool                    SEN0237A_PROPERTIES_MODE_CALIBRATION                      	= false;
char* 					SEN0237A_PROPERTIES_LABEL									= "do";
