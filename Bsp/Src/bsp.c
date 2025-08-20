#include "bsp.h"

PROCESS_TYPEDEF g_pro;

void bsp_init(void)
{
    // Initialize the process structure
    g_pro.rx_length = 0;
    g_pro.rx_complete_flag = 0;

    // Initialize other BSP components
 
    
    // Additional initialization code can be added here
}

