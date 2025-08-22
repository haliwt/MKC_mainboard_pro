#include "bsp.h"

uint8_t power_on_step;

/**
 * @brief  :  power on handler
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */


void power_on_handler(uint8_t power_flag)
{

   switch(power_flag){

    case 1:




    break;

    case 0:



    break;






   }



}
/**
 * @brief  :  power on initial process
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */

 static void power_on_init(void)
 {
    switch(power_on_step){

     case 0:
        
          

     break;

     case 1:


     break;

     case 2:

     break;

    }

}





