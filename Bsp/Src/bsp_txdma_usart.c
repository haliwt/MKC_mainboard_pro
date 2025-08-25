#include "bsp.h"

//static uint8_t tx_bufA[RX_BUFFER_SIZE];
//static uint8_t tx_bufB[RX_BUFFER_SIZE];
//static uint8_t *tx_fill = tx_bufA;  // 当前用于填充
//static uint8_t *tx_live = NULL;     // 正在 DMA 发送的缓冲

uint8_t dma_tx_buf[RX_BUFFER_SIZE];
void usart1_dma_send(const uint8_t *data, uint16_t len)
{

    dma_init_type dma_init_struct;
    
  // 1. 关通道，防止配置中途触发
    dma_channel_enable(DMA1_CHANNEL2, FALSE);

    // 2. 配置 DMA 通道3
    dma_default_para_init(&dma_init_struct);
    dma_init_struct.buffer_size          = len;
    dma_init_struct.direction            = DMA_DIR_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_base_addr     = (uint32_t)data; 
    dma_init_struct.memory_data_width    = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.memory_inc_enable    = TRUE;
    dma_init_struct.peripheral_base_addr = (uint32_t)&USART1->dt;
    dma_init_struct.peripheral_data_width= DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.peripheral_inc_enable= FALSE;
    dma_init_struct.priority             = DMA_PRIORITY_MEDIUM;
    dma_init_struct.loop_mode_enable     = FALSE; // 单次发送
    dma_init(DMA1_CHANNEL2, &dma_init_struct);



    // 4. 开 USART1 DMA TX
    dma_flexible_config(DMA1, FLEX_CHANNEL2, DMA_FLEXIBLE_UART1_TX);
   
     // 5. 使能 DMA 通道
    dma_channel_enable(DMA1_CHANNEL2, TRUE);

    usart_dma_transmitter_enable(USART1, TRUE);

    }
