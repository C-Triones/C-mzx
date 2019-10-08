#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h"
#include <stdlib.h>
#include <stdio.h>

#include "BSP_GPIO.h"

void BSP_GPIO_EXTI_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,EXTITrigger_TypeDef triger,u8 PreemptionPriority,u8 SubPriority);
uint32_t GPIO_TO_EXTI_PinSource(BSP_GPIOSource_TypeDef* GPIO);
uint8_t	GPIO_TO_NVIC_IRQChannel(BSP_GPIOSource_TypeDef* GPIO);
uint8_t GPIO_TO_EXTI_PortSource(BSP_GPIOSource_TypeDef* GPIO);
uint32_t GPIO_TO_EXTI_Line(BSP_GPIOSource_TypeDef* GPIO);
#endif
