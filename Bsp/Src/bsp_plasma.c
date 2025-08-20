#include "bsp.h"


void plasma_open(void)
{
	PLASMA_GPIO_PORT ->scr = PLASMA_PIN;

}
void plasma_close(void)
{
	PLASMA_GPIO_PORT ->clr = PLASMA_PIN;

}

