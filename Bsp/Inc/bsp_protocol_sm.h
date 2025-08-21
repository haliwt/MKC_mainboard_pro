#ifndef __BSP_PROTOCOL_SM_H
#define __BSP_PROTOCOL_SM_H
#include "at32f425.h"



#define FRAME_HEADER 0xA5
#define DEVICE_ID    0x02
#define FUNC_DATA    0x0F
#define FRAME_TAIL   0xFE
#define MAX_DATA_LEN 20

typedef enum {
    SM_WAIT_HEADER,
    SM_WAIT_FIXED,
    SM_WAIT_DATA,
    SM_WAIT_TAIL,
    SM_WAIT_BCC
} ProtocolState;

typedef struct ProtocolSM_TYPE{ //SM -state machine
    ProtocolState state;
    uint8_t buf[ MAX_DATA_LEN]; // 头+ID+cmd+func+data+尾/BCC
    uint8_t idx;
    void (*on_frame_ready)(struct ProtocolSM_TYPE *sm); // 可选回调函数指针
    uint8_t expected_len;
} ProtocolSM;

void protocol_sm_init(ProtocolSM *sm);
bool protocol_sm_input(ProtocolSM *sm, uint8_t byte);

void frame_parse_respond_handler(ProtocolSM *sm);

#endif 

