#include "bsp.h"


// system.c
system_param_t g_pro = {0}; // 默认初始化

// void system_init(void) {
//     g_pro.power_on = read_power_on_flag(); // 从硬件/Flash读取
// }


void bsp_init(void)
{
	protocol_sm_init() ;
	#if(Enable_EventRecorder == 1) 
		/* ³õÊ¼»¯EventRecorder²¢¿ªÆô */
		EventRecorderInitialize(EventRecordAll, 1U);
		EventRecorderStart();
	#endif
}

