#include "bsp.h"

uint8_t power_off_next_step,power_on_next_step =0;
uint8_t set_temp_counter;
uint8_t flag_counter;
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
   static uint8_t read_main_counter;
   static uint8_t adc_counter,read_temp_value;
   switch(power_on_next_step){

     case 0:
       power_off_next_step=0;
     
       g_pro.gTimer_adc_counter=0;
       g_pro.set_temp_value=20; //temp max is 20 
       sendData_to_dispBoard(0x1A,readAmbinet_temp_value());
   
        power_on_next_step=1;
     break;

     case 1:
        fan_24v_group_open();
        fan_12v_enable();
	    fan_12v_open();
        cooler_open();
        power_on_next_step=2;

     break;

     case 2:
          read_main_counter++;
          if(read_main_counter > 9){
              read_main_counter=0;
          if(g_pro.plasma_flag == open){
              plasma_open();
          }
          else{
             plasma_close();
          }
        }
         

         power_on_next_step=3;
     break;

     case 3:

        if(g_pro.gTimer_adc_counter> 2){ //send temperature value to dispalboard
            g_pro.gTimer_adc_counter=0;
          
            adcRead_voltageValue();
            read_temp_value = readAmbinet_temp_value();
           sendData_to_dispBoard(0x1A,read_temp_value);
        }
         power_on_next_step=4;

     break;

     case 4:
       set_temp_counter++;
       if(set_temp_counter > 29){
           set_temp_counter=0;
           flag_counter++;
          TEC_SetTargTemp(read_temp_value);

       }

        power_on_next_step=5;
     break;

     case 5:

      if(g_pro.gTimer_adc_water_counter > 3){

         g_pro.gTimer_adc_water_counter=0;

       if(readAtomization_adc_value() < 3000 ){
           
          
           adc_counter++;
		   if(adc_counter > 1){
               adc_counter =3;
			  ultrasonic_output();
        
              sendCmd_to_dispBoard(0x15,0x01);
		   }
		
         
           
           
       }
       else{
	   	  adc_counter=0;
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
   
   static uint16_t delay_counter;
  
   switch(power_off_next_step){

     case 0:
       power_on_next_step=0;
       cooler_close();
	   ultrasonic_stop();
       
       power_off_next_step=1;
     break;

     case 1:
       cooler_close();
      
       plasma_close();

       power_off_next_step=2;
      
     break;

     case 2:
       fan_24v_group_close();
	   fan_12v_disable();
       fan_12v_close();
       power_off_next_step=3;
     break;

     case 3:
        delay_counter++; //run instructions is about 20ns .
        if(delay_counter > 60000){ //60000*20ns = 1.2ms
          delay_counter=0;
          adcRead_voltageValue();
        }
        power_off_next_step=1;
     break;

     default:
        power_off_next_step=0;
     break;

 }

}





