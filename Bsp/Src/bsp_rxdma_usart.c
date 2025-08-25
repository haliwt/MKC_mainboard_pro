#include "bsp.h"



uint8_t frame_buf[FRAME_MAX_LEN ];


uint8_t counter_flag;
uint8_t pos, rx_len,rx_pos, rx_last,last_pos; 
volatile uint8_t rx_ready = false;

volatile uint8_t dma_last_pos = 0; // 上次处理结束位置


// 上层直接处理新数据的回调函数（零拷贝）
void usart1_dma_rx_handler(void)
{
   #if 0
    uint8_t i;
	// 这里直接操作 data[len]，不需要 memcpy
    // 例：简单回显
    for (i = 0; i < len; i++) {
        while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
        usart_data_transmit(USART1, data[i]);
        
    }
    #else
    uint8_t first_len;
        
        if(rx_ready ==1){
            rx_ready=0;
        if (rx_pos >= last_pos) {
            memcpy(frame_buf,(const uint8_t *) &dma_rx_buf[last_pos], rx_len);
           
        } else {
            first_len = RX_BUFFER_SIZE - last_pos;
            memcpy(frame_buf, (const uint8_t *) &dma_rx_buf[last_pos], first_len);
            memcpy(&frame_buf[first_len], (const uint8_t *) &dma_rx_buf[0], rx_pos);
           
        }

      //  parse_frame(frame_buf, rx_len);
        last_pos = rx_pos;
        memset(frame_buf + rx_len, 0, MAX_DATA_LEN - rx_len); // 清理剩余部分
       
		//protocol_sm_feed(&sm,); // 状态机解析
        // protocol_sm_feed(sm,frame_buf, rx_len);
        if(rx_len==6){
           protocol_sm_cmd_input(frame_buf,rx_len);
        }
        else if(rx_len==7){
           protocol_sm_ack_input(frame_buf,rx_len);
        }
        else if(rx_len > 7){

             protocol_sm_data_input(frame_buf,rx_len);
        }
        counter_flag++;
    }

    #endif
  
}




/**
 * @brief  : 中断函数调用此函数
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None                
 * @retval  None
 */
void usart1_irq_callback_process_rx(void)
{
  #if 0
	pos = RX_BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL1); // 当前DMA写入位置

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

   #else
    
    pos = RX_BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL1); // 当前DMA写入位置
    rx_len = (pos >= last_pos) ? (pos - last_pos) : (RX_BUFFER_SIZE - last_pos + pos);
    rx_ready = true;
    rx_pos = pos;
    vTaskNotic_Decoder_irq_handler();


   #endif 
}


