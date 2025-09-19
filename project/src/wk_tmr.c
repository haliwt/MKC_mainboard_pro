/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_tmr.c
  * @brief    work bench config program
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

/* Includes ------------------------------------------------------------------*/
#include "wk_tmr.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  init tmr1 function.
  * @param  none
  * @retval none
  */
void wk_tmr1_init(void)
{
  /* add user code begin tmr1_init 0 */
  // ultrasonic atomization is pwm 108KHz
  /* add user code end tmr1_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_output_config_type tmr_output_struct;
  tmr_brkdt_config_type tmr_brkdt_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr1_init 1 */

  /* add user code end tmr1_init 1 */

  /* configure the tmr1 CH1 pin */
  gpio_pin_mux_config(ULTR_PWM_GPIO_PORT, GPIO_PINS_SOURCE8, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = ULTR_PWM_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(ULTR_PWM_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR1, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR1, 0);
  tmr_period_buffer_enable(TMR1, FALSE);
  tmr_base_init(TMR1, 887, 0); // Divider value = 0, Period Value = 887 F= 108KHz

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR1, FALSE);
  tmr_primary_mode_select(TMR1, TMR_PRIMARY_SEL_RESET);

  /* configure channel 1 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, 0);
  tmr_output_channel_buffer_enable(TMR1, TMR_SELECT_CHANNEL_1, FALSE);

  tmr_output_channel_immediately_set(TMR1, TMR_SELECT_CHANNEL_1, FALSE);

  /* configure break and dead-time settings */
  tmr_brkdt_struct.brk_enable = FALSE;
  tmr_brkdt_struct.auto_output_enable = FALSE;
  tmr_brkdt_struct.brk_polarity = TMR_BRK_INPUT_ACTIVE_LOW;
  tmr_brkdt_struct.fcsoen_state = FALSE;
  tmr_brkdt_struct.fcsodis_state = FALSE;
  tmr_brkdt_struct.wp_level = TMR_WP_OFF;
  tmr_brkdt_struct.deadtime = 0;
  tmr_brkdt_config(TMR1, &tmr_brkdt_struct);

  tmr_brk_filter_value_set(TMR1, 0);


  tmr_output_enable(TMR1, FALSE);

  tmr_counter_enable(TMR1, FALSE);

  /* add user code begin tmr1_init 2 */

  /* add user code end tmr1_init 2 */
}

/**
  * @brief  init tmr2 function.
  * @param  none
  * @retval none
  */
//void wk_tmr2_init(void)
//{
//  /* add user code begin tmr2_init 0 */
//   //Buzzer sound frequency is 4KHZ
//  /* add user code end tmr2_init 0 */

//  gpio_init_type gpio_init_struct;
//  tmr_output_config_type tmr_output_struct;

//  gpio_default_para_init(&gpio_init_struct);

//  /* add user code begin tmr2_init 1 */
    //  crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE); //THIS IS OPEN TMR16 CLOCK .WT.EDTI 2025.09.19
//  /* add user code end tmr2_init 1 */

//  /* configure the tmr2 CH1 pin */
//  gpio_pin_mux_config(BEEP_PWM_GPIO_PORT, GPIO_PINS_SOURCE5, GPIO_MUX_2);
//  gpio_init_struct.gpio_pins = BEEP_PWM_PIN;
//  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
//  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
//  gpio_init(BEEP_PWM_GPIO_PORT, &gpio_init_struct);

//  /* configure counter settings */
//  tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);
//  tmr_clock_source_div_set(TMR2, TMR_CLOCK_DIV1);
//  tmr_period_buffer_enable(TMR2, FALSE);
//  tmr_base_init(TMR2, 249, 95);

//  /* configure primary mode settings */
//  tmr_sub_sync_mode_set(TMR2, FALSE);
//  tmr_primary_mode_select(TMR2, TMR_PRIMARY_SEL_RESET);

//  /* configure channel 1 output settings */
//  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
//  tmr_output_struct.oc_output_state = TRUE;
//  tmr_output_struct.occ_output_state = FALSE;
//  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
//  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
//  tmr_output_struct.oc_idle_state = FALSE;
//  tmr_output_struct.occ_idle_state = FALSE;
//  tmr_output_channel_config(TMR2, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
//  tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 0);
//  tmr_output_channel_buffer_enable(TMR2, TMR_SELECT_CHANNEL_1, FALSE);

//  tmr_output_channel_immediately_set(TMR2, TMR_SELECT_CHANNEL_1, FALSE);


// // tmr_counter_enable(TMR2, TRUE); //WT.EDIT 

//  /* add user code begin tmr2_init 2 */

//  /* add user code end tmr2_init 2 */
//}


/**
  * @brief  init tmr16 function.
  * @param  none
  * @retval none
  */
void wk_tmr16_init(void)
{
  /* add user code begin tmr16_init 0 */
   //Buzzer sound frequency is 4KHZ
  /* add user code end tmr16_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_output_config_type tmr_output_struct;
  tmr_brkdt_config_type tmr_brkdt_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr16_init 1 */
  crm_periph_clock_enable(CRM_TMR16_PERIPH_CLOCK, TRUE); //THIS IS OPEN TMR16 CLOCK .WT.EDTI 2025.09.19

  /* add user code end tmr16_init 1 */

  /* configure the tmr16 CH1 pin */
  gpio_pin_mux_config(BEEP_PWM_GPIO_PORT, GPIO_PINS_SOURCE8, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = BEEP_PWM_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(BEEP_PWM_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_cnt_dir_set(TMR16, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR16, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR16, 0);
  tmr_period_buffer_enable(TMR16, FALSE);
  tmr_base_init(TMR16, 249, 95);

  /* configure channel 1 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR16, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  tmr_channel_value_set(TMR16, TMR_SELECT_CHANNEL_1, 0);
  tmr_output_channel_buffer_enable(TMR16, TMR_SELECT_CHANNEL_1, FALSE);

  tmr_output_channel_immediately_set(TMR16, TMR_SELECT_CHANNEL_1, FALSE);

  /* configure break and dead-time settings */
  tmr_brkdt_struct.brk_enable = FALSE;
  tmr_brkdt_struct.auto_output_enable = FALSE;
  tmr_brkdt_struct.brk_polarity = TMR_BRK_INPUT_ACTIVE_LOW;
  tmr_brkdt_struct.fcsoen_state = FALSE;
  tmr_brkdt_struct.fcsodis_state = FALSE;
  tmr_brkdt_struct.wp_level = TMR_WP_OFF;
  tmr_brkdt_struct.deadtime = 0;
  tmr_brkdt_config(TMR16, &tmr_brkdt_struct);
  
  tmr_brk_filter_value_set(TMR16, 0);

  tmr_output_enable(TMR16, TRUE);

  tmr_counter_enable(TMR16, TRUE);

  /* add user code begin tmr16_init 2 */

  /* add user code end tmr16_init 2 */
}

/**
  * @brief  init tmr17 function.
  * @param  none
  * @retval none
  */
void wk_tmr17_init(void)
{
  /* add user code begin tmr17_init 0 */

  /* add user code end tmr17_init 0 */


  /* add user code begin tmr17_init 1 */

  /* add user code end tmr17_init 1 */

  /* configure counter settings */
  tmr_cnt_dir_set(TMR17, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR17, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR17, 0);
  tmr_period_buffer_enable(TMR17, FALSE);
  tmr_base_init(TMR17, 999, 95);

  tmr_counter_enable(TMR17, TRUE);

  /**
   * Users need to configure TMR17 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR17 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f425_int.c file.
   *     --void TMR17_GLOBAL_IRQHandler(void)
   */

  /* add user code begin tmr17_init 2 */
    /* 3. 使能更新中断（溢出中断） */
    
    tmr_interrupt_enable(TMR17, TMR_OVF_INT, TRUE);

    /* 4. NVIC 使能对应中断向量 */
  
  /* add user code end tmr17_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
