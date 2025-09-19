#ifndef __BSP_FAN_H
#define __BSP_FAN_H
#include "at32f425.h"


void fan_24v_group_open(void);
void fan_24v_group_close(void);

void fan_12v_open(void);
void fan_12v_close(void);

void fan_12v_enable(void);
void fan_12v_disable(void);





#endif 

