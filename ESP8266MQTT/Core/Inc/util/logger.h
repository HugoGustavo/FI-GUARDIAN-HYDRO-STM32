#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ssd1306/ssd1306_fonts.h>
#include <ssd1306/ssd1306.h>

typedef struct __attribute__((__packed__)) logger {
	unsigned int line;
} logger;

extern logger* logger_instance;

extern const unsigned int LOGGER_MAX_LINES;

logger* logger_get_instance();

void logger_trace(logger* logger, char* input);

void logger_off(logger* logger, char* input);

void logger_fatal(logger* logger, char* input);

void logger_error(logger* logger, char* input);

void logger_warn(logger* logger, char* input);

void logger_info(logger* logger, char* input);

void logger_debug(logger* logger, char* input);

void logger_clean(logger* logger);

#endif
