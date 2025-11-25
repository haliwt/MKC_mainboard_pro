#include "bsp.h"


void fan_24v_group_open(void)
{
   FAN_24V_CTL_GPIO_PORT->scr = FAN_24V_CTL_PIN;

}
void fan_24v_group_close(void)
{
   
   FAN_24V_CTL_GPIO_PORT->clr = FAN_24V_CTL_PIN;

}

void fan_12v_open(void)
{

	FAN_12V_CTL_GPIO_PORT->scr = FAN_12V_CTL_PIN;

}
void fan_12v_close(void)
{

	FAN_12V_CTL_GPIO_PORT->clr = FAN_12V_CTL_PIN;
}

void fan_12v_enable(void)
{
	OUTPUT_12V_ENABLE_GPIO_PORT->scr = OUTPUT_12V_ENABLE_PIN;

}
void fan_12v_disable(void)
{
	OUTPUT_12V_ENABLE_GPIO_PORT->clr = OUTPUT_12V_ENABLE_PIN;



}






