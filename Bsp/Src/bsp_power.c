#include "bsp.h"

uint8_t power_off_next_step,power_on_next_step =0;
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

   power_on_process();
  
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
    
   static uint8_t adc_counter;
   switch(power_on_next_step){

     case 0:
       power_off_next_step=0;
     
       g_pro.gTimer_adc_counter=0;
    
   
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

        if(g_pro.gTimer_adc_counter> 2){ //send temperature value to dispalboard
            g_pro.gTimer_adc_counter=0;
          
            adcRead_voltageValue();
        
           sendData_to_dispBoard(0x1A,readAmbinet_temp_value());
        }
         power_on_next_step=3;

     break;

     case 3:

      if(g_pro.gTimer_adc_water_counter > 3){

         g_pro.gTimer_adc_water_counter=0;

       if(readAtomization_adc_value() < 3000 ){
           
           if(adc_counter ==0){
                 adc_counter++;
           }
           else{
           ultrasonic_output();
        
           sendCmd_to_dispBoard(0x15,0x01);
           }
       }
       else{
          sendCmd_to_dispBoard(0x15,0x0);
          ultrasonic_stop();
          }
       }
      
      power_on_next_step=2;
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
     power_off_process();
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
       power_on_next_step=0;
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





