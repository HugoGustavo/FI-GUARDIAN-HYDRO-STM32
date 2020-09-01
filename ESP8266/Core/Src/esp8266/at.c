#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <esp8266/config.h>
#include <esp8266/ceb_cbuf.h>
#include <esp8266/at.h>
#include <esp8266/hw.h>

const uint8_t* at_cmd_basename_str[] = {
    (uint8_t*) "",
    (uint8_t*) "+RST",
    (uint8_t*) "E",
	(uint8_t*) "+CWAUTOCONN",
    (uint8_t*) "+CWMODE_CUR", // DEF
    (uint8_t*) "+CWLAP",
    (uint8_t*) "+CWJAP_CUR", // DEF
    (uint8_t*) "+CWDHCP_CUR", // DEF
    (uint8_t*) "+CWDHCPS_CUR", // DEF
    (uint8_t*) "+CIPAP_CUR", //DEF
    (uint8_t*) "+CWSAP_CUR", // DEF
    (uint8_t*) "+CIPSERVER",
    (uint8_t*) "+CIPSTO",
    (uint8_t*) "+CIPMUX",
    (uint8_t*) "+CIPSTART",
    (uint8_t*) "+CIPCLOSE",
    (uint8_t*) "+CIPSEND",
    (uint8_t*) "+CIPSSLSIZE",
    (uint8_t*) "+CIPMODE",
    (uint8_t*) "+UART_DEF",
};

ceb_cbuf_str_t at_ok_error[] = {
    { (uint8_t*) "OK\r\n", 4, 0 },
    { (uint8_t*) "ERROR\r\n", 7, 0 }
};

const uint8_t* at_eol 		= (uint8_t*) "\r\n";
const uint8_t* at_at 		= (uint8_t*) "AT";
const uint8_t* at_ready 	= (uint8_t*) "ready\r\n";

uint8_t at_rx_cbuf_area[AT_CBUF_MAX];
ceb_cbuf_t at_cb;
at_cmd_t cmd;
volatile bool at_started = false;

bool at_init(void) {
    if(ceb_cbuf_init(&at_cb, at_rx_cbuf_area, AT_CBUF_MAX) == CEB_CBUF_OK)
    	at_started = true;

    return at_started;
}   

ceb_cbuf_t* at_get_cbuf(void){
    return &at_cb;
}

at_status_t at_send_cmd_blocking(at_cmd_t* cmd, uint32_t tmrout_ms){
    if(cmd->id >= AT_CMD_NONE)
        return AT_STATUS_INVAL_CMD;

    // AT, if any
    hw_serial_tx(at_at, strlen((const char*)at_at));

    // base command name
    hw_serial_tx(at_cmd_basename_str[cmd->id], strlen((const char*)at_cmd_basename_str[cmd->id]));

    // parameters, if any
    switch(cmd->id){
        case AT_CMD_WIFI_AP_MODE: {
            uint8_t mode = '0' + cmd->payload.wifi_mode.ap_station;
            hw_serial_tx((uint8_t *)"=", 1);
            hw_serial_tx(&mode, 1);
            break;
        }

        case AT_CMD_CON_MUX: {
            uint8_t mode = '0' + cmd->payload.mux.enabled;
            hw_serial_tx((uint8_t *)"=", 1);
            hw_serial_tx(&mode, 1);
            break;
        }

        case AT_CMD_CON_MODE: {
            uint8_t mode = '0' + cmd->payload.con_mode.mode;
            hw_serial_tx((uint8_t *)"=", 1);
            hw_serial_tx(&mode, 1);
            break;            
        }

        case AT_CMD_ECHO: {
            uint8_t mode = '0' + cmd->payload.echo.enabled;
            hw_serial_tx(&mode, 1);
            break;                        
        }

        case AT_CMD_WIFI_AUTO_CON: {
            uint8_t enabled = '0' + cmd->payload.wifi_autocon.enabled;
            hw_serial_tx((uint8_t *)"=", 1);
            hw_serial_tx(&enabled, 1);
        	break;
        }

        case AT_CMD_WIFI_AP_SET: {
            hw_serial_tx((uint8_t *)"=\"", 2);
            hw_serial_tx(cmd->payload.wifi_ap.ssid, strlen((char*)cmd->payload.wifi_ap.ssid));
            hw_serial_tx((uint8_t *)"\",\"", 3);
            hw_serial_tx(cmd->payload.wifi_ap.pwd, strlen((char*)cmd->payload.wifi_ap.pwd));
            hw_serial_tx((uint8_t *)"\"", 1);
            break;
        }

        case AT_CMD_WIFI_AP_DHCP: {
            uint8_t val[10];
            sprintf((char*)val, "=%d,%d", cmd->payload.wifi_dhcp.ap_station, cmd->payload.wifi_dhcp.enabled);
            hw_serial_tx(val, strlen((char*)val));
            break;
        }

        case AT_CMD_WIFI_AP_NET_CFG: {
            hw_serial_tx((uint8_t *)"=\"", 2);
            hw_serial_tx(cmd->payload.wifi_net_cfg.ip, strlen((char*)cmd->payload.wifi_net_cfg.ip));
            hw_serial_tx((uint8_t *)"\",\"", 3);
            hw_serial_tx(cmd->payload.wifi_net_cfg.gateway, strlen((char*)cmd->payload.wifi_net_cfg.gateway));
            hw_serial_tx((uint8_t *)"\",\"", 3);
            hw_serial_tx(cmd->payload.wifi_net_cfg.mask, strlen((char*)cmd->payload.wifi_net_cfg.mask));
            hw_serial_tx((uint8_t *)"\"", 1);
            break;
        }

        case AT_CMD_WIFI_AP_DHCP_CFG: {
            uint8_t val[10];
            sprintf((char *)val, "=%d,%d,\"", cmd->payload.wifi_dhcp_cfg.enabled, cmd->payload.wifi_dhcp_cfg.lease_time_min);
            hw_serial_tx(val, strlen((char*)val));
            hw_serial_tx(cmd->payload.wifi_dhcp_cfg.ip_begin, strlen((char*)cmd->payload.wifi_dhcp_cfg.ip_begin));
            hw_serial_tx((uint8_t *)"\",\"", 3);
            hw_serial_tx(cmd->payload.wifi_dhcp_cfg.ip_end, strlen((char*)cmd->payload.wifi_dhcp_cfg.ip_end));
            hw_serial_tx((uint8_t *)"\"", 1);
            break;
        }
        case AT_CMD_WIFI_AP_SECURITY: {
            uint8_t val[16];
            hw_serial_tx((uint8_t *)"=\"", 2);
            hw_serial_tx(cmd->payload.wifi_security.ssid, strlen((char*)cmd->payload.wifi_security.ssid));
            hw_serial_tx((uint8_t *)"\",\"", 3);
            hw_serial_tx(cmd->payload.wifi_security.pwd, strlen((char*)cmd->payload.wifi_security.pwd));
            sprintf((char*)val, "\",%d,%d,%d,%d", cmd->payload.wifi_security.channel, cmd->payload.wifi_security.crypto, cmd->payload.wifi_security.max_conn, cmd->payload.wifi_security.ssid_hidden);
            hw_serial_tx(val, strlen((char*)val));
            break;
        }

        case AT_CMD_CON_SERVER: {
            uint8_t val[10];
            sprintf((char*)val,"=%d,%d", cmd->payload.con_server.create, cmd->payload.con_server.port);
            hw_serial_tx(val, strlen((char*)val));
            break;
        }

        case AT_CMD_CON_SERVER_TMROUT: {
            uint8_t val[10];
            sprintf((char*)val, "=%d", cmd->payload.con_server_tmrout.timeout_s);
            hw_serial_tx(val, strlen((char*)val));
            break;
        }

        case AT_CMD_SLL_BUFFER_SIZE: {
            uint8_t val[10];
            sprintf((char *)val, "=%d", cmd->payload.ssl_buffer.size);
            hw_serial_tx(val, strlen((char*)val));
            break;
        }

        case AT_CMD_CON_START: {
            uint8_t val[10];
            if(cmd->payload.con_start.channel >= 0) {
                sprintf((char *)val, "=%d,\"", cmd->payload.con_start.channel);
                hw_serial_tx(val,strlen((char*)val));
            }
            else hw_serial_tx((uint8_t *)"=\"", 2);
            
            hw_serial_tx(cmd->payload.con_start.transport, strlen((char*)cmd->payload.con_start.transport));
            hw_serial_tx((uint8_t *)"\",\"", 3);
            hw_serial_tx(cmd->payload.con_start.site, strlen((char*)cmd->payload.con_start.site));
            sprintf((char*)val, "\",%d", cmd->payload.con_start.port);
            hw_serial_tx(val, strlen((char*)val));

            if(strcmp((char*)cmd->payload.con_start.transport, "UDP") == 0) {
                sprintf((char*) val, ",%d,0", cmd->payload.con_start.port);
                hw_serial_tx(val, strlen((char*)val));
            }            

            break;
        }

        case AT_CMD_CON_SEND: {
            if(cmd->payload.con_send.transparent == 0){
                uint8_t val[10];
                if(cmd->payload.con_send.channel >= 0)
                    sprintf((char*)val, "=%d,%d", cmd->payload.con_send.channel, cmd->payload.con_send.size);
                else
                    sprintf((char*)val, "=%d", cmd->payload.con_send.size);

                hw_serial_tx(val, strlen((char*) val));

                // check UDP
                if((strlen((char*) cmd->payload.con_send.site) > 0) && (cmd->payload.con_send.port > 0)){
                    hw_serial_tx((uint8_t *)",\"", 3);
                    hw_serial_tx(cmd->payload.con_send.site, strlen((char*)cmd->payload.con_send.site));
                    sprintf((char*)val, "\",%d", cmd->payload.con_send.port);
                    hw_serial_tx(val, strlen((char*)val));
                }
            }            
            break;
        }

        case AT_CMD_CON_CLOSE: {
            if(cmd->payload.con_close.channel >= 0){
            	uint8_t val[10];
                sprintf((char*)val, "=%d", cmd->payload.con_close.channel);
                hw_serial_tx(val, strlen((char*)val));
            }
            break;
        }

        case AT_CMD_UART:{
            uint8_t val[20];
            sprintf((char*)val, "=%u,%d,%d,%d,%d", (unsigned int) cmd->payload.uart.baud_rate, cmd->payload.uart.data_bits, cmd->payload.uart.stop_bit, cmd->payload.uart.parity, cmd->payload.uart.flow_control);
            hw_serial_tx(val, strlen((char*)val));
        	break;
        }

        default:
            break;
    }

    // end of line, if any
    hw_serial_tx(at_eol, strlen((const char*)at_eol));
    
    // set expected answer
    int16_t ans;
    uint16_t nb;
    switch(cmd->id){
        case AT_CMD_RST:
            ans = ceb_cbuf_find_str(&at_cb, (uint8_t*) at_ready, strlen((const char*)at_ready), &nb, tmrout_ms);
            break;
        case AT_CMD_CON_SEND:
            ans = ceb_cbuf_find_str(&at_cb, (uint8_t *)">", 1, &nb, tmrout_ms);
            break;
        default:
            ans = ceb_cbuf_find_multi_str(&at_cb, at_ok_error, 2, tmrout_ms);
            break;
    }

    switch(ans){
        case 0:
        case 2:
            cmd->status = AT_STATUS_OK;
            break;
        case 1:
            cmd->status = AT_STATUS_ERROR;
            break;
        case -1:
        default:
            cmd->status = AT_STATUS_NO_ANSWER;
            break;
    }
    return AT_STATUS_OK;
}

void at_rx_interrupt(uint8_t c){
	if(at_started){
		if(ceb_cbuf_put(&at_cb, c) == CEB_CBUF_FULL){
			//printf("CB FULL\n");
			//fflush(stdout);
		}
		else{
			//printf("%02X-",buffer[0]);
			//printf("%c",c);
			//fflush(stdout);
		}
	}
}
