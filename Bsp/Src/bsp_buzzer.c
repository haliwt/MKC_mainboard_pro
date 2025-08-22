#include "bsp.h"


void buzzer_sound(void)
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
  tmr_output_channel_config(TMR2, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 125);
  tmr_output_channel_immediately_set(TMR2, TMR_SELECT_CHANNEL_1, TRUE);
  tmr_counter_enable(TMR2, TRUE);

  vTaskDelay(pdMS_TO_TICKS(20));
 // tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 125);
  tmr_output_channel_immediately_set(TMR2, TMR_SELECT_CHANNEL_1,FALSE);
  tmr_counter_enable(TMR2, FALSE);
}


void buzzer_on_sound(void)
{
  // tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 125);
  tmr_output_channel_immediately_set(TMR2, TMR_SELECT_CHANNEL_1,FALSE);
  tmr_counter_enable(TMR2, FALSE);


}