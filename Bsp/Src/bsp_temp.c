#include "bsp.h"

/**
 * @brief  display board set temperature value 
 * @note   temp range "10~20"
 * @param  
 * 
 */
void TEC_SetTargTemp(uint8_t amtemp_value)
{
     if(g_pro.set_temp_value < amtemp_value){ //this is cooler don't heat.

          cooler_open();

     } 
     else{

         cooler_close();

     }   
      

}


