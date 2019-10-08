#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H
#include "BSP_GPIO.h"

#define LED PFout(9)

void Led_Init(void);
void Led_On(void);





#endif
