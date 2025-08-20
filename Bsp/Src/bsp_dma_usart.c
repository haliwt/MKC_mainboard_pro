#include "bsp.h"

#define SEG_Q_SIZE 8

#define FRAME_MAX_LEN  20

volatile uint8_t dma_rx_buf[RX_BUFFER_SIZE];



typedef struct {
    uint8_t pos; // 在DMA环形缓冲区中的起始位置
    uint8_t len; // 段长度
} seg_t;


uint8_t  g_frame[FRAME_MAX_LEN];
static uint8_t g_frame_len = 0;
static volatile seg_t seg_q[SEG_Q_SIZE];
static volatile uint8_t seg_q_head = 0, seg_q_tail = 0;
static volatile uint8_t rx_last = 0;

static void rx_process_chunk(const uint8_t *data, uint16_t len);

/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None
 * @retval  None
 */
static void push_seg(uint8_t pos,uint8_t len)
{
    uint8_t next = (seg_q_head + 1) % SEG_Q_SIZE;
    if (next == seg_q_tail) {
        // 队列满：覆盖最旧的一段（丢弃最老记录，保留新数据）
        seg_q_tail = (seg_q_tail + 1) % SEG_Q_SIZE;
    }
    seg_q[seg_q_head].pos = pos;
    seg_q[seg_q_head].len = len;
    seg_q_head = next;
}

/**
 * @brief  读取DMA1 CHANNEL_1 剩下数组的空间位置
 * @note 该函数在USART1接收完成时被调用
 * @retval None 
 * @parameter None
 * @details 该函数会将接收到的数据段推入环形缓冲区
 */
static uint8_t dma_rx_cur_index(void)
{
    uint8_t remain = DMA1_CHANNEL1->dtcnt; // AT32F425 DTCNT寄存器
    return (RX_BUFFER_SIZE - remain) % RX_BUFFER_SIZE;
}
/**
 * @brief USART1 DMA接收完成回调处理函数
 * @note 该函数在USART1接收完成时被调用
 * @retval None 
 * @parameter None
 * @details 该函数会将接收到的数据段推入环形缓冲区
 */
void usart1_irq_callback_handler(void)
{
    uint8_t cur = dma_rx_cur_index(); // 剩下没有写入的数据空间,获取当前DMA接收的索引位置
    uint8_t last = rx_last;

    if (cur != last) {  // 1️⃣ 有新数据到达
        if (cur > last) {
            // 2️⃣ 普通情况：写指针没回绕
            push_seg(last, cur - last);
        } else {
            // 3️⃣ 回绕情况：写指针绕过缓冲区尾部，从头写
            push_seg(last, RX_BUFFER_SIZE - last); // 先推尾部剩余的数据段
            if (cur){
                push_seg(0, cur);                 // 再推从头到cur的段
                }
        }
        // 4️⃣ 记录当前位置，方便下次比较
        rx_last = cur;
    }
}




/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None
 * @retval  None
 */
static void rx_process_chunk(const uint8_t *data, uint16_t len)
{
    if (!len) return;

    // 限长防护
    if (len > FRAME_MAX_LEN) {
        len = FRAME_MAX_LEN;
    }

    // 覆盖模式：直接从 g_frame[0] 开始拷贝本帧
    memcpy(g_frame, data, len);

    // 记录本帧长度
    g_frame_len   = len;
   // g_frame_ready = 1;     // 标记本帧已就绪（可在主循环读取）
    memset(g_frame + len, 0, FRAME_MAX_LEN - len); // 清理剩余部分
}

/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None
 * @retval  None
 */
void usart1_dma_rx_process(void)
{
    while (seg_q_tail != seg_q_head) {
        uint16_t pos = seg_q[seg_q_tail].pos;
        uint16_t len = seg_q[seg_q_tail].len;

        // 在这里做memcpy / 解析 / 覆盖模式拼帧
        rx_process_chunk((const uint8_t*)&dma_rx_buf[pos], len);

        seg_q_tail = (seg_q_tail + 1) % SEG_Q_SIZE;
    }
}

