#ifndef __BSP_EXIT_H
#define __BSP_EXIT_H

#include "stm32f4xx.h"
#include "stdlib.h"
#include "stdio.h"

#include "BSP_GPIO.h"

void BSP_GPIO_EXIT_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,EXTITrigger_TypeDef triger,u8 PreemptionPriority,u8 SubPriority);
uint8_t GPIO_TO_EXTI_PortSource(BSP_GPIOSource_TypeDef* GPIO);
uint32_t GPIO_TO_EXTI_PinSource(BSP_GPIOSource_TypeDef* GPIO);


#endif
