#include "../../Inc/util/logger.h"


logger* logger_instance = NULL;

const unsigned int LOGGER_MAX_LINES = 8;

logger* logger_get_instance(){
	if( logger_instance == NULL ){
		SSD1306_Init();
		SDD1306_Clear_Screen();
		logger_instance = (logger*) malloc(sizeof(logger));
		logger_instance->line = 0;
	}
	return logger_instance;
}

void logger_trace(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[T] ", input));
}

void logger_off(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[O] ", input));
}

void logger_fatal(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[F] ", input));
}

void logger_error(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[E] ", input));
}

void logger_warn(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[W] ", input));
}

void logger_info(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[I] ", input));
}

void logger_debug(logger* logger, char* input){
	if( logger == NULL ) return;
	if( logger->line == LOGGER_MAX_LINES-1) SDD1306_Clear_Screen();
	unsigned int line = (++logger->line) % LOGGER_MAX_LINES;
	SSD1306_Goto(0, line);
	SSD1306_Write_String((uint8_t*) string_util_concat("[D] ", input));
}
