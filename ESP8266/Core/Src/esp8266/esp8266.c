#include <esp8266/esp8266.h>

esp8266* esp8266_init(void){
	esp8266* esp = (esp8266*) malloc(sizeof(esp8266));
    esp->ssid = NULL;
    esp->password = NULL;
    esp->connected = false;
    esp->ip = NULL;
    esp->port = 1883;
    esp8266_turn_on(esp);
    return esp;
}

void esp8266_destroy(esp8266* esp8266){
	if( esp8266 == NULL ) return;
	esp8266_turn_off(esp8266);
	free(esp8266);
	esp8266 = NULL;
}

void esp8266_turn_on(esp8266* esp8266){
	if( esp8266 == NULL ) return;
	// app_init
	hw_esp_power_set(true);
	hw_time_sleep(100);
	hw_uart_init();

	// iot_on
	// WifiOn
	hw_esp_power_set(true);
	hw_esp_reset_set(false);
	hw_esp_enable_set(true);

	// iot_on
	hw_time_sleep(1000);
	at_init();

	cmd.id = AT_CMD_READY;
	at_send_cmd_blocking(&cmd,1000);

	cmd.id = AT_CMD_READY;
	at_send_cmd_blocking(&cmd,3000);

	if(cmd.status != AT_STATUS_OK)		return NULL;

	cmd.id = AT_CMD_WIFI_AUTO_CON;
	cmd.payload.wifi_autocon.enabled = 0;
	at_send_cmd_blocking(&cmd,1000);
}

void esp8266_turn_off(esp8266* esp){
	if( esp == NULL ) return;
	hw_esp_power_set(false);
	hw_esp_reset_set(true);
	hw_esp_enable_set(false);
}

void esp8266_reset(esp8266* esp8266){
	if( esp8266 == NULL ) return;
	cmd.id = AT_CMD_RST;
	at_send_cmd_blocking(&cmd, 6000);
}

void esp8266_setOprToStationSoftAP(esp8266* esp8266){
	if ( esp8266 == NULL ) return;

	cmd.id = AT_CMD_WIFI_AP_MODE;
	cmd.payload.wifi_mode.ap_station = AT_WIFI_MODE_STATION;
	at_send_cmd_blocking(&cmd,2000);

    cmd.id = AT_CMD_WIFI_AP_DHCP;
    cmd.payload.wifi_dhcp.ap_station = 1;
    cmd.payload.wifi_dhcp.enabled = 1;
    at_send_cmd_blocking(&cmd,2000);
}

bool esp8266_joinAP(esp8266* esp8266, uint8_t* ssid, uint8_t* password){
	if( esp8266 == NULL ) return false;

	cmd.id = AT_CMD_WIFI_AP_SET;
	cmd.payload.wifi_ap.ssid = ssid;
	cmd.payload.wifi_ap.pwd = password;

	at_send_cmd_blocking(&cmd, 30000);
	if( cmd.status != AT_STATUS_OK ) return false;

	cmd.id = AT_CMD_SLL_BUFFER_SIZE;
	cmd.payload.ssl_buffer.size = 4096;
	at_send_cmd_blocking(&cmd, 2000);

	return true;

}

bool esp8266_enableMUX(esp8266* esp8266){
	if ( esp8266 == NULL ) return false;
    cmd.id = AT_CMD_CON_MUX;
    cmd.payload.mux.enabled = 1;
    at_send_cmd_blocking(&cmd, 2000);

    return true;
}

bool esp8266_disableMUX(esp8266* esp8266){
	if ( esp8266 == NULL ) return false;
    cmd.id = AT_CMD_CON_MUX;
    cmd.payload.mux.enabled = 0;
    at_send_cmd_blocking(&cmd, 2000);
    return true;
}

bool esp8266_createTCP(esp8266* esp8266, uint8_t* ip, uint16_t port){
	if ( esp8266 == NULL ) return false;

	cmd.id = AT_CMD_CON_START;
	cmd.payload.con_start.port = port;
	cmd.payload.con_start.transport = (uint8_t*) "TCP";
	cmd.payload.con_start.site = ip;
	cmd.payload.con_start.channel = 0;
	at_send_cmd_blocking(&cmd, 10000);

	esp8266->connected = true; //cmd.status != AT_STATUS_OK ? false : true;

	return esp8266->connected;
}

bool esp8266_releaseTCP(esp8266* esp8266){
	if( esp8266 == NULL ) return true;

	cmd.id = AT_CMD_CON_CLOSE;
	cmd.payload.con_close.channel = 0;
	at_send_cmd_blocking(&cmd, 5000);

    esp8266->connected = false;
    return true;
}

uint32_t esp8266_recv(esp8266* esp8266){
	return 0;
}

bool esp8266_send(esp8266* esp8266, uint8_t* buffer, uint16_t buffer_size){
	if( esp8266 == NULL ) return false;

    cmd.id = AT_CMD_CON_SEND;
    cmd.payload.con_send.size = buffer_size;
    cmd.payload.con_send.transparent = 0;
    cmd.payload.con_send.channel = 0;
    at_send_cmd_blocking(&cmd, 2000);

    hw_serial_tx(buffer, buffer_size);

    bool result = cmd.status != AT_STATUS_OK ? false : true;

    return result;
}

void esp8266_wait_for_sending(uint16_t timeoutInMilliseconds){
	clock_t goal = clock() + timeoutInMilliseconds;
	while (goal > clock());
}
