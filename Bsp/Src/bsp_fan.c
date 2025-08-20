#include "bsp.h"


void fan_group_open(void)
{
   FAN_GROUP_GPIO_PORT->scr = FAN_GROUP_PIN;

}
void fan_group_close(void)
{
   
FAN_GROUP_GPIO_PORT->clr = FAN_GROUP_PIN;

}


void fan_singal_open(void)
{
  FAN_CTL_GPIO_PORT ->scr = FAN_CTL_PIN ;

}
void fan_singal_close(void)
{
	FAN_CTL_GPIO_PORT ->clr = FAN_CTL_PIN ;


}



