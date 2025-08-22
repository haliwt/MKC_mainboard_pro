#include "bsp.h"

uint8_t power_on_step,power_off_step,power_off_next_step,power_on_next_step =0;
 static void power_on_process(void);
 static void power_off_process(void);
/**
 * @brief  :  power on handler
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */


void power_on_handler(void)
{

   switch(power_on_step){

    case 0:
      power_off_step=0;
      power_on_next_step =0;
      g_pro.gTimer_adc_counter=0;
      power_on_step =1;

    break;

    case 1:
     power_on_process();


    break;

    default:
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

 static void power_on_process(void)
 {
    switch(power_on_next_step){

     case 0:
        power_off_step=0;
   
        fan_group_open();
        fan_oneself_open();
       
       
        power_on_next_step=1;
     break;

     case 1:
          plasma_open();
          cooler_open();

         power_on_next_step=2;
     break;

     case 2:

        if(g_pro.gTimer_adc_counter> 4){ //send temperature value to dispalboard
            g_pro.gTimer_adc_counter=0;
            //sendData_to_dispBoard(0x1A,32);
            adcRead_voltageValue();
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        

     break;

     default:
     break;

    }

}

/**
 * @brief  :  power off main  process
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */

 void power_off_handler(void)
 {
     switch(power_off_step){

      case 0:
          power_on_step =0;
          power_off_next_step=0;   
          power_off_step=1;

      break;

      case 1:
          power_off_process();

      break;

      default:

      break;




     }
     


 }
/**
 * @brief  :  power off initial  process
 * @note    该函数会根据输入字节更新状态机状态，并处理完整帧
 * @param   sm: 状态机实例  
 * @param   byte: 输入字节
 * @retval  true: 完整帧已解析，false: 未解析到完整
 */
static void power_off_process(void)
{
   switch(power_off_next_step){

     case 0:
    
       cooler_close();
      
       power_off_next_step=1;
     break;

     case 1:
       cooler_close();
       fan_group_close();
       fan_oneself_close();
       plasma_close();
      
     break;

     default:

     break;

 }

}





