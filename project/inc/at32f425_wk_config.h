/* add user code begin Header */
/**
  **************************************************************************
  * @file     at32f425_wk_config.h
  * @brief    header file of work bench config
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* define to prevent recursive inclusion -----------------------------------*/
#ifndef __AT32F425_WK_CONFIG_H
#define __AT32F425_WK_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes -----------------------------------------------------------------------*/
#include "stdio.h"
#include "at32f425.h"

/* private includes -------------------------------------------------------------*/
/* add user code begin private includes */

/* add user code end private includes */

/* exported types -------------------------------------------------------------*/
/* add user code begin exported types */

/* add user code end exported types */

/* exported constants --------------------------------------------------------*/
/* add user code begin exported constants */

/* add user code end exported constants */

/* exported macro ------------------------------------------------------------*/
/* add user code begin exported macro */

/* add user code end exported macro */

/* add user code begin dma define */
/* user can only modify the dma define value */
#define DMA1_CHANNEL1_BUFFER_SIZE   0
#define DMA1_CHANNEL1_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL1_PERIPHERAL_BASE_ADDR  0

#define DMA1_CHANNEL2_BUFFER_SIZE   0
#define DMA1_CHANNEL2_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL2_PERIPHERAL_BASE_ADDR   0

#define DMA1_CHANNEL3_BUFFER_SIZE   0
#define DMA1_CHANNEL3_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL3_PERIPHERAL_BASE_ADDR   0

//#define DMA1_CHANNEL4_BUFFER_SIZE   0
//#define DMA1_CHANNEL4_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL4_PERIPHERAL_BASE_ADDR   0

//#define DMA1_CHANNEL5_BUFFER_SIZE   0
//#define DMA1_CHANNEL5_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL5_PERIPHERAL_BASE_ADDR   0

//#define DMA1_CHANNEL6_BUFFER_SIZE   0
//#define DMA1_CHANNEL6_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL6_PERIPHERAL_BASE_ADDR   0

//#define DMA1_CHANNEL7_BUFFER_SIZE   0
//#define DMA1_CHANNEL7_MEMORY_BASE_ADDR   0
//#define DMA1_CHANNEL7_PERIPHERAL_BASE_ADDR   0
/* add user code end dma define */

/* Private defines -------------------------------------------------------------*/
//new PCB 
#define COOLER_PIN          GPIO_PINS_7
#define COOLER_GPIO_PORT    GPIOA

#define BEEP_PWM_PIN            GPIO_PINS_8//GPIO_PINS_5
#define BEEP_PWM_GPIO_PORT      GPIOB//GPIOA
//FAN GPIO
#define OUTPUT_12V_ENABLE_PIN    			GPIO_PINS_6
#define OUTPUT_12V_ENABLE_GPIO_PORT    	GPIOA

#define FAN_12V_CTL_PIN         		GPIO_PINS_4
#define FAN_12V_CTL_GPIO_PORT      		GPIOA

#define FAN_24V_CTL_PIN         			GPIO_PINS_5
#define FAN_24V_CTL_GPIO_PORT      			GPIOA

//ADC GPIO
#define ADC_TEMP_PIN    				GPIO_PINS_0
#define ADC_TEMP_GPIO_PORT    			GPIOB

#define ADC_WATER_PIN                  GPIO_PINS_1
#define ADC_WATER_GPIO_PORT            GPIOB

//ULTRASONIC GPIO
#define ULTR_PWM_PIN    				GPIO_PINS_8
#define ULTR_PWM_GPIO_PORT    			GPIOA

#define PLASMA_PIN                    GPIO_PINS_10//GPIO_PIN_6
#define PLASMA_GPIO_PORT              GPIOB

//HALL GPIO LED STRIP
#define HAL_PIN                        GPIO_PINS_7
#define HAL_GPIO_PORT                  GPIOB

#define LED_DOOR_PIN                   GPIO_PINS_9
#define LED_DOOR_GPIO_PORT             GPIOB  

/* exported functions ------------------------------------------------------- */
  /* system clock config. */
  void wk_system_clock_config(void);

  /* config periph clock. */
  void wk_periph_clock_config(void);

  /* nvic config. */
  void wk_nvic_config(void);

/* add user code begin exported functions */

/* add user code end exported functions */

#ifdef __cplusplus
}
#endif

#endif
