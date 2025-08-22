#ifndef __BSP_MESSAGE_H
#define __BSP_MESSAGE_H
#include "at32f425.h"


 void responseCmd_fun(uint8_t cmd,uint8_t fun_code);

void sendData_to_dispBoard(uint8_t notice,uint8_t data);


#endif 

