#include "bsp.h"

#define ACK_FRAME_HEADER 0x5A      //main board send data to main board
#define ACK_DEVICE_ID    0x10      //main board device address ID 
#define ACK_CMD_NOTICE   0xFF
#define ACK_FUNC_DATA    0x0F
#define ACK_FRAME_TAIL   0xFE
#define ACK_DATA_SIEZE  12

typedef struct {
    uint8_t cmd_notice;
    uint8_t func;

    uint8_t fun_code;
    uint8_t data_length;
    uint8_t ack_buf[ACK_DATA_SIEZE];
} responseParsedFrame_t;
responseParsedFrame_t ack_t;

static uint8_t bcc_check(const unsigned char *data, int len) ;
/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   receive data buffer, data of length, struct ParsedFrame to fill
 * @retval  true if frame is valid, false otherwise
 */
 void responseCmd_fun(uint8_t cmd,uint8_t fun_code)
 {
   
    //crc=0x55;
	ack_t.ack_buf[0]=0x5A; //head : mainboard Board = 0x5A
	ack_t.ack_buf[1]=0x10; //main board device No: 0x10
	ack_t.ack_buf[2]=ACK_CMD_NOTICE; //command : temperature of value 
	ack_t.ack_buf[3]=cmd; // 0x0F : is data ,don't command data.
	ack_t.ack_buf[4]=fun_code; //data of length: 0x01 - 2 byte.
	ack_t.ack_buf[5] = 0xFE;
    ack_t.ack_buf[6] = bcc_check(ack_t.ack_buf,5);
	
	ack_t.data_length = 7;
    usart1_dma_send(ack_t.ack_buf,7);

	// if(transferSize)
	// {
	// 	while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
	// 	transOngoingFlag=1;
	// 	HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	// }
}
/********************************************************************************
    **
    *Function Name:void SendWifiData_To_Cmd(uint8_t cmd,uint8_t data)
    *Function : commad order , data -command type
    *Input Ref: commad order , data -command type
    *Return Ref:NO
    *
*******************************************************************************/
void sendData_to_dispBoard(uint8_t notice,uint8_t data)
{
        ack_t.ack_buf[0]=0x5A; //head : main board 0x5A
        ack_t.ack_buf[1]=0x10; //main board device No: 0x10
        ack_t.ack_buf[2]=notice; //command type: fan speed of value 
        ack_t.ack_buf[3]=0x0F; // 0x0F : is data ,don't command order.
        ack_t.ack_buf[4]= 0x01; // don't data ,onlay is command order,recieve data is 1byte .
        ack_t.ack_buf[5]= data; // don't data 
        
        ack_t.ack_buf[6] = 0xFE;
        ack_t.ack_buf[7] = bcc_check(ack_t.ack_buf,6);
        
        ack_t.data_length = 8;
        usart1_dma_send(ack_t.ack_buf,8);
        // if(transferSize)
        // {
        //     while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
        //     transOngoingFlag=1;
        //     HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
        // }
	
}
/**
 * @brief  :  处理解析帧函数
 * @note    
 * @param   None
 * @retval  None
 */
/**********************************************************************
    *
    *Function Name:uint8_t bcc_check(const unsigned char *data, int len) 
    *Function: BCC????
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
static uint8_t bcc_check(const unsigned char *data, int len) 
{
    uint8_t bcc = 0;
	uint8_t i;
    for (i = 0; i < len; i++) {
        bcc ^= data[i];
    }
    return bcc;
}