#ifndef __BSP_TXDMA_USART_H
#define __BSP_TXDMA_USART_H
#include "at32f425.h"

extern uint8_t dma_tx_buf[RX_BUFFER_SIZE];

void usart1_dma_send(const uint8_t *data, uint16_t len);


#endif 
