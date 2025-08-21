#include "bsp.h"

PROCESS_TYPEDEF g_pro;

void bsp_init(void)
{
	ProtocolSM sm;
	protocol_sm_init(&sm) ;
	#if(Enable_EventRecorder == 1) 
		/* ³õÊ¼»¯EventRecorder²¢¿ªÆô */
		EventRecorderInitialize(EventRecordAll, 1U);
		EventRecorderStart();
	#endif
}

