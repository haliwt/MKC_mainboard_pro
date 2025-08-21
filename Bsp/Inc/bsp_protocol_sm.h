#ifndef __BSP_PROTOCOL_SM_H
#define __BSP_PROTOCOL_SM_H
#include "at32f425.h"



#define FRAME_HEADER 0xA5
#define DEVICE_ID    0x02
#define FUNC_DATA    0x0F
#define FRAME_TAIL   0xFE
#define MAX_DATA_LEN 20

typedef enum {
    SM_WAIT_HEADER=0,
    SM_WAIT_FIXED=1,
    SM_WAIT_CMD_NOTICE=2,
    SM_WAIT_FUN_JUDGE=3,
    SM_WAIT_DATA_LENGHT=4,
    SM_WAIT_DATA_ONE =5,
    SM_WAIT_DATA_TWO =6,
    SM_WAIT_DATA_THREE= 7 ,
    SM_WAIT_DATA_FOUR =8,
    SM_WAIT_CMD_TAIL=9,
    SM_WAIT_CMD_BCC = 0x0A,
    SM_WAIT_TAIL=0x0B,
    SM_WAIT_BCC=0X0C
} ProtocolState;

typedef struct ProtocolSM_TYPE{ //SM -state machine
    ProtocolState state;
    uint8_t buf[ MAX_DATA_LEN]; // 头+ID+cmd+func+data+尾/BCC
    uint8_t data_buf[4];
    uint8_t idx;
    void (*on_frame_ready)(struct ProtocolSM_TYPE *sm); // 可选回调函数指针
    uint8_t expected_len;
    uint8_t cmd_notice;
    uint8_t cmd_fun_code;
    uint8_t cmd_execute_code;
    uint8_t  bcc_data;
    uint8_t   data_length;
    uint8_t  data_counter;
} ProtocolSM;

void protocol_sm_init(ProtocolSM *sm);
bool protocol_sm_input(ProtocolSM *sm, const uint8_t *byte);

void frame_parse_respond_handler(ProtocolSM *sm);

#endif 

