#include <main.h>
#include <stdint.h>
#include <stdbool.h>
#include <stm32l4xx_hal.h>
//#include "usb_device.h"
#include <ssd1306/ssd1306_fonts.h>
#include <ssd1306/ssd1306.h>
#include <esp8266/ceb_cbuf.h>
#include <esp8266/config.h>
#include <esp8266/at.h>
#include <esp8266/hw.h>
//#include "usbd_cdc_if.h"

UART_HandleTypeDef 	huart2;
#define UART_HANDLE huart2

#define I2C_HANDLE  hi2c2

extern I2C_HandleTypeDef I2C_HANDLE;

#define LM7X_I2C       &I2C_HANDLE
#define LM7X_I2C_ADDR  (0x48 << 1)

bool hw_debug_enable = false;

void hw_display_set(bool value){
//	if(value)
//		HAL_GPIO_WritePin(DSP_ON_GPIO_Port,DSP_ON_Pin,GPIO_PIN_RESET);
//	else
//		HAL_GPIO_WritePin(DSP_ON_GPIO_Port,DSP_ON_Pin,GPIO_PIN_SET);
}

void hw_esp_power_set(bool value){
	if(value)
		HAL_GPIO_WritePin(ESP_POWER_EN_GPIO_Port, ESP_POWER_EN_Pin, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(ESP_POWER_EN_GPIO_Port, ESP_POWER_EN_Pin, GPIO_PIN_SET);
}

void hw_esp_reset_set(bool value){
//	if(value)
//		HAL_GPIO_WritePin(ESP_RST_GPIO_Port,ESP_RST_Pin,GPIO_PIN_RESET);
//	else
//		HAL_GPIO_WritePin(ESP_RST_GPIO_Port,ESP_RST_Pin,GPIO_PIN_SET);
}

void hw_esp_enable_set(bool value){
	if(value)
		HAL_GPIO_WritePin(ESP_EN_GPIO_Port, ESP_EN_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(ESP_EN_GPIO_Port, ESP_EN_Pin, GPIO_PIN_RESET);
}

//bool hw_user_key_get(void){
//	return (HAL_GPIO_ReadPin(USER_KEY_GPIO_Port,USER_KEY_Pin) == GPIO_PIN_RESET);
//}
//
//void hw_user_led_set(bool value)
//{
//	HAL_GPIO_WritePin(USR_LED_GPIO_Port,USR_LED_Pin,value ? GPIO_PIN_SET: GPIO_PIN_RESET);
//}

//

float hw_temperature_get(void){
	static float v = 1.0;

	v = v + 0.1;

    return v;
}

void hw_debug(const uint8_t* msg, uint16_t len)
#if 0
{
	CDC_Transmit_FS((uint8_t*)msg,len);
}
#else
{
	static uint8_t col 	= 0;
	static uint8_t row 	= 0;
	uint8_t nrow 		= 0;
	int n;

	SSD1306_Goto(col*6, row);

	for(n = 0 ; n < len; n++){
		if(msg[n] == '\n' || msg[n] == '\r'){
			nrow = (row+1) >= SSD1306_HEIGHT/8 ? 0 : row+1;
		}
		else {
			SSD1306_Write_Char(msg[n], &SSD1306_Font_07X05);
			col++;
			if(col >= SSD1306_WIDTH/6){
				col = 0;
				nrow = (row+1) >= SSD1306_HEIGHT/8 ? 0 : row+1;
			}
		}

		if(row != nrow){
			row = nrow;
			SSD1306_Goto(col*6, row);
		}
	}
}
#endif

void USART2_IRQHandler(void){
    uint8_t c = 0;
    uint32_t sr;
    USART_TypeDef* h = UART_HANDLE.Instance;

    // lê o status register e trata erros até que desapareçam
    // (o manual manda ler o SR e em seguida DR)

    sr = h->ISR;

    while(sr & (UART_FLAG_ORE | UART_FLAG_PE | UART_FLAG_FE | UART_FLAG_NE)){
    	h->ICR = UART_CLEAR_OREF | UART_CLEAR_PEF | UART_CLEAR_FEF | UART_CLEAR_NEF;
    	sr = h->ISR;
        //c = h->RDR;
    }

    if(sr & UART_FLAG_RXNE){
        c = h->RDR;

        if(hw_debug_enable)
        	hw_debug(&c, 1);

        at_rx_interrupt(c);
        // some action here
    }
}

static void hw_serial_send_byte(uint8_t c){
	USART_TypeDef* h = UART_HANDLE.Instance;
	while( !(h->ISR & UART_FLAG_TXE) ) {}
	h->TDR = c;
}

uint32_t hw_serial_tx(const uint8_t* str, uint16_t len){
	uint16_t n;

	if(hw_debug_enable)
		hw_debug(str, len);

	for(n = 0 ; n < len ; n++)
		hw_serial_send_byte(str[n]);

	return len;
}

uint32_t hw_time_get(void){
	return HAL_GetTick();
}

uint32_t hw_time_elapsed(uint32_t tmr_old_ms, uint32_t tmr_new_ms){
    uint32_t elapsed_ms;

    if(tmr_new_ms < tmr_old_ms)
        elapsed_ms = UINT32_MAX - tmr_old_ms + tmr_new_ms + 1;
    else
        elapsed_ms = tmr_new_ms - tmr_old_ms;

    return elapsed_ms;
}

void hw_time_sleep(uint32_t tmr_ms){
    uint32_t tmr_new_ms;
    uint32_t tmr_old_ms = hw_time_get();

    do{
        tmr_new_ms = hw_time_get();
    } while(hw_time_elapsed(tmr_old_ms, tmr_new_ms) < tmr_ms);
}

void hw_debug_set(bool state){
	hw_debug_enable = state;
}

void hw_uart_init(void){
	UART_HANDLE.Instance->CR3 |= USART_CR3_EIE;
	UART_HANDLE.Instance->CR1 |= USART_CR1_PEIE | USART_CR1_RXNEIE;
	HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}
