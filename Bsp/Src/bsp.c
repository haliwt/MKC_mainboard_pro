#include "bsp.h"

PROCESS_TYPEDEF g_pro;

void bsp_init(void)
{
    
#if(Enable_EventRecorder == 1) 
	/* ³õÊ¼»¯EventRecorder²¢¿ªÆô */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif
}

