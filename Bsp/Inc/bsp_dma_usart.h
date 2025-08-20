#ifndef __BSP_DAM_USART_H
#define __BSP_DAM_USART_H
#include "at32f425.h"

#define RX_BUFFER_SIZE  20

volatile extern uint8_t dma_rx_buf[RX_BUFFER_SIZE];

void usart1_irq_callback_handler(void);

void usart1_dma_rx_process(void);
#endif 

