#include <configuration/properties.h>




/*--------------------------------------------------- BEGIN GENERAL CONFIGURATION -----------------------------------------------------------------------------------------------------------*/
char*                   SMART_WATER_PROPERTIES_SMART_WATER_ID                       = (char*) 		    "FI-GUARDIAN-HYDRO";
uint8_t* 	            SMART_WATER_PROPERTIES_SSID                                 = (uint8_t*) 	    "LAPTOP-SE6C11TJ1937";
uint8_t* 	            SMART_WATER_PROPERTIES_PASSWORD_SSID                        = (uint8_t*) 	    "5hB6;261";
char* 	            	SMART_WATER_PROPERTIES_API_GATEWAY_HOST 					= (char*) 		    "192.168.137.1";
uint16_t 	            SMART_WATER_PROPERTIES_API_GATEWAY_PORT                     = (uint16_t) 	    1883;
char* 	            	SMART_WATER_PROPERTIES_API_GATEWAY_CHANNEL                  = (char*) 		    "request";
char*                   SMART_WATER_PROPERTIES_REPLY_HOST                           = (char*) 		    "192.168.137.1";
char*                   SMART_WATER_PROPERTIES_REPLY_PORT                           = (char*) 		    "1883";
char*                   SMART_WATER_PROPERTIES_REPLY_CHANNEL                        = (char*) 		    "response";
char*                   SMART_WATER_PROPERTIES_METHOD                               = (char*) 		    "PUT";
char*                   SMART_WATER_PROPERTIES_URI                                  = (char*) 		    "/api/v1/self/devices/datapoints/FI-GUARDIAN-HYDRO";
uint32_t                SMART_WATER_PROPERTIES_MEASUREMENT_CYCLE_IN_SECONDS		    = (uint32_t)        5;					// 5 Seconds
unsigned char 			QOS_LEVEL													= (unsigned char)   0x00;               // QOS_LEVEL_0 = 0x00, QOS_LEVEL_1 = 0x01, QOS_LEVEL_2 = 0x02
/*--------------------------------------------------- END GENERAL CONFIGURATION -------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN DS18B20 -------------------------------------------------------------------------------------------------------------------------*/
GPIO_TypeDef*           DS18B20_PROPERTIES_PORT                                     = (GPIO_TypeDef*)   GPIOA;		// GPIOA
uint16_t                DS18B20_PROPERTIES_PIN                                      = (uint16_t)        GPIO_PIN_0; // GPIO_PIN_0;
char*            		DS18B20_PROPERTIES_LABEL									= (char*) 			"temperature";
/*---------------------------------------------------- END DS18B20 --------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0161 -------------------------------------------------------------------------------*/
uint32_t      			SEN0161_PROPERTIES_PIN                                      = (uint32_t)        0; 				// ADC_CHANNEL_2;
char*            		SEN0161_PROPERTIES_LABEL									= (char*) 			"ph";
/*---------------------------------------------------- END SEN0161 --------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0165 -------------------------------------------------------------------------------------------------------------------------*/
uint32_t      			SEN0165_PROPERTIES_PIN                                      = (uint32_t)		LL_ADC_CHANNEL_3;	// ADC_CHANNEL_3;
float					SEN0165_PROPERTIES_OFFSET									= (float) 			-2206.375;
char*            		SEN0165_PROPERTIES_LABEL									= (char*) 			"orp";
/*---------------------------------------------------- END SEN0165 --------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0169 -------------------------------------------------------------------------------------------------------------------------*/
uint32_t      			SEN0169_PROPERTIES_PIN                                      = (uint32_t)		LL_ADC_CHANNEL_2;	// ADC_CHANNEL_2;
char*            		SEN0169_PROPERTIES_LABEL									= (char*) 			"ph";
/*---------------------------------------------------- END SEN0169 --------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0189 -------------------------------------------------------------------------------------------------------------------------*/
uint32_t      			SEN0189_PROPERTIES_PIN                                      = (uint32_t)		LL_ADC_CHANNEL_1;	// ADC_CHANNEL_1;
char*                   SEN0189_PROPERTIES_LABEL									= (char*) 			"turbidity";
/*---------------------------------------------------- END SEN0189 --------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0237 -------------------------------------------------------------------------------------------------------------------------*/
uint32_t      			SEN0237A_PROPERTIES_PIN                                    	= (uint32_t)        LL_ADC_CHANNEL_12;	// ADC_CHANNEL_12;
char					SEN0237A_PROPERTIES_IS_MODE_CALIBRATION						= (char)            0x00;			// 0x00 is False, any other value is True
char                    SEN0237A_PROPERTIES_POINTS_CALIBRATION                  	= (char)            0x01;			// Single-point calibration = 0x01, Two-point calibration = 0x02
uint32_t				SEN0237A_PROPERTIES_VOLTAGE_POINT_1							= (uint32_t)        3964.84f;
uint8_t					SEN0237A_PROPERTIES_TEMPERATURE_POINT_1						= (uint8_t)	        25;				// Temperature = [0, 1, 2, 3, ... , 40]
uint32_t				SEN0237A_PROPERTIES_VOLTAGE_POINT_2							= (uint32_t)        0.00f;
uint8_t					SEN0237A_PROPERTIES_TEMPERATURE_POINT_2						= (uint8_t)         25;				// Temperature = [0, 1, 2, 3, ... , 40]
char* 					SEN0237A_PROPERTIES_LABEL									= (char*)           "do";
/*---------------------------------------------------- END SEN0237 --------------------------------------------------------------------------------------------------------------------------*/

