#include "bsp.h"


void ultrasonic_output(void)
{
 tmr_output_config_type tmr_output_struct;
 /* configure channel 1 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  /* 2. 应用到定时器通道 */
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  /* 3. 设置比较值（占空比） */
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, 328);// pwm duty = 444/888=50% dlet 
  tmr_output_channel_immediately_set(TMR1, TMR_SELECT_CHANNEL_1, TRUE);
  /* 4. 使能定时器 */
  tmr_output_enable(TMR1, TRUE);
  tmr_counter_enable(TMR1, TRUE);

 
}

void ultrasonic_stop(void)
{

 // tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 125);
  tmr_output_channel_immediately_set(TMR1, TMR_SELECT_CHANNEL_1,FALSE);
  tmr_output_enable(TMR1, FALSE);
  tmr_counter_enable(TMR1, FALSE); //stop timer output pwm  
}