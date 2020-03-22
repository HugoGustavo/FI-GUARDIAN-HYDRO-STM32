/*
 * app.c
 *
 *  Created on: Feb 27, 2020
 *      Author: skywalker
 */


#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "hw.h"
#include "iot.h"

void app_init(void)
{
	  SSD1306_Init();
	  SDD1306_Clear_Screen();
	  SSD1306_Goto(0, 1);
	  SSD1306_Write_Centered_String((uint8_t*)"FIGUARDIAN DEVICE",0);
	  SSD1306_Goto(0, 2);
	  SSD1306_Write_Centered_String((uint8_t*)"DISPLAY TEST DIEGO",1);
	  SSD1306_Goto(0, 7);
	  SSD1306_Write_String((uint8_t*)"Finish");

	  hw_esp_power_set(true);
	  hw_time_sleep(100);

	  hw_uart_init();
	  iot_on();

}

void app_main(void)
{
	iot_update();
	hw_time_sleep(5000);
}
