#ifndef __BSP_HAL_H
#define __BSP_HAL_H
#include "at32f425.h"

#define HAL_READ_VALUE()   gpio_input_data_bit_read(HAL_GPIO_PORT,HAL_PIN) //((HAL_GPIO_PORT->idt & HAL_PIN) ? 1: 0)

#define LED_TRIP_ON()   gpio_bits_set(LED_DOOR_GPIO_PORT,LED_DOOR_PIN)

#define LED_TRIP_OFF()    gpio_bits_reset(LED_DOOR_GPIO_PORT,LED_DOOR_PIN)


void door_state_hanlder(void);


#endif 

