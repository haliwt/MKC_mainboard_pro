#include "bsp.h"

volatile uint8_t dma_trans_complete_flag;

 uint16_t adc_buf[ADC_CHANNEL_COUNT];

 uint16_t voltage;

 static void adc_again_enable_adc(void);

 typedef struct ADC_TYPE_T{

  uint16_t adc_detected;
  uint16_t adc_temperature;
  uint16_t adc_atomization;
    

 }adc_typedef_t;

adc_typedef_t adc_t;

/**
 * 
 * @brief
 * @note:
 * @parameter :
 */
void adcRead_voltageValue(void)
 {
    uint8_t i;
    
    if(dma_trans_complete_flag==1){
        dma_trans_complete_flag ++;

          /* 打印采样结果 */
    for(i = 0; i < ADC_CHANNEL_COUNT; i++)
    {
        voltage = (adc_buf[i] / 4095) * 3300;

        printf("CH[%d] ADC=%d  Voltage=%d V\r\n", i, adc_buf[i], voltage);

    }

   }

   if( dma_trans_complete_flag ==2){

      dma_trans_complete_flag =0;
        // 清除 DMA 完成标志
      dma_flag_clear(DMA1_FDT1_FLAG);
    /* flexible function enable */
      dma_flexible_config(DMA1, FLEX_CHANNEL3, DMA_FLEXIBLE_ADC1);
    // 重新打开 DMA 通道
    dma_channel_enable(DMA1_CHANNEL1, TRUE);

    // 软件触发 ADC 转换
    adc_ordinary_software_trigger_enable(ADC1, TRUE);

   
   }


 }


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




