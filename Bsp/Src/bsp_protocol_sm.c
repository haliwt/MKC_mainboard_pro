#include "bsp.h"

ProtocolSM sm;
uint8_t calc ;

static uint8_t calc_bcc(const uint8_t *buf, uint8_t len)
{
    uint8_t bcc=0 ,i;
    for (i = 0; i < (len-1); i++){
		bcc ^= buf[i];
	}
    return bcc;
}

void protocol_sm_init(void) 
{
    ProtocolSM tsm;
    tsm.state = SM_WAIT_HEADER;
    tsm.idx = 0;
    tsm.expected_len = 0;
             // 初始化状态机
    tsm.on_frame_ready = frame_parse_respond_handler; // 绑定回调
}
/**
 * @brief  :  状态机输入函数
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
bool protocol_sm_input(const uint8_t *data,uint8_t data_length) 
{
    
   
	
	switch (sm.state) {
    case SM_WAIT_HEADER: //0x00 --> 0xA5 display board
        if (data[0]== FRAME_HEADER) {
            sm.idx = 1;
            sm.state = SM_WAIT_FIXED;
			//printf("sm->state=0 ! \r\n");
        }
        else{
           return  false;
        }
        break;

    case SM_WAIT_FIXED: //0x01--"0x02" display board 
        if (data[1] == DEVICE_ID) {
           
           sm.state = SM_WAIT_CMD_NOTICE;
           sm.idx = 2;
		  // printf("sm->state=1 ! \r\n");
            
        }
        else{
           sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;  
        }
        break;

    case SM_WAIT_CMD_NOTICE:
       sm.cmd_notice =data[2];
       sm.state = SM_WAIT_FUN_JUDGE;
      sm.idx = 3;
	   //printf("sm->state=2 ! \r\n");
            
    break;

    case SM_WAIT_FUN_JUDGE:
       sm.cmd_fun_code =data[3];
       if(sm.cmd_fun_code == FUNC_DATA){
          sm.state = SM_WAIT_DATA_LENGHT;
          sm.idx = 4;
		  
       }
       else{
           sm.cmd_execute_code =0;
           sm.state = SM_WAIT_CMD_TAIL;
           sm.idx = 4;
       }

    break;

    //command notice 
    case SM_WAIT_CMD_TAIL:
        if (data[4] == FRAME_TAIL) {
           
           sm.state = SM_WAIT_CMD_BCC;
           sm.idx = 5;
        }
        else{
           sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;    
        }


    break;

    case SM_WAIT_CMD_BCC:
       sm.bcc_data = data[5];
 
      calc =  calc_bcc(data, 5);
      if(sm.bcc_data == calc){
        sm.idx = 0;
        sm.data_counter=0;
        sm.state = SM_WAIT_HEADER;    
        return true;

      }

    break;

    //data length 
    case SM_WAIT_DATA_LENGHT:
      sm.data_length =data[4];
      sm.state = SM_WAIT_DATA_ONE;
      sm.idx = 5;


    break;

    case SM_WAIT_DATA_ONE:
      sm.data_buf[sm.data_counter]=data[5];
      sm.data_counter++;
      if(sm.data_counter == sm.data_length){
        sm.state = SM_WAIT_TAIL;
        sm.idx = 6;
      }
      else{

        sm.state = SM_WAIT_DATA_TWO;
        sm.idx = 6;

      }
       
    break;

    case SM_WAIT_DATA_TWO:
      sm.data_buf[sm.data_counter]=data[6];
      sm.data_counter++;
      if(sm.data_counter == sm.data_length){
        sm.state = SM_WAIT_TAIL;
        sm.idx = 7;
      }
      else{
        sm.state = SM_WAIT_DATA_THREE;
        sm.idx = 7;
      }
       
    break;

    case SM_WAIT_DATA_THREE:
      sm.data_buf[sm.data_counter]=data[7];
      sm.data_counter++;
      if(sm.data_counter == sm.data_length){
        sm.state = SM_WAIT_TAIL;
        sm.idx = 8;
      }
      else{
        sm.state = SM_WAIT_DATA_FOUR;
        sm.idx = 8;
      }
       
    break;

    case SM_WAIT_TAIL:
      
       if (data[sm.idx] == FRAME_TAIL) {
           
           sm.state = SM_WAIT_BCC;
           sm.idx = sm.idx + 1;//sm->idx + 1;
		  // sm->idx++;
        }
        else{
           sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;    
        }
        break;

    case SM_WAIT_BCC:
       sm.bcc_data = data[sm.idx] ;
 
      calc =  calc_bcc(data, sm.idx);
      if(sm.bcc_data == calc){
        sm.idx = 0;
        sm.data_counter=0;
        sm.state = SM_WAIT_HEADER;    
        return true;

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
void frame_parse_respond_handler(ProtocolSM sm)
{
    // sm->buf 里是完整帧数据，长度是 sm->idx
	uint8_t i;
    printf("frem.length=%d \r\n", sm.idx);

    // 例如：打印十六进制
    for (i = 0; i < sm.idx; i++) {
        printf("%02X ", frame_buf[i]);
    }
    printf("\n");

    // TODO: 在这里做协议解析、业务处理
}



