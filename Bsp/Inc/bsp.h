#ifndef __BSP_H
#define __BSP_H
#include "at32f425.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
#include "bsp_rxdma_usart.h"
#include "bsp_txdma_usart.h"
#include "bsp_protocol_sm.h"
#include "bsp_ntc.h"
#include "bsp_power.h"

#include "bsp_freertos.h"
#include "interrupt_manager.h"

#define  USE_FreeRTOS      1

#define  DEBUG_FLAG        1


#if USE_FreeRTOS == 1
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ??????????l? */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* '???????? */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* ????????? */
#endif

/* Ä¬ÈÏÊÇ¹Ø±Õ×´Ì¬ */
#define  Enable_EventRecorder  1

#if Enable_EventRecorder == 1
	#include "EventRecorder.h"
#endif

typedef enum{
  power_off,
  power_on

}power_state_enum;
	
typedef enum{
  close,
  open
}fun_state_enum;

// system.h
typedef struct {
    uint8_t power_on;   // 开机标志
    uint8_t plasma_flag;
    uint8_t set_temp_value;
    uint8_t mode;
    uint8_t error_code;
    // ... 其他系统状态
   uint8_t gTimer_adc_counter;
} system_param_t;

extern system_param_t g_pro;



void bsp_init(void);


#endif 

