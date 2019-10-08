#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "stm32f10x.h"
#include <stdlib.h>
#include <stdio.h>

#include "BSP_GPIO.h"

typedef struct
{
	BSP_GPIOSource_TypeDef *ICAP_GPIO;	//输入捕获
	uint16_t TIM_ICPolarity;						//输入捕获极性：TIM_ICPolarity_Rising；TIM_ICPolarity_Falling；TIM_ICPolarity_BothEdge
}BSP_TIM_ICAP_TypeDef;

void BSP_TIM_RCC_Init(TIM_TypeDef* BSP_TIMx);
void BSP_TIM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler);
void BSP_TIM_INT_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,u8 PreemptionPriority,u8 SubPriority);
uint32_t	TIM_TO_GPIO_PinRemap(TIM_TypeDef* BSP_TIMx);
void BSP_TIM_ICAP_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_TIM_ICAP_TypeDef* ICAP1,
											BSP_TIM_ICAP_TypeDef* ICAP2,
											BSP_TIM_ICAP_TypeDef* ICAP3,
											BSP_TIM_ICAP_TypeDef* ICAP4,
											u8 PreemptionPriority, u8 SubPriority);
#endif
