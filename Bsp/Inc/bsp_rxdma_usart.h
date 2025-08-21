#ifndef __BSP_RXDMA_USART_H
#define __BSP_RXDMA_USART_H
//#include "at32f4xx.h"
#include "at32f425.h"

void usart1_irq_callback_process_rx(void);

void usart1_dma_rx_handler(void);


#endif 
