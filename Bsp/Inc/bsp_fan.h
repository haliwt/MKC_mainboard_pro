#ifndef __BSP_FAN_H
#define __BSP_FAN_H
#include "at32f425.h"


void fan_group_open(void);
void fan_group_close(void);

void fan_oneself_open(void);
void fan_oneself_close(void);


#endif 

