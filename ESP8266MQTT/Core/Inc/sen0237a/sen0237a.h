#ifndef SEN0237A_H
#define SEN0237A_H

#include <stdio.h>
#include <stdlib.h>
#include <util/stm32_util.h>
#include "stm32l4xx_hal.h"
#include <dma/direct_memory_access.h>

typedef struct __attribute__((__packed__)) sen0237a {
	direct_memory_access* 	dma;
	uint32_t 				channel;

	char 					mode_calibration;
	char					points_for_calibration;

	uint32_t 				voltage_point_1;
	uint8_t 				temperature_point_1;

	uint32_t				voltage_point_2;
	uint8_t 				temperature_point_2;

	uint32_t				current_temperature;

	uint16_t 				table_reference[41];
} sen0237a;

sen0237a* sen0237a_init(direct_memory_access* dma, uint32_t channel, char mode_calibration, char points_for_calibration, uint32_t voltage_point_1, uint8_t temperature_point_1, uint32_t voltage_point_2, uint8_t temperature_point_2);

void sen0237a_destroy(sen0237a* sen0237a);

uint32_t sen0237a_get_channel(sen0237a* sen0237a);

void sen0237a_set_channel(sen0237a* sen0237a, uint32_t channel);

char sen0237a_get_mode_calibration(sen0237a* sen0237a);

void sen0237a_set_mode_calibration(sen0237a* sen0237a, char mode_calibration);

char sen0237a_get_points_for_calibration(sen0237a* sen0237a);

void sen0237a_set_points_for_calibration(sen0237a* sen0237a, char points_for_calibration);

float sen0237a_get_voltage_point_1(sen0237a* sen0237a);

void sen0237a_set_voltage_point_1(sen0237a* sen0237a, float voltage_point_1);

uint8_t sen0237a_get_temperature_point_1(sen0237a* sen0237a);

void sen0237a_set_temperature_point_1(sen0237a* sen0237a, uint8_t temperature_point_1);

float sen0237a_get_voltage_point_2(sen0237a* sen0237a);

void sen0237a_set_voltage_point_2(sen0237a* sen0237a, float voltage_point_2);

uint8_t sen0237a_get_temperature_point_2(sen0237a* sen0237a);

void sen0237a_set_temperature_point_2(sen0237a* sen0237a, uint8_t temperature_point_2);

uint32_t sen0237a_get_current_temperature(sen0237a* sen0237a);

void sen0237a_set_current_temperature(sen0237a* sen0237a, uint32_t current_temperature);

direct_memory_access* sen0237a_get_dma(sen0237a* sen0237a);

void sen0237a_set_dma(sen0237a* sen0237a, direct_memory_access* dma);

float sen0237a_read(sen0237a* sen0237a);

#endif
