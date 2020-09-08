/*
 * hw.h
 *
 *  Created on: 17 de dez de 2016
 *      Author: marcelo
 */

#ifndef HW_H_
#define HW_H_

void hw_display_set(bool value);

void hw_esp_power_set(bool value);

void hw_esp_reset_set(bool value);

void hw_esp_enable_set(bool value);

bool hw_user_key_get(void);

void hw_user_led_set(bool value);

float hw_temperature_get(void);

void hw_debug(const uint8_t *msg, uint16_t len);

void hw_time_sleep(uint32_t tmr_ms);

uint32_t hw_time_elapsed(uint32_t tmr_old_ms, uint32_t tmr_new_ms);

uint32_t hw_time_get(void);

uint32_t hw_serial_tx(const uint8_t *str, uint16_t len);

void hw_debug_set(bool state);

void hw_uart_init(void);

#endif /* HW_H_ */
