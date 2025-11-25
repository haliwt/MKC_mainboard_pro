#include "bsp.h"

/**
 * @brief  display board set temperature value 
 * @note   temp range "10~20"
 * @param  
 * 
 */
void TEC_SetTargTemp(uint8_t amtemp_value)
{
   

	 if(g_pro.set_temerature_value_flag ==0){

	     if(amtemp_value > 20 ){
		     cooler_open();

         }
		 else if(amtemp_value < 20){

		    cooler_close();
         }


	 }
	 else if(g_pro.set_temerature_value_flag ==1){ //This is bug need process .DATA.2025.10.09

         if(g_pro.set_temp_value < amtemp_value){
		        cooler_open();

         }
		 else
		    cooler_close();
		 

     }   
      

}


