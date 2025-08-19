#include "bsp.h"

#define BIT_1                (1<<1)

#define DECODER_BIT_0        (1<< 0)

/***********************************************************************************************************
											閸戣姤鏆熸竟鐗堟
***********************************************************************************************************/
static void vTaskWifiPro(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);


/* 閸掓稑缂撴禒璇插闁矮淇婇張鍝勫煑 */
//static void AppObjCreate(void);


/***********************************************************************************************************
											閸欐﹢鍣烘竟鐗堟
***********************************************************************************************************/
static TaskHandle_t xHandleTaskWifiPro = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
#define LOWEST_PRIORITY   1  // ???????
#define HIGHEST_PRIORITY  2

typedef struct Msg
{
	uint8_t  ucMessageID;
	uint8_t usData[12];

}MSG_T;

MSG_T   gl_tMsg; /* ?????????????? */

uint8_t txBuf[] ={0x0A,0x0B,0x0C,0x0d};
uint8_t  txLen = 4;//sizeof(txBuf) - 1; // Exclude null terminator


/**********************************************************************************************************
*
*	Function Name:void freeRTOS_Handler(void)
*   Function :
*	
*  
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
     /* 閸掓稑缂撴禒璇插 */
	  AppTaskCreate();
	  
	  /* 閸掓稑缂撴禒璇插闁矮淇婇張鍝勫煑 */
//	   AppObjCreate();
	  
	  /* 閸氼垰濮╃拫鍐ㄥ閿涘苯绱戞慨瀣⒔鐞涘奔鎹㈤敓?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 */
	   vTaskStartScheduler();


}

/**********************************************************************************************************
*	Function Name: vTaskStart
*	閸旂喕鍏樼拠瀛樻: 閸氼垰濮╂禒璇插閿涘奔绡冪亸杈ㄦЦ閺堫澁鎷�1�71閿�1�7?7妤傛ü绱崗鍫㈤獓娴犺濮熼敍宀冪箹闁插瞼鏁ゆ担婊勫瘻闁款喗澹傞幓蹇ユ嫹1閿�1�7?7閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7
*	閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7    閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7: pvParameters 閺勵垰婀崚娑樼紦鐠囥儰鎹㈤崝鈩冩娴肩媴鎷�1�71閿�1�7?7閿�1�7?1閿�1�7?7閻ㄥ嫬鑸伴崣?
*	閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7: 閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7
*   閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7: 4  (閺佸府鎷�1�71閿�1�7?7閿�1�7?1閿�1�7?7鐡掑﹤鐨导妯哄帥缁狙嗙Ш娴ｅ函绱濇潻娆庨嚋鐠虹劏COS閻╃寮�1�7)
************************************ifi**********************************************************************/
 static void vTaskWifiPro(void *pvParameters)
 {
  
      while(1)
      {
       
        vTaskDelay(pdMS_TO_TICKS(1000));
     }


 }

/**
 * @brief  :  static void vTaskStart(void *pvParameters)鍒涘缓鏁版嵁澶勭悊浠诲姟锛屼紭鍏堢骇涓轰腑绛�1�7
 * @note    浠诲姟鍐呴儴浣跨敤闃熷垪鎺ユ敹鏁版嵁锛岄渶鍏堝垵濮嬪寲闃熷垪
 * @param   None
 * @retval  None
 */
static void vTaskMsgPro(void *pvParameters)
{
  while(1)
    {
   
			vTaskDelay(pdMS_TO_TICKS(10));
				                                   
 	}
}	

/**
 * @brief  :  static void vTaskStart(void *pvParameters)鍒涘缓鏁版嵁澶勭悊浠诲姟锛屼紭鍏堢骇涓轰腑绛�1�7
 * @note    浠诲姟鍐呴儴浣跨敤闃熷垪鎺ユ敹鏁版嵁锛岄渶鍏堝垵濮嬪寲闃熷垪
 * @param   None
 * @retval  None
 */
static void vTaskStart(void *pvParameters)
{
    
	while(1)
    {
  
  
			vTaskDelay(pdMS_TO_TICKS(10));
       
    }
 }
       

  
/**
 * @brief  :  void AppTaskCreate (void)寤烘暟鎹鐞嗕换鍔★紝浼樺厛绾т负涓瓑
 * @note    浠诲姟鍐呴儴浣跨敤闃熷垪鎺ユ敹鏁版嵁锛岄渶鍏堝垵濮嬪寲闃熷垪
 * @param   None
 * @retval  None
 */
void AppTaskCreate (void)
{
   xTaskCreate( vTaskWifiPro,     		/* 娴犺濮熼崙鑺ユ殶  */
                 "vTaskWifiPro",   		/* 娴犺濮熼敓?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7    */
                 128,            		/* 娴犺濮熼弽鍫濄亣鐏忓骏绱濋崡鏇氱秴word閿涘奔绡冪亸杈ㄦЦ4鐎涙濡�1�7 */
                 NULL,           		/* 娴犺濮熼崣鍌涙殶  */
                 3,              		/* 娴犺濮熸导妯哄帥閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閺佸府鎷�1�71閿�1�7?7閿�1�7?1閿�1�7?7鐡掑﹤鐨导妯哄帥缁狙嗙Ш娴ｅ函绱濇潻娆庨嚋鐠虹劏COS閻╃寮�1�7 */
                 &xHandleTaskWifiPro);   /* 娴犺濮熼崣銉︾労  */
 
  xTaskCreate( vTaskMsgPro,     		/* 娴犺濮熼崙鑺ユ殶  */
                 "vTaskMsgPro",   		/* 娴犺濮熼敓?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7    */
                 128,            		/* 娴犺濮熼弽鍫濄亣鐏忓骏绱濋崡鏇氱秴word閿涘奔绡冪亸杈ㄦЦ4鐎涙濡�1�7 */
                 NULL,           		/* 娴犺濮熼崣鍌涙殶  */
                 1,              		/* 娴犺濮熸导妯哄帥閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閺佸府鎷�1�71閿�1�7?7閿�1�7?1閿�1�7?7鐡掑﹤鐨导妯哄帥缁狙嗙Ш娴ｅ函绱濇潻娆庨嚋鐠虹劏COS閻╃寮�1�7 */
                 &xHandleTaskMsgPro);   /* 娴犺濮熼崣銉︾労  */


   xTaskCreate( vTaskStart,     		/* 娴犺濮熼崙鑺ユ殶  */
                 "vTaskStart",   		/* 娴犺濮熼敓?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7    */
                 128,            		/* 娴犺濮熼弽鍫濄亣鐏忓骏绱濋崡鏇氱秴word閿涘奔绡冪亸杈ㄦЦ4鐎涙濡�1�7 */
                 NULL,           		/* 娴犺濮熼崣鍌涙殶  */
                 2,              		/* 娴犺濮熸导妯哄帥閿�1�7?1閿�1�7?7?1閿�1�7?1閿�1�7?7?7 閺佸府鎷�1�71閿�1�7?7閿�1�7?1閿�1�7?7鐡掑﹤鐨导妯哄帥缁狙嗙Ш娴ｅ函绱濇潻娆庨嚋鐠虹劏COS閻╃寮�1�7 */
                 &xHandleTaskStart );   /* 娴犺濮熼崣銉︾労  */
}


/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//     
//     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//   //  MSG_T *ptMsg;

//    if(huart->Instance==USART2)
//    {
//	
// 
//	
//     //  ENABLE_INT();
//	  __HAL_UART_CLEAR_OREFLAG(&huart2);
//      //HAL_UART_Receive_IT(&huart2,wifi_rx_inputBuf,1);
//	}
//    else if(huart->Instance==USART1)//if(huart==&huart1) // Motor Board receive data (filter)
//	{
//     
//		}

//      //  ENABLE_INT();
//	    __HAL_UART_CLEAR_OREFLAG(&huart1);
//		//HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
//		
//	 }
//    
//    
//  
// }


//void freertos_set_prority(void)
//{
//	
//	vTaskPrioritySet(xHandleTaskStart, LOWEST_PRIORITY);  // ???????
//	taskYIELD();  // ??????
//	vTaskPrioritySet(xHandleTaskMsgPro,HIGHEST_PRIORITY);  // ???????

//   
//} 



