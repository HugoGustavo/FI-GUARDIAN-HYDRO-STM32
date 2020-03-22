#ifndef SSD1306_H
#define SSD1306_H

#ifdef __cplusplus
extern "C" {
#endif

#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT  64

typedef enum
{
	SSD1306_COLOR_BLACK = 0x00,
	SSD1306_COLOR_WHITE = 0x01
} SSD1306_COLOR_t;

uint8_t SSD1306_Init(void);
void SDD1306_Clear_Screen(void);
void SSD1306_Goto(uint8_t col, uint8_t row);
uint8_t SSD1306_Write_Command(uint8_t command);
uint8_t SSD1306_Write_Data(uint8_t value);
void SSD1306_Write_Char(uint8_t c, SSD1306_Font_t* font);
void SSD1306_Write_Buffer(uint8_t *str, uint8_t size, SSD1306_Font_t* font);
void SSD1306_Write_String(uint8_t *str);
void SSD1306_Write_Centered_String(uint8_t *str, uint8_t row);
void SSD1306_On(void);
void SSD1306_Off(void);

#ifdef __cplusplus
}
#endif

#endif
