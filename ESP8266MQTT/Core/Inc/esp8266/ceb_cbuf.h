/**

@file
@defgroup CBUF CBUF
@brief Funções para uso de buffer circulares.
@{

*/
#pragma once

/**
@brief Valores de retorno das funções de buffer circular.
*/
typedef enum __attribute__((__packed__)) cbuf_status_s
{
    CEB_CBUF_OK = 0, /**< Operação realizada com sucesso */
    CEB_CBUF_FULL,   /**< Buffer circular cheio */
    CEB_CBUF_EMPTY,  /**< Buffer circular vazio */
	CEB_CBUF_TMROUT, /**< Timeout na operação */
} cbuf_status_t;

/**
@brief Estrutura de controle do buffer circular.
*/
typedef struct __attribute__((__packed__)) ceb_cbuf_s
{
	volatile uint16_t prod; /**< Indicador da posição de produção no buffer circular */
	volatile uint16_t cons; /**< Indicador da posição de consumo no buffer circular */
	uint16_t size;          /**< Tamanho total do buffer circular */
    uint8_t *buffer;        /**< Ponteiro para a área de dados do buffer circular (alocado pelo usuário) */
} ceb_cbuf_t;

typedef struct __attribute__((__packed__)) ceb_cbuf_str_e
{
	uint8_t *str;
	uint16_t len;
	uint16_t n_match;
} ceb_cbuf_str_t;

/**
@brief Declara e instancia um buffer circular.
Pode ser colocado no escopo global do arquivo ou mesmo dentro de uma função (alocação feita na área de variáveis globais).
Deve ser realizada uma proteção caso exista concorrência no uso do produto ou do consumidor do buffer.
@code

#define BUFFER_SIZE 128

CEB_CBUF_DECLARE(cb,BUFFER_SIZE);
uint8_t c = 0xff;

if(ceb_cbuf_put(&cb,c) == CEB_CBUF_OK)
{
    // valor inserido no buffer
}
if(ceb_cbuf_get(&cb,&c) == CEB_CBUF_OK)
{
    // valor removido do buffer e colocado em c
}

@endcode

*/
#define CEB_CBUF_DECLARE(name,_size)            \
    static uint8_t name##buffer[_size + 1];     \
    static ceb_cbuf_t name = {                  \
        .prod = 0, 								\
        .cons = 0, 								\
        .size = _size+1,      	                \
        .buffer = (uint8_t*) name##buffer,      \
    }
/**
 @brief Retorna a quantidade de bytes disponível para consumo num buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @return quantidade de bytes disponível para consumo
*/
uint16_t ceb_cbuf_bytes_available(ceb_cbuf_t *cb);
/**
 @brief Esvazia um buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @return ver @ref cbuf_status_s
*/
cbuf_status_t ceb_cbuf_flush(ceb_cbuf_t *cb);
/**
 @brief Retira um byte do buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @param[out] c - ponteiro para o destino do dado (previamente alocado).
 @return ver @ref cbuf_status_s
*/
cbuf_status_t ceb_cbuf_get(ceb_cbuf_t *cb, uint8_t *c);
/**
 @brief Reinicializa um buffer circular, caso seja necessário.
 A macro @ref CEB_CBUF_DECLARE já faz esse papel mas essa função pode ser usada para inicialização de forma
 independente da macro.
 @param[in] cb - ponteiro para o buffer circular.
 @param[in] area - buffer previamente alocado que será usado para armazenamento do conteúdo do buffer circular.
 @param[in] size - tamanho da área de dados apontada por @p area.
 @return ver @ref cbuf_status_s
*/
cbuf_status_t ceb_cbuf_init(ceb_cbuf_t *cb, uint8_t *area, uint16_t size);
/**
 @brief Coloca um byte no buffer circular.
 @param[in] cb - ponteiro para o buffer circular.
 @param[in] c - byte a ser adicionado ao buffer circular.
 @return ver @ref cbuf_status_s
*/
cbuf_status_t ceb_cbuf_put(ceb_cbuf_t *cb, uint8_t c);

/**
@}
*/

int16_t ceb_cbuf_find_str(ceb_cbuf_t *cb, uint8_t *str, uint16_t len, uint16_t *nb, uint32_t tmrout_ms);
int16_t ceb_cbuf_find_multi_str(ceb_cbuf_t *cb, ceb_cbuf_str_t *str_list, uint16_t len_list, uint32_t tmrout_ms);
int16_t ceb_cbuf_get_str_until_find(ceb_cbuf_t *cb, uint8_t *buf, uint16_t *buf_len,
                                     uint8_t *str, uint16_t len, uint32_t tmrout_ms);
cbuf_status_t ceb_cbuf_get_tmrout(ceb_cbuf_t *cb, uint8_t *c, uint32_t tmrout_ms);
int16_t ceb_cbuf_get_str(ceb_cbuf_t *cb, uint8_t *buf, uint16_t *buf_len, uint32_t tmrout_ms);
cbuf_status_t ceb_cbuf_get_beg(ceb_cbuf_t *cb, uint8_t *c, uint16_t *cons);
cbuf_status_t ceb_cbuf_get_end(ceb_cbuf_t *cb,  uint16_t *cons);
int16_t ceb_cbuf_get_str_on_buffer_beg(ceb_cbuf_t *cb, uint16_t *cons, uint8_t **buf, uint16_t *buf_len, uint32_t tmrout_ms);
int16_t ceb_cbuf_get_str_on_buffer_end(ceb_cbuf_t *cb, uint16_t *cons);

