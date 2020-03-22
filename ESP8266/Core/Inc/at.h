#ifndef __AT__
#define __AT__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum at_status_e
{
    AT_STATUS_OK,
    AT_STATUS_ERROR,
    AT_STATUS_TMROUT,
    AT_STATUS_INVAL_CMD,
    AT_STATUS_NO_ANSWER,
} at_status_t;

typedef enum at_con_channel_e
{
    AT_CON_CHANNEL_SINGLE = 0,
    AT_CON_CHANNEL_1 = 1,
    AT_CON_CHANNEL_2 = 2,
    AT_CON_CHANNEL_3 = 3,
    AT_CON_CHANNEL_4 = 4,
} at_con_channel_t;

typedef enum at_con_proto_e
{
    AT_CON_PROTO_TCP,
    AT_CON_PROTO_UDP,
    AT_CON_PROTO_SSL
} at_con_proto_t;

typedef enum at_wifi_mode_e
{
    AT_WIFI_MODE_STATION = 1,
    AT_WIFI_MODE_AP = 2,
    AT_WIFI_MODE_AP_STATION = 3
} at_wifi_mode_t;

typedef enum at_wifi_ap_dhcp_e
{
    AT_WIFI_AP_DHCP_AP = 0,
    AT_WIFI_AP_DHCP_STATION = 1,
    AT_WIFI_AP_DHCP_AP_STATION = 2
} at_wifi_ap_dhcp_t;

typedef enum at_wifi_ap_encryption_e
{
    AT_WIFI_AP_ENCRYPTION_OPEN = 0,
    AT_WIFI_AP_ENCRYPTION_WPA_PSK = 2,
    AT_WIFI_AP_ENCRYPTION_WPA2_PSK = 3,
    AT_WIFI_AP_ENCRYPTION_WPA_WPA2_PSK = 4,
} at_wifi_ap_encryption_t;

typedef enum at_cmd_id_e
{
    AT_CMD_READY = 0,
    AT_CMD_RST,
    AT_CMD_ECHO,
    AT_CMD_WIFI_AUTO_CON,
    AT_CMD_WIFI_AP_MODE,
    AT_CMD_WIFI_LIST,
    AT_CMD_WIFI_AP_SET,
    AT_CMD_WIFI_AP_DHCP,
    AT_CMD_WIFI_AP_DHCP_CFG,
    AT_CMD_WIFI_AP_NET_CFG,
    AT_CMD_WIFI_AP_SECURITY,
    AT_CMD_CON_SERVER,
    AT_CMD_CON_SERVER_TMROUT,
    AT_CMD_CON_MUX,
    AT_CMD_CON_START,
    AT_CMD_CON_CLOSE,
    AT_CMD_CON_SEND,
    AT_CMD_SLL_BUFFER_SIZE,
    AT_CMD_CON_MODE,
    AT_CMD_UART,
    AT_CMD_NONE,
} at_cmd_id_t;

typedef struct at_cmd_reset_s
{
} at_cmd_reset_t;

typedef struct at_cmd_echo_s
{
    uint8_t enabled;
} at_cmd_echo_t;

typedef struct at_cmd_mux_s
{
    uint8_t enabled;
} at_cmd_mux_t;

typedef struct at_cmd_wifi_autocon_s
{
    uint8_t enabled;
} at_cmd_wifi_autocon_t;

typedef struct at_cmd_wifi_mode_s
{
    uint8_t ap_station;
} at_cmd_wifi_mode_t;

typedef struct at_cmd_wifi_ap_dhcp_e
{
    uint8_t ap_station;
    uint8_t enabled;
} at_cmd_wifi_ap_dhcp_t;

typedef struct at_cmd_wifi_ap_net_cfg_e
{
    const uint8_t *ip;
    const uint8_t *gateway;
    const uint8_t *mask;
} at_cmd_wifi_ap_net_cfg_t;

typedef struct at_cmd_wifi_ap_dhcp_cfg_e
{
    uint8_t enabled;
    uint16_t lease_time_min;
    const uint8_t *ip_begin;
    const uint8_t *ip_end;
} at_cmd_wifi_ap_dhcp_cfg_t;

typedef struct at_cmd_wifi_ap_security_e
{
    const uint8_t *ssid;
    const uint8_t *pwd;
    uint8_t channel;
    uint8_t crypto;
    uint8_t max_conn;
    uint8_t ssid_hidden;
} at_cmd_wifi_ap_security_t;

typedef struct at_cmd_con_close_s
{
    uint8_t channel;
} at_cmd_con_close_t;

typedef struct at_cmd_con_server_s
{
    uint8_t create;
    uint16_t port;
} at_cmd_con_server_t;

typedef struct at_cmd_con_server_tmrout_s
{
    uint16_t timeout_s;
} at_cmd_con_server_tmrout_t;

typedef struct at_cmd_wifi_ap_set_s
{
    const uint8_t *ssid;
    const uint8_t *pwd;
} at_cmd_wifi_ap_set_t;

typedef struct at_cmd_con_start_s
{
    const uint8_t *site;
    const uint8_t *transport;
    int8_t channel;
    uint16_t port;
} at_cmd_con_start_t;

typedef struct at_cmd_con_send_s
{
    uint16_t size;
    int8_t channel;
    const uint8_t *site;
    uint16_t port;
    uint8_t transparent;
} at_cmd_con_send_t;

typedef struct at_cmd_ssl_buffer_e
{
    uint16_t size;
} at_cmd_ssl_buffer_t;

typedef struct at_cmd_con_mode_s
{
    uint8_t mode;
} at_cmd_con_mode_t;

typedef struct at_cmd_uart_s
{
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t stop_bit;
    uint8_t parity;
    uint8_t flow_control;
} at_cmd_uart_t;

typedef union at_cmds_u
{
    at_cmd_reset_t reset;
    at_cmd_echo_t echo;
    at_cmd_mux_t mux;
    at_cmd_wifi_autocon_t wifi_autocon;
    at_cmd_wifi_mode_t wifi_mode;
    at_cmd_wifi_ap_set_t wifi_ap;
    at_cmd_wifi_ap_dhcp_t wifi_dhcp;
    at_cmd_wifi_ap_net_cfg_t wifi_net_cfg;
    at_cmd_wifi_ap_dhcp_cfg_t wifi_dhcp_cfg;
    at_cmd_wifi_ap_security_t wifi_security;
    at_cmd_ssl_buffer_t ssl_buffer;
    at_cmd_con_close_t con_close;
    at_cmd_con_start_t con_start;
    at_cmd_con_send_t con_send;
    at_cmd_con_server_t con_server;
    at_cmd_con_server_tmrout_t con_server_tmrout;
    at_cmd_con_mode_t con_mode;
    at_cmd_uart_t uart;
} at_cmds_t;

typedef struct at_cmd_s
{
    at_cmd_id_t id;
    at_cmds_t payload;
    at_status_t status;
} at_cmd_t;

extern const uint8_t *at_eol;
extern at_cmd_t cmd;

bool at_init(void);
ceb_cbuf_t *at_get_cbuf(void);
void at_rx_interrupt(uint8_t c);
at_status_t at_send_cmd_blocking(at_cmd_t *cmd, uint32_t tmrout_ms);
void at_rx_data(uint8_t *buffer, uint16_t len, uint32_t tmrout_ms);

#ifdef __cplusplus
}
#endif

#endif /* __AT__ */


