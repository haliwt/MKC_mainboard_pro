#include "bsp.h"

#define BIT_1                (1<<1)

#define DECODER_BIT_0        (1<< 0)

/***********************************************************************************************************
											靑芥暟澹版槑
***********************************************************************************************************/
//static void vTaskWifiPro(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);


/* 青涘缓浠诲姟閫氫俊靈哄埗 */
//static void AppObjCreate(void);


/***********************************************************************************************************
											静橀噺澹版槑
***********************************************************************************************************/
//static TaskHandle_t xHandleTaskWifiPro = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
#define LOWEST_PRIORITY   1  // ???????
#define HIGHEST_PRIORITY  2

typedef struct Msg
{
	uint8_t  ucMessageID;
	uint8_t usData[12];

}MSG_T;

MSG_T  gl_tMsg; /* ?????????????? */


uint8_t fan_switch_flag,power_on_flag = 0;


/**********************************************************************************************************
*
*	Function Name:void freeRTOS_Handler(void)
*   Function :
*	
*  
**********************************************************************************************************/
void freertos_handler(void)
{
     /* 青涘缓浠诲姟 */
	  AppTaskCreate();
	  
	  /* 青涘缓浠诲姟閫氫俊靈哄埗 */
//	   AppObjCreate();
	  
	  /* 靚姩璋冨害锛屽紑濮嬫墽睛屼杢锟?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7 */
	   vTaskStartScheduler();


}

// /**********************************************************************************************************
//  * 
// *	Function Name: vTaskStart
// *	Function : only one freeRTOS task 
// *	Input Ref:NO
// *	Return Ref:NO
// *   
// ************************************ifi**********************************************************************/
//  static void vTaskWifiPro(void *pvParameters)
//  {
  
//       while(1)
//       {
       
//         vTaskDelay(pdMS_TO_TICKS(1000));
//      }


//  }

/**
 * @brief  :  static void vTaskStart(void *pvParameters)创建数杮处睆任务，优先级为中筄1�71�1�77
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None
 * @retval  None
 */
static void vTaskMsgPro(void *pvParameters)
{
  
  
  while(1)
  {
     
    if(fan_switch_flag == 0)
    {
        fan_singal_open();
        fan_group_open();
        if(power_on_flag == 0)
        {
          power_on_flag++;
          printf("vTaskMsgPro: fan_group_open \r\n");
        }
        
        
    }
    else
    {
      fan_singal_close();
      fan_group_close();
        
    }
    
 
      // 2. 每隔120s和240s执行一次
    if(g_pro.gTimer_1s_flag > 180) // 240s
     {
        g_pro.gTimer_1s_flag = 0;
        fan_switch_flag = !fan_switch_flag; // 切换风扇状态
   
      }
  
	 vTaskDelay(pdMS_TO_TICKS(50));
				                                   
 	}
}	

/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None
 * @retval  None
 */
static void vTaskStart(void *pvParameters)
{
  BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(5000); //40//30/* 璁剧疆鏈拷澶х瓑寰呮椂闂翠负30ms */
	uint32_t ulValue;  
	while(1)
  {
     xResult = xTaskNotifyWait(0x00000000,      
						          0xFFFFFFFF,      
						          &ulValue,        /* 淇濆瓨ulNotifiedValue鍒板彉閲弖lValue涓�1锟�7 */
						          xMaxBlockTime);  /* block times,releas cpu power right */
		
	if( xResult == pdPASS )
	{
    	/* 鎺ユ敹鍒版秷鎭紝妫拷娴嬮偅涓綅琚寜涓�1锟�7 */

        if((ulValue & DECODER_BIT_0 ) != 0)
        {
           gl_tMsg.ucMessageID++;
			
           usart1_dma_rx_handler();

        }
    }
 }
}
       

  
/**
 * @brief  :  void AppTaskCreate (void)建数杮处睆任务，优先级为中等
 * @note    任务内部使用队列接收数杮，需先初始化队列
 * @param   None
 * @retval  None
 */
void AppTaskCreate (void)
{
  //  xTaskCreate( vTaskWifiPro,     		/* 浠诲姟靑芥暟  */
  //                "vTaskWifiPro",   		/* 浠诲姟锟?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7    */
  //                128,            		/* 浠诲姟靝堝㝇睝忥紝靗曚綅word锛屼篃睝辨槸4瀛楄妄1�71�1�77 */
  //                NULL,           		/* 浠诲姟静傛暟  */
  //                3,              		/* 浠诲姟浼樺厛锄1�71�1�77?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7 靝帮拄1�71�1�771锄1�71�1�77?7锄1�71�1�77?1锄1�71�1�77?7瓒婂皬浼樺厛绾ц秺浣庯紝杩欎釜璺焨COS革�6�0弄1�71�1�77 */
  //                &xHandleTaskWifiPro);   /* 浠诲姟静ユ焺  */
 
  xTaskCreate( vTaskMsgPro,     		/* 浠诲姟靑芥暟  */
                 "vTaskMsgPro",   		/* 浠诲姟锟?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7    */
                 128,            		/* 浠诲姟靝堝㝇睝忥紝靗曚綅word锛屼篃睝辨槸4瀛楄妄1�71�1�77 */
                 NULL,           		/* 浠诲姟静傛暟  */
                 1,              		/* 浠诲姟浼樺厛锄1�71�1�77?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7 靝帮拄1�71�1�771锄1�71�1�77?7锄1�71�1�77?1锄1�71�1�77?7瓒婂皬浼樺厛绾ц秺浣庯紝杩欎釜璺焨COS革�6�0弄1�71�1�77 */
                 &xHandleTaskMsgPro);   /* 浠诲姟静ユ焺  */


   xTaskCreate( vTaskStart,     		/* 浠诲姟靑芥暟  */
                 "vTaskStart",   		/* 浠诲姟锟?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7    */
                 128,            		/* 浠诲姟靝堝㝇睝忥紝靗曚綅word锛屼篃睝辨槸4瀛楄妄1�71�1�77 */
                 NULL,           		/* 浠诲姟静傛暟  */
                 2,              		/* 浠诲姟浼樺厛锄1�71�1�77?1锄1�71�1�77?7?1锄1�71�1�77?1锄1�71�1�77?7?7 靝帮拄1�71�1�771锄1�71�1�77?7锄1�71�1�77?1锄1�71�1�77?7瓒婂皬浼樺厛绾ц秺浣庯紝杩欎釜璺焨COS革�6�0弄1�71�1�77 */
                 &xHandleTaskStart );   /* 浠诲姟静ユ焺  */
}






void vTaskNotic_Decoder_irq_handler(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xTaskNotifyFromISR(xHandleTaskStart,  /* 鐩爣浠诲姟 */
                    DECODER_BIT_0 ,     /* 璁剧疆鐩爣浠诲姟浜嬩欢鏍囧織浣峛it0  */
                    eSetBits,  /* 灏嗙洰鏍囦换鍔＄殑浜嬩欢鏍囧織浣嶄笌BIT_0杩涜鎴栨搷浣滐紝 灏嗙粨鏋滆祴鍊肩粰浜嬩欢鏍囧織浣� */
                    &xHigherPriorityTaskWoken);

                /* 濡傛灉xHigherPriorityTaskWoken = pdTRUE锛岄偅涔堥€€鍑轰腑鏂悗鍒囧埌褰撳墠鏈€楂樹紭鍏堢骇浠诲姟鎵ц */
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
 
}

