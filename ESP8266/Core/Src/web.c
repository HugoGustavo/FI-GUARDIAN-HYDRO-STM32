#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include <ceb_cbuf.h>
#include "at.h"
#include "hw.h"

// this buffer should store the setup request entirely
// TODO: REMOVE IT AND USE CIRC. BUFFER INSTEAD (NEW FUNCTION TO USE FROM IT WITHOUT ADVANCING CONSUMER)
#define PAYLOAD_MAX_BUF 600

ceb_cbuf_str_t web_channel_data[] =
{ 
    { (uint8_t *) "0,", 2, 0}, 
    { (uint8_t *) "1,", 2, 0}, 
    { (uint8_t *) "2,", 2, 0}, 
    { (uint8_t *) "3,", 2, 0},
    { (uint8_t *) "+IPD,", 5, 0}, 
};

ceb_cbuf_str_t web_conn_state[] =
{ 
    { (uint8_t *) "CONNECT\r\n", 9, 0}, 
    { (uint8_t *) "CLOSED\r\n", 8, 0}, 
};

uint8_t web_buffer[PAYLOAD_MAX_BUF];
uint8_t web_http_method[10];
uint8_t web_page[10];

static bool web_wait_response(uint8_t *channel, uint16_t *bytes)
{
    int16_t ans;
    uint16_t buf_len;
    int c,b;
    bool ret = false;

    ans = ceb_cbuf_find_multi_str(at_get_cbuf(),web_channel_data,5,5000);
    if(ans == -1)
    {
        ceb_cbuf_flush(at_get_cbuf());
    } // 0, 1, 2, 3 => channel (open or close information)
    else if(ans < 3) 
    {
        //uint8_t channel = (uint8_t) ans;
        ans = ceb_cbuf_find_multi_str(at_get_cbuf(),web_conn_state,2,5000);
        if(ans == -1)
        {
            ceb_cbuf_flush(at_get_cbuf());
        }
        //if(ans == 0)
            //printf("Connection openned for channel %d\r\n", channel);
        //else
            //printf("Connection closed for channel %d\r\n", channel);
    } // 4 => +IPD
    else
    {
        buf_len = PAYLOAD_MAX_BUF-1;
        ans = ceb_cbuf_get_str_until_find(at_get_cbuf(),web_buffer,&buf_len,(uint8_t *)":",1,5000);
        if(buf_len < 4)
        {
            ceb_cbuf_flush(at_get_cbuf());
        }

        web_buffer[buf_len] = '\0';
        if(sscanf((char *)web_buffer,"%d,%d:",&c,&b) != 2)
        {
            ceb_cbuf_flush(at_get_cbuf());
        }
        else
        {
            *channel = (uint8_t) c;
            *bytes = (uint16_t) b;
            ret = true;
        }
    }

    return ret;
}

static bool web_get_payload(uint16_t bytes)
{
    uint16_t buf_len;

    //printf("Payload: %d bytes\r\n",bytes);
    if(bytes < (PAYLOAD_MAX_BUF-1))
    {
        buf_len = bytes;
        ceb_cbuf_get_str(at_get_cbuf(),web_buffer,&buf_len,10000);
        web_buffer[buf_len] = '\0';
        if(buf_len != bytes)
        {
            hw_time_sleep(3000);
            ceb_cbuf_flush(at_get_cbuf());
            return false;
        }
        else
            return true;
    }
    else
    {
        //printf("Payload is too large\r\n");
        ceb_cbuf_flush(at_get_cbuf());
        return false;
    }    
}

bool web_client(void)
{
    uint16_t buf_len;
    uint8_t channel = 0;
    uint16_t bytes = 0;
    int ret_code;
    uint16_t nb;

    if(web_wait_response(&channel,&bytes))
    {
        // HTTP/1.0 200 OK
        buf_len = PAYLOAD_MAX_BUF-1;
        ceb_cbuf_get_str_until_find(at_get_cbuf(),web_buffer,&buf_len,(uint8_t *)at_eol,strlen((const char *)at_eol),5000);
        if(buf_len < 16)
        {
            ceb_cbuf_flush(at_get_cbuf());
            return false;
        }

        web_buffer[buf_len] = '\0';
        bytes -= buf_len;
        if(sscanf((char *)web_buffer,"%*s %d %*s\r\n",&ret_code) != 1)
        {
            ceb_cbuf_flush(at_get_cbuf());
            return false;
        }

        // discarding all headers
        ceb_cbuf_find_str(at_get_cbuf(),(uint8_t *)"\r\n\r\n",4,&nb,10000);
        bytes = bytes - nb;
        
        if(ret_code == 204)
        {
            return true;
        }
        else
        {
            ret_code = ret_code / 100;
             if(ret_code == 2)
             {
                if(web_get_payload(bytes))
                    return true;
                else
                    return false;
             }
             else
                return false;
        }
    }
    else
        return false;
}

