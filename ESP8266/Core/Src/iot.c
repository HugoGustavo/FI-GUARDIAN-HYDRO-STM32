#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "config.h"

#include <ceb_cbuf.h>
#include "at.h"
#include "hw.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "web.h"
#include "iot.h"

const uint8_t *dweetio_hdr1 = (uint8_t *) "POST /dweet/for/";
const uint8_t *dweetio_hdr2 = (uint8_t *) " HTTP/1.1\r\n"
                             "Content-Type: application/json\r\n"
                             "Content-Length: ";

const uint8_t *iothub_ssl_hdr1 = (uint8_t *) "POST /devices/";
const uint8_t *iothub_ssl_hdr2 = (uint8_t *) "/messages/events?api-version=2015-08-15-preview HTTP/1.1\r\n"
                             "Content-Type: application/atom+xml;type=entry;charset=utf-8\r\n"  
                             "Authorization: SharedAccessSignature sr=";
const uint8_t *iothub_ssl_hdr3 = (uint8_t *) "Host: ";
const uint8_t *iothub_ssl_hdr4 = (uint8_t *) "Content-Length: ";

const uint8_t *bluemix_ssl_hdr1 = (uint8_t *) "POST /api/v0002/device/types/";
const uint8_t *bluemix_ssl_hdr2 = (uint8_t *) "/devices/";
const uint8_t *bluemix_ssl_hdr3 = (uint8_t *) "/events/status HTTP/1.1\r\n"
                             "Content-Type: application/json\r\n"
                             "Authorization: Basic ";
const uint8_t *bluemix_ssl_hdr4 = (uint8_t *) "Host: ";
const uint8_t *bluemix_ssl_hdr5 = (uint8_t *) "Content-Length: ";

const uint8_t *tspeak_hdr1 = (uint8_t *) "POST /update HTTP/1.1\r\n"
                                         "Content-Type: application/x-www-form-urlencoded\r\n"
                                         "Connection: close\r\n"
                                         "Host: api.thingspeak.com\r\n"
                                         "Content-Length: ";

uint8_t sens_val[100];
//uint8_t sens_val = 2;

uint8_t *mon_get_wifi_pwd(void)
{
	return (uint8_t *)"gfzs3569";
}

uint8_t *mon_get_wifi_ssid(void)
{
	return (uint8_t *)"AndroidAP4f29";
}

mon_cloud_id_t mon_get_cloud_id(void)
{
	return MON_DWEET_CLOUD_ID;
}

uint8_t *mon_get_device_token(void)
{
	return 0;
}

uint8_t *mon_get_device_type(void)
{
	return 0;
}

uint8_t *mon_get_cpu_tag(void)
{
	return (uint8_t *)"THING_UFU";
}

uint8_t *mon_get_iot_hub(void)
{
	return 0;
}

static void wifi_on(void)
{
    hw_esp_power_set(true);
    hw_esp_reset_set(false);
    hw_esp_enable_set(true);
}

static void wifi_off(void)
{
	hw_esp_power_set(false);
    hw_esp_reset_set(true);
    hw_esp_enable_set(false);
}

static int8_t wifi_startup(void)
{
	// do not expect so much from this command as we can be at
	// some wrong baud rate
//	cmd.id = AT_CMD_UART;
//	cmd.payload.uart.baud_rate = 115200;
//	cmd.payload.uart.data_bits = 8;
//	cmd.payload.uart.stop_bit = 1;
//	cmd.payload.uart.parity = 0;
//	cmd.payload.uart.flow_control = 0;
//	at_send_cmd_blocking(&cmd,1000);

	// first command after changing serial baud rate fails...
	cmd.id = AT_CMD_READY;
	at_send_cmd_blocking(&cmd,1000);

	cmd.id = AT_CMD_READY;
	at_send_cmd_blocking(&cmd,3000);

	if(cmd.status != AT_STATUS_OK)
		return -1;

	cmd.id = AT_CMD_WIFI_AUTO_CON;
	cmd.payload.wifi_autocon.enabled = 0;
	at_send_cmd_blocking(&cmd,1000);

    cmd.id = AT_CMD_WIFI_AP_MODE;
    cmd.payload.wifi_mode.ap_station = AT_WIFI_MODE_STATION;
    at_send_cmd_blocking(&cmd,2000);

    cmd.id = AT_CMD_WIFI_AP_DHCP;
    cmd.payload.wifi_dhcp.ap_station = 1;
    cmd.payload.wifi_dhcp.enabled = 1;
    at_send_cmd_blocking(&cmd,2000);

    cmd.id = AT_CMD_CON_MUX;
    cmd.payload.mux.enabled = 1;
    at_send_cmd_blocking(&cmd,2000);

    cmd.id = AT_CMD_WIFI_AP_SET;
    cmd.payload.wifi_ap.ssid = mon_get_wifi_ssid();
    cmd.payload.wifi_ap.pwd = mon_get_wifi_pwd();
    at_send_cmd_blocking(&cmd,30000);

	if(cmd.status != AT_STATUS_OK)
		return -2;

    cmd.id = AT_CMD_SLL_BUFFER_SIZE;
    cmd.payload.ssl_buffer.size = 4096;
    at_send_cmd_blocking(&cmd,2000);

    return 1;
}

bool send_tspeak_update(void)
{
    uint8_t val[10];
    float t = hw_temperature_get();
    int16_t ti;
    uint16_t tf;
    uint16_t len;
    bool ret;

    ti = (int16_t) t;
    tf = (uint16_t) fabs((t - ti)*100);
    sprintf((char *) sens_val,"key=%s&field1=%s&field2=%d.%d",
    		(char *) mon_get_device_token(),
			(char *) mon_get_cpu_tag(),
			ti,tf);

    SSD1306_Goto(0, 2);
    SSD1306_Write_String((uint8_t*)"Connec. tspeak...  ");

    cmd.id = AT_CMD_CON_START;
    cmd.payload.con_start.port = 443;
    cmd.payload.con_start.transport = (uint8_t *) "SSL";
    cmd.payload.con_start.site = (uint8_t *) "api.thingspeak.com";
    cmd.payload.con_start.channel = 0;
    at_send_cmd_blocking(&cmd,10000);

    sprintf((char *)val,"%u\r\n\r\n",(unsigned int)strlen((char *) sens_val));
    len = strlen((char *)tspeak_hdr1) +
			strlen((char *) val) +
			strlen((char *) sens_val);

    cmd.id = AT_CMD_CON_SEND;
    cmd.payload.con_send.size = len;
    cmd.payload.con_send.transparent = 0;
    cmd.payload.con_send.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    hw_serial_tx(tspeak_hdr1,strlen((char *)tspeak_hdr1));
    hw_serial_tx(val,strlen((char *)val));
    hw_serial_tx(sens_val,strlen((char *)sens_val));

    ret = web_client();

    cmd.id = AT_CMD_CON_CLOSE;
    cmd.payload.con_close.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    return ret;
}

bool send_bluemix_update(void)
{
    uint8_t val[10];
    float t = hw_temperature_get();
    int16_t ti;
    uint16_t tf;
    uint16_t len;
    bool ret;

    ti = (int16_t) t;
    tf = (uint16_t) fabs((t - ti)*100);
    sprintf((char *) sens_val,"{\"temperature\":%d.%d}",ti,tf);

    SSD1306_Goto(0, 2);
    SSD1306_Write_String((uint8_t*)"Connec. bluemix... ");

    cmd.id = AT_CMD_CON_START;
    cmd.payload.con_start.port = 1883;
    cmd.payload.con_start.transport = (uint8_t *) "TCP";
    cmd.payload.con_start.site = mon_get_iot_hub();
    cmd.payload.con_start.channel = 0;
    at_send_cmd_blocking(&cmd,10000);

    sprintf((char *)val,"%u\r\n\r\n",(unsigned int)strlen((char *) sens_val));
    len = strlen((char *)bluemix_ssl_hdr1) +
    		strlen((char *) mon_get_device_type()) +
			strlen((char *) bluemix_ssl_hdr2) +
			strlen((char *) mon_get_cpu_tag()) +
			strlen((char *) bluemix_ssl_hdr3) +
			strlen((char *) mon_get_device_token()) +
			strlen((const char *) at_eol) +
			strlen((char *) bluemix_ssl_hdr4) +
			strlen((char *) mon_get_iot_hub()) +
			strlen((const char *) at_eol) +
			strlen((char *) bluemix_ssl_hdr5) +
			strlen((char *) val) +
			strlen((char *) sens_val);

    cmd.id = AT_CMD_CON_SEND;
    cmd.payload.con_send.size = len;
    cmd.payload.con_send.transparent = 0;
    cmd.payload.con_send.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    hw_serial_tx(bluemix_ssl_hdr1,strlen((char *)bluemix_ssl_hdr1));
    hw_serial_tx(mon_get_device_type(),strlen((char *)mon_get_device_type()));
    hw_serial_tx(bluemix_ssl_hdr2,strlen((char *)bluemix_ssl_hdr2));
    hw_serial_tx(mon_get_cpu_tag(),strlen((char *)mon_get_cpu_tag()));
    hw_serial_tx(bluemix_ssl_hdr3,strlen((char *)bluemix_ssl_hdr3));
    hw_serial_tx(mon_get_device_token(),strlen((char *)mon_get_device_token()));
    hw_serial_tx(at_eol,strlen((char *)at_eol));
    hw_serial_tx(bluemix_ssl_hdr4,strlen((char *)bluemix_ssl_hdr4));
    hw_serial_tx(mon_get_iot_hub(),strlen((char *)mon_get_iot_hub()));
    hw_serial_tx(at_eol,strlen((char *)at_eol));
    hw_serial_tx(bluemix_ssl_hdr5,strlen((char *)bluemix_ssl_hdr5));
    hw_serial_tx(val,strlen((char *)val));
    hw_serial_tx(sens_val,strlen((char *)sens_val));

    ret = web_client();

    cmd.id = AT_CMD_CON_CLOSE;
    cmd.payload.con_close.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    return ret;
}

bool send_azure_update(void)
{
    uint8_t val[10];
    float t = hw_temperature_get();
    int16_t ti;
    uint16_t tf;
    uint16_t len;
    bool ret;

    ti = (int16_t) t;
    tf = (uint16_t) fabs((t - ti)*100);
    sprintf((char *) sens_val,"{\"temperature\":\"%d.%d\"}",ti,tf);

    SSD1306_Goto(0, 2);
    SSD1306_Write_String((uint8_t*)"Connec. azure...   ");

    cmd.id = AT_CMD_CON_START;
    cmd.payload.con_start.port = 443;
    cmd.payload.con_start.transport = (uint8_t *) "SSL";
    cmd.payload.con_start.site = mon_get_iot_hub();
    cmd.payload.con_start.channel = 0;
    at_send_cmd_blocking(&cmd,10000);

    sprintf((char *)val,"%u\r\n\r\n",(unsigned int)strlen((char *) sens_val));
    len = strlen((char *)iothub_ssl_hdr1) +
                    strlen((char *) mon_get_cpu_tag()) +
                    strlen((char *) iothub_ssl_hdr2) +
                    strlen((char *) mon_get_device_token()) +
                    strlen((const char *) at_eol) +
                    strlen((char *) iothub_ssl_hdr3) +
                    strlen((char *) mon_get_iot_hub()) +
                    strlen((const char *) at_eol) +
                    strlen((char *) iothub_ssl_hdr4) +
                    strlen((char *) val) +
                    strlen((char *) sens_val);

    cmd.id = AT_CMD_CON_SEND;
    cmd.payload.con_send.size = len;
    cmd.payload.con_send.transparent = 0;
    cmd.payload.con_send.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    hw_serial_tx(iothub_ssl_hdr1,strlen((char *)iothub_ssl_hdr1));
    hw_serial_tx(mon_get_cpu_tag(),strlen((char *) mon_get_cpu_tag()));
    hw_serial_tx(iothub_ssl_hdr2,strlen((char *)iothub_ssl_hdr2));
    hw_serial_tx(mon_get_device_token(),strlen((char *) mon_get_device_token()));
    hw_serial_tx(at_eol,strlen((const char *)at_eol));
    hw_serial_tx(iothub_ssl_hdr3,strlen((char *)iothub_ssl_hdr3));
    hw_serial_tx(mon_get_iot_hub(),strlen((char *) mon_get_iot_hub()));
    hw_serial_tx(at_eol,strlen((const char *)at_eol));
    hw_serial_tx(iothub_ssl_hdr4,strlen((char *)iothub_ssl_hdr4));
    hw_serial_tx(val,strlen((char *)val));
    hw_serial_tx(sens_val,strlen((char *) sens_val));

    ret = web_client();

    cmd.id = AT_CMD_CON_CLOSE;
    cmd.payload.con_close.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    return ret;
}

bool send_dwwtio_update(void)
{
    uint8_t val[10];
    //float t = hw_temperature_get();
    float t = 2;
    int16_t ti;
    uint16_t tf;
    uint16_t len;
    bool ret;
    uint8_t *site = (uint8_t *) "dweet.io";
    uint8_t *device = (uint8_t *) mon_get_cpu_tag();

    ti = (int16_t) t;
    tf = (uint16_t) fabs((t - ti)*100);
    sprintf((char *) sens_val,"{\"temperature\":\"%d.%d\"}",ti,tf);

    SSD1306_Goto(0, 2);
    SSD1306_Write_String((uint8_t*)"Connec. dweet.io... ");

    cmd.id = AT_CMD_CON_START;
    cmd.payload.con_start.port = 80;
    cmd.payload.con_start.transport = (uint8_t *) "TCP";
    cmd.payload.con_start.site = site;
    cmd.payload.con_start.channel = 0;
    at_send_cmd_blocking(&cmd,10000);

    if(cmd.status != AT_STATUS_OK)
    {
        SSD1306_Goto(0, 2);
        SSD1306_Write_String((uint8_t*)"Can't connect!      ");
        return false;
    }

    SSD1306_Goto(0, 2);
    SSD1306_Write_String((uint8_t*)"Sending data...     ");

    sprintf((char *)val,"%u\r\n\r\n",(unsigned int)strlen((char *) sens_val));
    len = strlen((char *)dweetio_hdr1) + 
                    strlen((char *) device) +
                    strlen((char *) dweetio_hdr2) +
                    strlen((char *) val) +  
                    strlen((char *) sens_val);


    cmd.id = AT_CMD_CON_SEND;
    cmd.payload.con_send.size = len;
    cmd.payload.con_send.transparent = 0;
    cmd.payload.con_send.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    hw_serial_tx(dweetio_hdr1,strlen((char *)dweetio_hdr1));
    hw_serial_tx(device,strlen((char *) device));
    hw_serial_tx(dweetio_hdr2,strlen((char *)dweetio_hdr2));
    hw_serial_tx(val,strlen((char *)val));
    hw_serial_tx(sens_val,strlen((char *) sens_val));

    if(cmd.status != AT_STATUS_OK)
    {
        SSD1306_Goto(0, 2);
        SSD1306_Write_String((uint8_t*)"Can't send!         ");
        ret = false;
        goto dweet_close_tcp_con;
    }
    
    SSD1306_Goto(0, 2);
    SSD1306_Write_String((uint8_t*)"Waiting response... ");

    ret = web_client();

    if(!ret)
    {
        SSD1306_Goto(0, 2);
        SSD1306_Write_String((uint8_t*)"No response!        ");
    }

dweet_close_tcp_con:

    cmd.id = AT_CMD_CON_CLOSE;
    cmd.payload.con_close.channel = 0;
    at_send_cmd_blocking(&cmd,2000);

    //hw_serial_tx("AT+GSLP=4000\r\n",14);
    return ret;
}

void iot_off(void)
{
	wifi_off();
}

int8_t iot_on(void)
{
	wifi_on();
    hw_time_sleep(1000);
    at_init();

    return wifi_startup();
}


bool iot_update(void)
{
	bool ret = false;

	// TODO: check AT+CIPSTATUS (is connected ?)
	switch(mon_get_cloud_id())
	{
	case MON_DWEET_CLOUD_ID:
		ret = send_dwwtio_update();
		break;
	case MON_AZURE_CLOUD_ID:
		ret = send_azure_update();
		break;
	case MON_BLUEMIX_CLOUD_ID:
		ret = send_bluemix_update();
		break;
	case MON_TSPEAK_CLOUD_ID:
		ret = send_tspeak_update();
		break;
	default:
		ret = false;
	}

	return ret;
}


