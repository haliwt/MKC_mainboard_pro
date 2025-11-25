#include "bsp.h"

#define ACK_HEADER   0x5A  //main board answer cmd header 
#define ACK_DEVICE_ID    0x10
#define ACK_CMD        0xFF
#define ACK_TAIL       0xFE

ProtocolSM sm;
uint8_t calc ;

static void getParseCmd_displayBoard(void);
static void ack_to_dispboard_handler(void);
static void getParseData_displayBoard(void);

/**
 * @brief  : BCC of check funtion
 * @note    receive data is length more 6 
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval   check code
 */
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
        if (data[1] == DEVICE_ID || data[1]==NEW_CMD_COPY) {

           sm.state = SM_WAIT_CMD_NOTICE;
           sm.idx = 2;
            
        }
        else{
           sm.idx = 0;
         
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
    case SM_WAIT_CMD_TAIL://6
        if (data[4] == FRAME_TAIL) {
           
           sm.state = SM_WAIT_CMD_BCC;
           sm.idx = 5;
        }
        else{
           sm.idx = 0;
      
           sm.state = SM_WAIT_HEADER;  
           return FALSE;  
        }


  
    case SM_WAIT_CMD_BCC://7
       sm.bcc_data = data[5];
 
      calc =  calc_bcc(data, 5);
      if(sm.bcc_data == calc){
        sm.idx = 0;
     
        sm.state = SM_WAIT_HEADER;    
        getParseCmd_displayBoard();
        return  TRUE;

      }
      else{
        sm.idx = 0;
   
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
	uint8_t i;  
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
           sm.state = SM_WAIT_HEADER;  
            return  FALSE;
        }
      

     case SM_WAIT_CMD_NOTICE:
       sm.cmd_notice =data[2];
       sm.state = SM_WAIT_FUN_JUDGE;
      sm.idx = 3;
	  
      case SM_WAIT_FUN_JUDGE:
       if(data[3] == FUNC_DATA){ //adjust is data . 0x0F
          sm.state = SM_WAIT_DATA_LENGHT;
          sm.idx = 4;
		  
       }
       else{
            sm.idx = 0;
         
           sm.state = SM_WAIT_HEADER;  
           return  FALSE;
       }

    
     //data length 
    case SM_WAIT_DATA_LENGHT:
      sm.data_length =data[4]; //data don't function code.
      sm.state = SM_WAIT_DATA;
      sm.idx = 5;

    

    case SM_WAIT_DATA:

      for(i=0;i< sm.data_length; i++){
           sm.data_buf[i]=data[5+i];
     
      }
      sm.state =SM_WAIT_TAIL;
      
      sm.idx = 5 + sm.data_length;
     

    case SM_WAIT_TAIL:
  
      
     if (data[sm.idx] == FRAME_TAIL) {
           
           sm.state = SM_WAIT_BCC;
    
           sm.idx = sm.idx + 1;//sm->idx + 1;
	
        }
        else{
         
           sm.idx = 0;
        
           sm.state = SM_WAIT_HEADER;  
           return FALSE;  
        }
    
    case SM_WAIT_BCC:
        sm.bcc_data = data[sm.idx] ;
    
        calc =  calc_bcc(data, sm.idx);
        if(sm.bcc_data == calc){
            sm.idx = 0;
      
            sm.state = SM_WAIT_HEADER; 
			getParseData_displayBoard();
           // printf("receive data success > 6 !!!\r\n");   
            return true;

        }
        else{
		  #if DEBUG_FLAG
            printf("receive data fail >6  !!!\r\n");
		  #endif 
            sm.idx = 0;
        
            sm.state = SM_WAIT_HEADER;  
            return FALSE;  

        }



    break;
       
    }
}
/**
 * @brief  : parse protocol is answer command .
 * @note    receive data is length more 6 
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
bool protocol_sm_ack_input(const uint8_t *data,uint8_t data_length) 
{
  if (data_length == 7) {
    switch (sm.state) {
      case SM_WAIT_HEADER:
        if (data[0] == ACK_HEADER) {
          sm.idx = 1;
          sm.state = SM_WAIT_FIXED;
        } else {
          return FALSE;
        }
        // fall through

      case SM_WAIT_FIXED:
        if (data[1] == ACK_DEVICE_ID) {
          sm.state = SM_WAIT_CMD_NOTICE;
          sm.idx = 2;
        } else {
          sm.idx = 0;
        
          sm.state = SM_WAIT_COPY_HEADER;
          return FALSE;
        }
        // fall through

      case SM_WAIT_COPY_HEADER:
        //sm.cmd_notice = data[2];
        if (data[2] == ACK_CMD) { // only process ack signal
          sm.state = SM_WAIT_COPY_CMD_NOTICE;
          sm.idx = 3;
        } else {
          sm.idx = 0;
     
          sm.state = SM_WAIT_HEADER;
          return FALSE;
        }
        // fall through
      case SM_WAIT_COPY_CMD_NOTICE:

         sm.cmd_notice = data[3];
         sm.state = SM_WAIT_COPY_FUNC_CODE;
         sm.idx = 4;
    

      case SM_WAIT_COPY_FUNC_CODE: //ACK cmd or noticer or data
        sm.cmd_fun_code = data[4];
        sm.state = SM_WAIT_CMD_TAIL;
        sm.idx = 5;
        // fall through

  

      case SM_WAIT_CMD_TAIL:
        if(data[5] == FRAME_TAIL) {
          sm.state = SM_WAIT_CMD_BCC;
          sm.idx = 6;
        } 
        else {
          sm.idx = 0;
      
          sm.state = SM_WAIT_HEADER;
          return FALSE;
        }
        // fall through

      case SM_WAIT_CMD_BCC:
        sm.bcc_data = data[6];
        calc = calc_bcc(data, 6); //bcc length = length -1 
        if (sm.bcc_data == calc) {
          sm.idx = 0;
      
          sm.state = SM_WAIT_HEADER;
          // 可以在这里处理应答信号
         // printf("ACK signal received!\r\n");
          return TRUE;
        } 
        else {
          sm.idx = 0;
      
          sm.state = SM_WAIT_HEADER;
          printf("receive ACK fail !!!\r\n");
          return FALSE;
        }
        break;
    }
    return FALSE;
  }
  return FALSE;
}

/**
 * @brief  : redeive form display board data don't command
 * @note    
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval 
 */
static void getParseData_displayBoard(void)
{
   switch (sm.cmd_notice)
   {
   case 0x1B : //set temperarue value .cmd=0x1B.
        if(sm.data_length==1){
		   g_pro.set_temerature_value_flag = 1;
           g_pro.set_temp_value = sm.data_buf[0];
        }

    /* code */
   break;

   case 0xFE:

       if(sm.data_length==3){


       }

   break;

  }


}

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
           responseCmd_fun(0x01,sm.cmd_fun_code);
           g_pro.power_on = power_off;  
        }

    /* code */
   break;

   case 0x03://plasma cmd
    if(sm.cmd_fun_code==0x01){//power on
           buzzer_sound() ; 
           responseCmd_fun(0x03,sm.cmd_fun_code);
	       plasma_open();
           g_pro.plasma_flag =open;
    }
    else{
           buzzer_sound() ; 
           responseCmd_fun(0x03,sm.cmd_fun_code);
           plasma_close();
           g_pro.plasma_flag =close;
    }


   break;

   case 0x06: //buzzer sound 
     if(g_pro.power_on == power_on){
      if(sm.cmd_fun_code==0x01){//buzzer sound on
            buzzer_sound() ; 

      }
      else{
          buzzer_no_sound();
      }
    }


   break;

  case 0x16: //buzzer sound with answer signal 
     if(g_pro.power_on == power_on){
      if(sm.cmd_fun_code==0x01){//buzzer sound on
            buzzer_sound() ; 
            responseCmd_fun(0x16,sm.cmd_fun_code);
      }
      else{
          buzzer_no_sound();
          responseCmd_fun(0x16,0x00);
      }
  }


   break;
   
   default:
    break;
   }


}

/**
 * @brief  : parse protocol form display board 
 * @note    
 * @param   
 * @param   
 * @retval  
 */
//static void ack_to_dispboard_handler(void)
//{
//   switch( sm.cmd_notice ){


//     case 0x01:

//    break;






//   }



//}