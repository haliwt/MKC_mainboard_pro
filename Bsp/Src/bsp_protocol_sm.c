#include "bsp.h"


static uint8_t calc_bcc(const uint8_t *buf, uint8_t len)
{
    uint8_t bcc = 0,i;
    for (i = 0; i < len; i++) bcc ^= buf[i];
    return bcc;
}

void protocol_sm_init(ProtocolSM *sm) 
{
    sm->state = SM_WAIT_HEADER;
    sm->idx = 0;
    sm->expected_len = 0;
             // 初始化状态机
    sm->on_frame_ready = frame_parse_respond_handler; // 绑定回调
}
/**
 * @brief  :  状态机输入函数
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
bool protocol_sm_input(ProtocolSM *sm, uint8_t byte) 
{
    uint8_t calc ;
	
	switch (sm->state) {
    case SM_WAIT_HEADER:
        if (byte == FRAME_HEADER) {
            sm->buf[0] = byte;
            sm->idx = 1;
            sm->state = SM_WAIT_FIXED;
        }
        break;

    case SM_WAIT_FIXED:
        sm->buf[sm->idx++] = byte;
        if (sm->idx == 4) { // 已收 header, ID, cmd, func
            if (sm->buf[1] != DEVICE_ID) {
                sm->state = SM_WAIT_HEADER; // ID不符，重来
                sm->idx = 0;
                break;
            }
            if (sm->buf[3] == FUNC_DATA) {
                sm->state = SM_WAIT_DATA;
            } else {
                sm->state = SM_WAIT_TAIL;
            }
        }
        break;

    case SM_WAIT_DATA:
        sm->buf[sm->idx++] = byte;
        if (sm->idx >= MAX_DATA_LEN + 4) { // 防溢出
            sm->state = SM_WAIT_HEADER;
            sm->idx = 0;
        }
        // 数据帧长度未知，这里可加协议内长度字段判断
        // 简化：假设上层知道何时结束，直接等到 BCC
        // if (sm->idx >= 5 && /*条件判断结束*/) {
        //     sm->state = SM_WAIT_BCC;
        // }
        break;

    case SM_WAIT_TAIL:
        sm->buf[sm->idx++] = byte;
        if (byte == FRAME_TAIL) {
            sm->state = SM_WAIT_BCC;
        } else {
            sm->state = SM_WAIT_HEADER;
            sm->idx = 0;
        }
        break;

    case SM_WAIT_BCC:
        sm->buf[sm->idx++] = byte;
        calc = (sm->buf[3] == FUNC_DATA)
            ? calc_bcc(sm->buf, sm->idx - 1)
            : calc_bcc(sm->buf, 4);
        if (calc == byte) {
            // ✅ 一帧完成
            sm->state = SM_WAIT_HEADER;
            sm->idx = 0;
            return true;
        } else {
            // 校验失败
            sm->state = SM_WAIT_HEADER;
            sm->idx = 0;
        }
        break;
    }
    return false;
}

/**
 * @brief  : 回调函数
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
void frame_parse_respond_handler(ProtocolSM *sm)
{
    // sm->buf 里是完整帧数据，长度是 sm->idx
	uint8_t i;
    printf("frem.length=%d \r\n", sm->idx);

    // 例如：打印十六进制
    for (i = 0; i < sm->idx; i++) {
        printf("%02X ", sm->buf[i]);
    }
    printf("\n");

    // TODO: 在这里做协议解析、业务处理
}



