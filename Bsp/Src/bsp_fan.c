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
	FAN_ENABLE_12V_GPIO_PORT->scr = FAN_ENABLE_12V_PIN;

}
void fan_12v_disable(void)
{
	FAN_ENABLE_12V_GPIO_PORT->clr = FAN_ENABLE_12V_PIN;



}






