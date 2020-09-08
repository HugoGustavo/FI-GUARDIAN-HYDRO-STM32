#include <view/init_screen.h>

void init_screen_show(void){
	SSD1306_Init();
	SDD1306_Clear_Screen();

	SSD1306_Write_Centered_String((uint8_t*) "FI-GUARDIAN", (uint8_t) 2);
	SSD1306_Write_Centered_String((uint8_t*) "SMART WATER", (uint8_t) 3);
	SSD1306_Write_Centered_String((uint8_t*) "powered by UFU & VM9", (uint8_t) 5);

	stm32_util_delay_in_seconds(8);
	SDD1306_Clear_Screen();
}
