#ifndef __BSP_DMA_ADC_H
#define __BSP_DMA_ADC_H
#include "at32f425.h"

#define ADC_CHANNEL_COUNT 3

volatile extern uint8_t dma_trans_complete_flag;

extern  uint16_t adc_buf[ADC_CHANNEL_COUNT];

 void adcRead_voltageValue(void);



#endif 

