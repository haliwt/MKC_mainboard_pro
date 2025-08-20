#include "bsp.h"

void cooler_open(void)
{
   COOLER_GPIO_PORT->scr = COOLER_PIN ; //output gpio is "1"

}
void cooler_close(void)
{
	COOLER_GPIO_PORT->clr = COOLER_PIN ; //output gpio is "0"


}

