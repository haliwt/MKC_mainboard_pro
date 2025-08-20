#include "bsp.h"



static volatile uint8_t dma_last_pos = 0; // 上次处理结束位置

// 上层直接处理新数据的回调函数（零拷贝）
static void app_process_rx_data(const uint8_t *data, uint8_t len)
{
    #if 1
    uint8_t i;
	// 这里直接操作 data[len]，不需要 memcpy
    // 例：简单回显
    for (i = 0; i < len; i++) {
        while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
        usart_data_transmit(USART1, data[i]);
        
    }
    #else 
      usart1_dma_send(data, len); // 直接使用 DMA 发送

    #endif 
}

// 处理新数据（零拷贝核心）
void usart1_irq_callback_process_rx(void)
{
    uint16_t pos = RX_BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL1); // 当前DMA写入位置

    if (pos != dma_last_pos) {
        if (pos > dma_last_pos) {
            // 数据在连续内存区
            app_process_rx_data((const uint8_t *)&dma_rx_buf[dma_last_pos], pos - dma_last_pos);
        } else {
            // 数据回绕，分两段处理
            app_process_rx_data((const uint8_t*)&dma_rx_buf[dma_last_pos],(RX_BUFFER_SIZE - dma_last_pos));
            if (pos > 0) {
                app_process_rx_data((const uint8_t *)&dma_rx_buf[0], pos);
            }
        }
        dma_last_pos = pos;
    }
}


