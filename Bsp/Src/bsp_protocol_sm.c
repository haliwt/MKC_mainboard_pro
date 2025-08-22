#include "bsp.h"

ProtocolSM sm;
uint8_t calc ;

static void getParseCmd_displayBoard(void);

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
   // ProtocolSM tsm;
   // tsm.state = SM_WAIT_HEADER;
  //  tsm.idx = 0;
   // tsm.expected_len = 0;
             // 初始化状态机
   // tsm.on_frame_ready = frame_parse_respond_handler; // 绑定回调
}


/**
 * @brief  : parse protocol is command  don't data
 * @note    receive data is length more 6 
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
bool protocol_sm_cmd_input(const uint8_t *data,uint8_t data_length) 
{
   
    if(data_length ==6){

     switch(sm.state){
         case SM_WAIT_HEADER: //0x00 --> 0xA5 display board
        if (data[0]== FRAME_HEADER) {
            sm.idx = 1;
            sm.state = SM_WAIT_FIXED;
	
        }
        else{
           return  FALSE;
        }
       

    case SM_WAIT_FIXED: //0x01--"0x02" display board 
        if (data[1] == DEVICE_ID) {
           
           sm.state = SM_WAIT_CMD_NOTICE;
           sm.idx = 2;
            
        }
        else{
           sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;  
            return  FALSE;
        }
      

    case SM_WAIT_CMD_NOTICE:
       sm.cmd_notice =data[2];
       sm.state = SM_WAIT_FUN_JUDGE;
      sm.idx = 3;
	
    case SM_WAIT_FUN_JUDGE:
   
          sm.cmd_fun_code=data[3];
           sm.state = SM_WAIT_CMD_TAIL;
           sm.idx = 4;
       

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
           return FALSE;  
        }


  
    case SM_WAIT_CMD_BCC:
       sm.bcc_data = data[5];
 
      calc =  calc_bcc(data, 5);
      if(sm.bcc_data == calc){
        sm.idx = 0;
        sm.data_counter=0;
        sm.state = SM_WAIT_HEADER;    
        getParseCmd_displayBoard();
        return  TRUE;

      }
      else{
        sm.idx = 0;
        sm.data_counter=0;
        sm.state = SM_WAIT_HEADER;  
         printf("receive data fail !!!\r\n");
        return FALSE;
      }
    break;
    
  }
	 return FALSE ;
  }
  
}
/**
 * @brief  : parse protocol is data don't command 
 * @note    receive data is length more 6 
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
bool protocol_sm_data_input(const uint8_t *data,uint8_t data_length) 
{
	  
	switch(sm.state){
    case SM_WAIT_HEADER: //0x00 --> 0xA5 display board
        if (data[0]== FRAME_HEADER) {
            sm.idx = 1;
            sm.state = SM_WAIT_FIXED;
			//printf("sm->state=0 ! \r\n");
        }
        else{
          sm.idx = 0;
           return  FALSE;
        }
  

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
            return  FALSE;
        }
      

    case SM_WAIT_CMD_NOTICE:
       sm.cmd_notice =data[2];
       sm.state = SM_WAIT_FUN_JUDGE;
      sm.idx = 3;
	  
            
    

    case SM_WAIT_FUN_JUDGE:
       //sm.cmd_fun_code =data[3];
       if(data[3] == FUNC_DATA){
          sm.state = SM_WAIT_DATA_LENGHT;
          sm.idx = 4;
		  
       }
       else{
            sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;  
           return  FALSE;
       }

    
     //data length 
    case SM_WAIT_DATA_LENGHT:
      sm.data_length =data[4];
      sm.state = SM_WAIT_DATA_ONE;
      sm.idx = 5;

    

    case SM_WAIT_DATA_ONE:
      sm.data_buf[sm.data_counter]=data[5];
      sm.data_counter++;
      if(sm.data_counter == sm.data_length){
        sm.state = SM_WAIT_DATA_TWO;
        sm.data_to_tail = SM_WAIT_TAIL ;
        sm.idx = 6;
      }
      else{
        sm.data_to_tail=0;
        sm.state = SM_WAIT_DATA_TWO;
        sm.idx = 6;

      }

    

    
    case SM_WAIT_DATA_TWO:
    
       
    if(sm.data_to_tail==0){
   
      sm.data_buf[sm.data_counter]=data[6];
      sm.data_counter++;
      if(sm.data_counter == sm.data_length){
        sm.state = SM_WAIT_DATA_THREE;
        sm.data_to_tail = SM_WAIT_TAIL ;
        sm.idx = 7;
      }
      else{
        sm.state = SM_WAIT_DATA_THREE;
        sm.idx = 7;
      }
    }
    else{  
      
     if (data[sm.idx] == FRAME_TAIL) {
           
           sm.state = SM_WAIT_DATA_THREE;
          sm.data_to_tail = SM_WAIT_BCC ;
           sm.idx = sm.idx + 1;//sm->idx + 1;
		  // sm->idx++;
        }
        else{
           sm.data_to_tail = 0;
           sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;  
           return FALSE;  
        }
    }

    case  SM_WAIT_DATA_THREE: //7

        if(sm.data_to_tail == SM_WAIT_TAIL){
        if (data[sm.idx] == FRAME_TAIL) {
           
           sm.state = SM_WAIT_BCC;
           sm.data_to_tail = SM_WAIT_BCC ;
           sm.idx = sm.idx + 1;//sm->idx + 1;
		  // sm->idx++;
        }
        }
        else if(sm.data_to_tail==0){
           sm.data_to_tail = 0;
           sm.idx = 0;
           sm.data_counter=0;
           sm.state = SM_WAIT_HEADER;  
           return FALSE;  
        }
        else if(sm.data_to_tail == SM_WAIT_BCC){
        
        sm.bcc_data = data[sm.idx] ;
    
        calc =  calc_bcc(data, sm.idx);
        if(sm.bcc_data == calc){
            sm.idx = 0;
            sm.data_counter=0;
             sm.data_to_tail=0;
            sm.state = SM_WAIT_HEADER; 
            printf("receive data success > 6 !!!\r\n");   
            return true;

        }
        else{
                printf("receive data fail <6  !!!\r\n");
                sm.idx = 0;
            sm.data_counter=0;
            sm.data_to_tail=0;
            sm.state = SM_WAIT_HEADER;  
            return FALSE;  

        }
      }

    case SM_WAIT_BCC:

        sm.bcc_data = data[sm.idx] ;
    
        calc =  calc_bcc(data, sm.idx);
        if(sm.bcc_data == calc){
            sm.idx = 0;
            sm.data_counter=0;
             sm.data_to_tail=0;
            sm.state = SM_WAIT_HEADER; 
            printf("receive data success > 6 !!!\r\n");   
            return true;

        }
        else{
            printf("receive data fail >6  !!!\r\n");
            sm.idx = 0;
            sm.data_counter=0;
            sm.data_to_tail=0;
            sm.state = SM_WAIT_HEADER;  
            return FALSE;  

        }



    break;
       
    }
}

/**
 * @brief  : 回调函数
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */


/**
 * @brief  : parse protocol form display board 
 * @note    
 * @param   
 * @param   
 * @retval  
 */
static void getParseCmd_displayBoard(void)
{
   switch (sm.cmd_notice)
   {
   case 0x01 : //power on or off

        if(sm.cmd_fun_code==0x01){//power on
           buzzer_sound() ; 
           responseCmd_fun(0x01,sm.cmd_fun_code);
           g_pro.power_on = power_on;  
        }
        else{
           buzzer_sound() ; 
           responseCmd_fun(0x0,sm.cmd_fun_code);
           g_pro.power_on = power_off;  
        }

    /* code */
   break;

   case 0x06: //buzzer sound 
     if(g_pro.power_on == power_on){
      if(sm.cmd_fun_code==0x01){//buzzer sound on
            buzzer_sound() ; 

      }
      else{
          buzzer_on_sound();
      }
    }


   break;
   
   default:
    break;
   }


}

