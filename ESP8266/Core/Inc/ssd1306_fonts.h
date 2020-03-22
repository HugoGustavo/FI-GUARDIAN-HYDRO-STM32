#ifndef SSD1306_FONTS_H
#define SSD1306_FONTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define SSD1306_FONT_07X05 1

typedef struct
{
	uint8_t width;
	uint8_t height;
	const uint8_t *data;
} SSD1306_Font_t;

#if SSD1306_FONT_07X05 == 1
extern SSD1306_Font_t SSD1306_Font_07X05;
#endif

#ifdef __cplusplus
}
#endif

 
#endif

