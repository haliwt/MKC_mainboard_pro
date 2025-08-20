#ifndef __BSP_H
#define __BSP_H
#include "at32f425.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wk_adc.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_dma.h"
#include "wk_gpio.h"

//freertos 

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"





//main board 

#include "bsp_tim.h"
#include "bsp_dma_usart.h"
#include "bsp_dma_adc.h"
#include "bsp_message.h"
#include "bsp_plasma.h"
#include "bsp_ultrasonic.h"
#include "bsp_cooler.h"
#include "bsp_buzzer.h"
#include "bsp_fan.h"

#include "interrupt_manager.h"


typedef struct _PROCESS_T{

  uint8_t rx_length; //接收数据长度
  uint8_t rx_complete_flag; //接收完成标志 


}PROCESS_TYPEDEF;
extern PROCESS_TYPEDEF g_pro;



void bsp_init(void);


#endif 

