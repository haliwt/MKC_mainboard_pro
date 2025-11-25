#include "bsp.h"


void door_state_hanlder(void)
{
  if(HAL_READ_VALUE()==0){//open door

     LED_TRIP_ON();

  }
  else{
     LED_TRIP_OFF();

  }
}

