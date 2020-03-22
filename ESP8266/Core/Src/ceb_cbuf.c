#include <stdbool.h>
#include <stdint.h>
#include "ceb_cbuf.h"

#define CEB_CBUF_INC(v,mv)   ((((v) + 1) >= (mv)) ? 0 : (v) + 1)

cbuf_status_t ceb_cbuf_init(ceb_cbuf_t *cb, uint8_t *area, uint16_t size)
{
	cb->buffer = area;
	cb->size = size;
	cb->prod = cb->cons = 0;

	return CEB_CBUF_OK;
}

uint16_t ceb_cbuf_bytes_available(ceb_cbuf_t *cb)
{
	if(cb->prod >= cb->cons)
		return cb->prod - cb->cons;
	else
		return cb->prod + (cb->size - cb->cons);
}

cbuf_status_t ceb_cbuf_flush(ceb_cbuf_t *cb)
{
	cb->prod = cb->cons = 0;

	return CEB_CBUF_OK;
}

cbuf_status_t ceb_cbuf_get(ceb_cbuf_t *cb, uint8_t *c)
{
	if(cb->cons == cb->prod)
		return CEB_CBUF_EMPTY;

	*c = cb->buffer[cb->cons];
	cb->cons = CEB_CBUF_INC(cb->cons,cb->size);

	return CEB_CBUF_OK;
}

cbuf_status_t ceb_cbuf_put(ceb_cbuf_t *cb, uint8_t c)
{
	uint16_t next_prod = CEB_CBUF_INC(cb->prod,cb->size);

	if(next_prod == cb->cons)
		return CEB_CBUF_FULL;

	cb->buffer[cb->prod] = c;
	cb->prod = next_prod;

	return CEB_CBUF_OK;
}

#if 1
int16_t ceb_cbuf_find_str(ceb_cbuf_t *cb, uint8_t *str, uint16_t len, uint16_t *nb, uint32_t tmrout_ms)
{
	uint16_t n_match = 0;
	uint8_t c;
	uint32_t tmr = hw_time_get();

	*nb = 0;
	do
	{
		if(ceb_cbuf_get(cb,&c) == CEB_CBUF_OK)
		{
			*nb = *nb + 1;
			if(str[n_match] == c)
				n_match++;
			else
				n_match = 0;

			if(n_match >= len)
				return 0;		
		}
	} while (hw_time_elapsed(tmr,hw_time_get()) < tmrout_ms);

	return -1;
}

int16_t ceb_cbuf_find_multi_str(ceb_cbuf_t *cb, ceb_cbuf_str_t *str_list, uint16_t len_list, uint32_t tmrout_ms)
{
	uint16_t n;
	uint8_t c;
	uint32_t tmr = hw_time_get();

	for(n = 0; n < len_list ; n++)
		str_list[n].n_match = 0;

	do
	{
		if(ceb_cbuf_get(cb,&c) == CEB_CBUF_OK)
		{
			for(n = 0; n < len_list ; n++)
			{
				if(str_list[n].str[str_list[n].n_match] == c)
					str_list[n].n_match++;
				else
					str_list[n].n_match = 0;

				if(str_list[n].n_match >= str_list[n].len)
					return n;
			}
		}
	} while (hw_time_elapsed(tmr,hw_time_get()) < tmrout_ms);

	return -1;	
}

int16_t ceb_cbuf_get_str_until_find(ceb_cbuf_t *cb, uint8_t *buf, uint16_t *buf_len,
                                     uint8_t *str, uint16_t len, uint32_t tmrout_ms)
{
	uint16_t n_match = 0;
	uint8_t c;
	uint32_t tmr = hw_time_get();
	uint16_t p = 0;

	if(*buf_len == 0)
		return -1;

	do
	{
		if(ceb_cbuf_get(cb,&c) == CEB_CBUF_OK)
		{
			buf[p++] = c;
			if(p >= *buf_len)
				return 1;
			
			if(str[n_match] == c)
				n_match++;
			else
				n_match = 0;

			if(n_match >= len)
			{
				*buf_len = p;
				return 0;
			}
		}
	} while (hw_time_elapsed(tmr,hw_time_get()) < tmrout_ms);

	*buf_len = p;
	return -1;
}

cbuf_status_t ceb_cbuf_get_tmrout(ceb_cbuf_t *cb, uint8_t *c, uint32_t tmrout_ms)
{
	uint32_t tmr = hw_time_get();
	
	while (hw_time_elapsed(tmr,hw_time_get()) < tmrout_ms)
	{
		if(cb->cons == cb->prod)
			continue;
		else
			break;
	}
	
	if(cb->prod == cb->cons)
		return CEB_CBUF_EMPTY;

	*c = cb->buffer[cb->cons];
	cb->cons = CEB_CBUF_INC(cb->cons,cb->size);

	return CEB_CBUF_OK;
}

int16_t ceb_cbuf_get_str(ceb_cbuf_t *cb, uint8_t *buf, uint16_t *buf_len, uint32_t tmrout_ms)
{
	uint8_t c;
	uint32_t tmr = hw_time_get();
	uint16_t p = 0;

	if(*buf_len == 0)
		return -1;

	do
	{
		if(ceb_cbuf_get(cb,&c) == CEB_CBUF_OK)
		{
			buf[p++] = c;
			if(p >= *buf_len)
				return 1;			
		}
	} while (hw_time_elapsed(tmr,hw_time_get()) < tmrout_ms);

	*buf_len = p;
	return -1;
}

cbuf_status_t ceb_cbuf_get_beg(ceb_cbuf_t *cb, uint8_t *c, uint16_t *cons)
{
	if(*cons == cb->prod)
		return CEB_CBUF_EMPTY;

	*c = cb->buffer[*cons];
	*cons = CEB_CBUF_INC(*cons,cb->size);

	return CEB_CBUF_OK;
}

cbuf_status_t ceb_cbuf_get_end(ceb_cbuf_t *cb,  uint16_t *cons)
{
	cb->cons = *cons;

	return CEB_CBUF_OK;
}

int16_t ceb_cbuf_get_str_on_buffer_beg(ceb_cbuf_t *cb, uint16_t *cons, uint8_t **buf, uint16_t *buf_len, uint32_t tmrout_ms)
{
	uint8_t c;
	uint32_t tmr = hw_time_get();
	uint16_t p = 0;
	*cons = cb->cons;

	if(buf_len == 0)
	{
		*buf_len = 0;
		return -1;
	}

	// starting position
	*buf = &cb->buffer[*cons];

	do
	{
		if(ceb_cbuf_get_beg(cb,&c,cons) == CEB_CBUF_OK)
		{
			if(++p >= *buf_len)
				return 1;			
		}
	} while (hw_time_elapsed(tmr,hw_time_get()) < tmrout_ms);

	*buf_len = p;
	return -1;
}

int16_t ceb_cbuf_get_str_on_buffer_end(ceb_cbuf_t *cb, uint16_t *cons)
{
	return ceb_cbuf_get_end(cb,cons);
}

#endif

#if 0
ceb_cbuf_t tst;
uint8_t tst_area[AT_CBUF_MAX];
cbuf_str_t list[3];

void hw_cbuf_test(void)
{
	ceb_cbuf_init(&tst,tst_area,AT_CBUF_MAX);

	ceb_cbuf_put(&tst,'a');
	ceb_cbuf_put(&tst,'b');
	ceb_cbuf_put(&tst,'c');
	ceb_cbuf_put(&tst,'O');
	ceb_cbuf_put(&tst,'K');
	ceb_cbuf_put(&tst,'\r');
	ceb_cbuf_put(&tst,'\n');
	ceb_cbuf_put(&tst,'e');
	ceb_cbuf_put(&tst,'f');
	ceb_cbuf_put(&tst,'g');

	// cbuf_find_str(&tst,(uint8_t*)"OK1\r\n",4,2000);

	list[0].str = (uint8_t *) "OK1\r\n";
	list[0].len = 5;
	list[1].str = (uint8_t *) "OK\r\n";
	list[1].len = 4;

	cbuf_find_multi_str(&tst,list,2,2000);
	
}


//static at_status_t cbuf_find_multi_str(uint8_t *buffer, uint16_t len, cbuf_str_t *str_list, uint16_t len_list)
//{
//	uint16_t n,m;
//	uint8_t c;
//	at_status_t st = AT_INVALID_FRAME;
//
//	for(n = 0; n < len_list ; n++)
//		str_list[n].n_match = 0;
//
//	for(m = 0 ; m < len ; m++)
//	{
//		c = buffer[m];
//
//		for(n = 0; n < len_list ; n++)
//		{
//			if(str_list[n].str[str_list[n].n_match] == c)
//				str_list[n].n_match++;
//			else
//				str_list[n].n_match = 0;
//
//			if(str_list[n].n_match >= str_list[n].len)
//				return str_list[n].status;
//		}
//	}
//
//	return st;
//}

#endif

