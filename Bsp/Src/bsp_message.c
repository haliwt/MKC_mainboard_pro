#include "bsp.h"

#define FRAME_HEADER 0xA5      //display board send data to main board
#define DEVICE_ID    0x02
#define CMD_SWITCH   0x01
#define FUNC_DATA    0x0F
#define FRAME_TAIL   0xFE
#define MAX_DATA_LEN 20

typedef struct {
    uint8_t cmd;
    uint8_t func;
    uint8_t data[MAX_DATA_LEN];
    uint8_t data_len;
    bool    is_data_frame;
} ParsedFrame;
/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   receive data buffer, data of length, struct ParsedFrame to fill
 * @retval  true if frame is valid, false otherwise
 */
bool parse_protocol_frame(const uint8_t *buf, uint16_t len, ParsedFrame *frame)
{
    
    uint8_t bcc ,calc_bcc,i;
    if (len < 5 || buf[0] != FRAME_HEADER || buf[1] != DEVICE_ID) {
        return false; // 帧头或设备ID错误
    }

    frame->cmd  = buf[2];
    frame->func = buf[3];

    if (frame->func == FUNC_DATA) {
        // 数据帧
        frame->is_data_frame = true;

        if (len < 6) return false; // 至少要有一个数据字节

        frame->data_len = len - 4; // 从第4字节开始是数据
        if (frame->data_len > MAX_DATA_LEN) return false;

         memcpy(frame->data, &buf[4], frame->data_len);

    } else {
        // 命令帧
        frame->is_data_frame = false;

        if (buf[4] != FRAME_TAIL) {
            return false; // 帧尾错误
        }

        bcc = buf[5];
        calc_bcc = 0;
        for (i = 0; i < 5; i++) {
            calc_bcc ^= buf[i];
        }

        if (bcc != calc_bcc) {
            return false; // 校验失败
        }

        frame->data_len = 0;
    }

    return true;
}

/**
 * @brief  :  处理解析帧函数
 * @note    
 * @param   None
 * @retval  None
 */
void handle_frame(const uint8_t *rx_buf, uint16_t rx_len)
{
    #if 0
	uint8_t i;
	ParsedFrame frame;
    if (parse_protocol_frame(rx_buf, rx_len, &frame)) {
        if (frame.is_data_frame) {
            printf("数据帧，功能码: 0x%02X，长度: %d\r\n", frame.func, frame.data_len);
            for (i = 0; i < frame.data_len; i++) {
                printf("数据[%d]: 0x%02X\r\n", i, frame.data[i]);
            }
        } else {
            printf("命令帧，功能码: 0x%02X，命令: %s\r\n",
                   frame.func,
                   (frame.func == 0x01) ? "开机" :
                   (frame.func == 0x00) ? "关机" : "未知");
        }
    } else {
        printf("帧解析失败\r\n");
    }
	#endif 
}
