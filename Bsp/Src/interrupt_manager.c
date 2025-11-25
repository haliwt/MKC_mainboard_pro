#include "bsp.h"



void tim17_callback_handler(void)
{
    static uint16_t tim17_counter;

	tim17_counter ++;

	if(tim17_counter >999){

	   tim17_counter=0;
      // g_pro.gTimer_set_temp_counter++;
	   g_pro.gTimer_adc_water_counter++;
	   g_pro.gTimer_adc_temp_counter++;
	}


}

