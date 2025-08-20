#include "bsp.h"

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

    // 3. 清标志
    dma_flag_clear(DMA1_FDT2_FLAG | DMA1_HDT2_FLAG | DMA1_DTERR2_FLAG);

    // 4. 开 USART1 DMA TX
    dma_flexible_config(DMA1, FLEX_CHANNEL2, DMA_FLEXIBLE_UART1_TX);

    usart_dma_transmitter_enable(USART1, TRUE);

    // 5. 使能 DMA 通道
    dma_channel_enable(DMA1_CHANNEL2, TRUE);

//      // 关闭通道以便重新配置
//     dma_channel_enable(DMA1_CHANNEL2, FALSE);

//      /* 拷贝数据到 TX 缓冲 */
//      memcpy(dma_tx_buf, data, len);

//     // 设置内存地址和传输长度
//    // dma_memory_address_set(DMA1_CHANNEL2, (uint32_t)data);
//    DMA1_CHANNEL2->maddr = (uint32_t)dma_tx_buf;      // 内存地址

//     dma_data_number_set(DMA1_CHANNEL2, len);

//     // 清除可能的旧标志
//     dma_flag_clear(DMA1_FDT2_FLAG | DMA1_HDT2_FLAG | DMA1_DTERR2_FLAG);

//     // 开 USART1 DMA 发送
//     usart_dma_transmitter_enable(USART1, TRUE);

//     // 重新打开通道
//     dma_channel_enable(DMA1_CHANNEL2, TRUE);
//     /* 确保上一次 DMA 发送完成 */
//    // while (dma_channel_enable_status_get(DMA1_CHANNEL2) == SET);
//       // 等待DMA完成（简单轮询）
//   //  while (DMA1_CHANNEL2->ctrl & DMA_CHXCTRL_CHEN);
   
//     /* 拷贝数据到 TX 缓冲 */
//     memcpy(dma_tx_buf, data, len);

//     /* 设置长度 */
//     dma_data_number_set(DMA1_CHANNEL2, len);

//       /* 设置DMA传输参数 */
//    // DMA1_CHANNEL2->cnt = len;                          // 设置传输数据量
//     DMA1_CHANNEL2->maddr = (uint32_t)dma_tx_buf;         // 设置内存地址

//     /* 重新设置内存地址（如果缓冲可变） */
//     //dma_memory_base_addr_set(DMA1_CHANNEL2, (uint32_t)dma_tx_buf);
//     usart_dma_transmitter_enable(USART1,TRUE);
//     /* 启动 DMA 发送 */
//     dma_channel_enable(DMA1_CHANNEL2, TRUE);

//    // usart_dma_transmitter_enable(usart_type* usart_x, confirm_state new_state);
}
