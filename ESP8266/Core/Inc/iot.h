/*
 * iot.h
 *
 *  Created on: 18 de dez de 2016
 *      Author: marcelo
 */

#ifndef IOT_H_
#define IOT_H_

typedef enum mon_cloud_id_e
{
	MON_NO_CLOUD_ID      = 0,
	MON_DWEET_CLOUD_ID   = 1,
	MON_AZURE_CLOUD_ID   = 2,
	MON_BLUEMIX_CLOUD_ID = 3,
	MON_TSPEAK_CLOUD_ID  = 4,
	MON_MAX_CLOUD_ID
} mon_cloud_id_t;

int8_t iot_on(void);
void iot_off(void);
bool iot_update(void);

#endif /* IOT_H_ */
