#include "bsp.h"

volatile uint8_t dma_trans_complete_flag;

 uint16_t adc_buf[ADC_CHANNEL_COUNT];

 uint16_t voltage;

 static void adc_again_enable_adc(void);

 typedef struct ADC_TYPE_T{

  uint16_t adc_detected;
  uint16_t adc_temperature;
  uint16_t adc_atomization;
  uint8_t  adc_temperature_value;

 }adc_typedef_t;

adc_typedef_t adc_t;

 uint8_t disp_temp,disp_atom;

/**
 * 
 * @brief: read ADC switch result voltage value 
 * @note:
 * @parameter :
 */
void adcRead_voltageValue(void)
 {
    /* 打印采样结果 */
   
	
   
     adc_t.adc_detected= (adc_buf[0]  * 3300)/4095;
     //vTaskDelay(pdMS_TO_TICKS(5));
     adc_t.adc_temperature = (adc_buf[1] * 3300)/4095;
     //vTaskDelay(pdMS_TO_TICKS(5));
     adc_t.adc_atomization =  (adc_buf[2] * 3300)/4095;
     //vTaskDelay(pdMS_TO_TICKS(5));
     
     Get_Ntc_Resistance_Temperature_Handler(adc_t.adc_temperature);
     disp_temp= getNtc_linearTemperature_value();

 
     #if DEBUG_FLAG
      printf("adc_temp = %d\r\n",disp_temp);

      printf("adc_atomi = %d\r\n",adc_t.adc_atomization);
     #endif 
 

     
     
      adc_again_enable_adc();

    

}

uint8_t readAmbinet_temp_value(void)
{
     return disp_temp;
}

/**
 * 
 * @brief: read ADC switch result voltage value 
 * @note:
 * @parameter :
 */
 static void adc_again_enable_adc(void)
 {
 adc_base_config_type adc_base_struct;
  adc_base_default_para_init(&adc_base_struct);
  adc_base_struct.sequence_mode = TRUE;//FALSE; //be used to set "TRUE" ,has three channel .
  adc_base_struct.repeat_mode = FALSE;
  adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
  adc_base_struct.ordinary_channel_length = 3;//1; need ADC1 switch three channel .
  adc_base_config(ADC1, &adc_base_struct);
  adc_ordinary_software_trigger_enable(ADC1, TRUE);

 }




