#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_adc.h"
#include "stm32l4xx_hal_gpio.h"



/*--------------------------------------------------- BEGIN GENERAL CONFIGURATION -------------------------------------------------------------------------------*/
extern char*                SMART_WATER_PROPERTIES_SMART_WATER_ID;
extern uint8_t* 	        SMART_WATER_PROPERTIES_SSID;
extern uint8_t* 	        SMART_WATER_PROPERTIES_PASSWORD_SSID;
extern char* 	            SMART_WATER_PROPERTIES_API_GATEWAY_HOST;
extern uint16_t 	        SMART_WATER_PROPERTIES_API_GATEWAY_PORT;
extern char* 	            SMART_WATER_PROPERTIES_API_GATEWAY_CHANNEL;
extern char*                SMART_WATER_PROPERTIES_REPLY_HOST;
extern char*                SMART_WATER_PROPERTIES_REPLY_PORT;
extern char*                SMART_WATER_PROPERTIES_REPLY_CHANNEL;
extern char*                SMART_WATER_PROPERTIES_METHOD;
extern char*                SMART_WATER_PROPERTIES_URI;
extern uint32_t             SMART_WATER_PROPERTIES_MEASUREMENT_CYCLE_IN_SECONDS;
extern unsigned char 		QOS_LEVEL;
/*--------------------------------------------------- END GENERAL CONFIGURATION ---------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN DS18B20 -------------------------------------------------------------------------------*/
extern GPIO_TypeDef*        DS18B20_PROPERTIES_PORT;
extern uint16_t             DS18B20_PROPERTIES_PIN;
extern char*            	DS18B20_PROPERTIES_LABEL;
/*---------------------------------------------------- END DS18B20 --------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0161 -------------------------------------------------------------------------------*/
extern uint32_t      		SEN0161_PROPERTIES_PIN;
extern char*            	SEN0161_PROPERTIES_LABEL;
/*---------------------------------------------------- END SEN0161 --------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0165 -------------------------------------------------------------------------------*/
extern uint32_t      		SEN0165_PROPERTIES_PIN;
extern float				SEN0165_PROPERTIES_OFFSET;
extern char*            	SEN0165_PROPERTIES_LABEL;
/*---------------------------------------------------- END SEN0165 --------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0169 -------------------------------------------------------------------------------*/
extern uint32_t      		SEN0169_PROPERTIES_PIN;
extern char*            	SEN0169_PROPERTIES_LABEL;
/*---------------------------------------------------- END SEN0169 --------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0189 -------------------------------------------------------------------------------*/
extern uint32_t      		SEN0189_PROPERTIES_PIN;
extern char*                SEN0189_PROPERTIES_LABEL;
/*---------------------------------------------------- END SEN0189 --------------------------------------------------------------------------------*/




/*--------------------------------------------------- BEGIN SEN0237 -------------------------------------------------------------------------------*/
extern uint32_t      		SEN0237A_PROPERTIES_PIN;
extern char					SEN0237A_PROPERTIES_IS_MODE_CALIBRATION;
extern char                 SEN0237A_PROPERTIES_POINTS_CALIBRATION;
extern uint32_t				SEN0237A_PROPERTIES_VOLTAGE_POINT_1;
extern uint8_t				SEN0237A_PROPERTIES_TEMPERATURE_POINT_1;
extern uint32_t				SEN0237A_PROPERTIES_VOLTAGE_POINT_2;
extern uint8_t				SEN0237A_PROPERTIES_TEMPERATURE_POINT_2;
extern char* 				SEN0237A_PROPERTIES_LABEL;
/*---------------------------------------------------- END SEN0237 --------------------------------------------------------------------------------*/



#endif
