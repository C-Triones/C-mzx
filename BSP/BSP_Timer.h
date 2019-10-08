#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "stm32f4xx.h"
#include "stm32f4xx.h"
#include "stdlib.h"
#include "stdio.h"

#include "BSP_GPIO.h"

/*************************************************************
TIM1, TIM8->TIM11��ʱ��Ƶ��ΪAPB2ʱ�ӵ�2������168MHz
TIM2->TIM7, TIM12->TIM14��ʱ��Ƶ��ΪAPB1ʱ�ӵ�2������84MHz
*************************************************************/

typedef struct
{
	BSP_GPIOSource_TypeDef *ICAP_GPIO;	//���벶��
	uint16_t TIM_ICPolarity;						//���벶���ԣ�TIM_ICPolarity_Rising��TIM_ICPolarity_Falling��TIM_ICPolarity_BothEdge
}BSP_TIM_ICAP_TypeDef;

void BSP_TIM_RCC_Init(TIM_TypeDef* BSP_TIMx);
void BSP_TIM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler);
void BSP_TIM_INT_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,u8 PreemptionPriority,u8 SubPriority);
uint8_t	TIM_TO_GPIO_AF(TIM_TypeDef* BSP_TIMx);
void BSP_TIM_ICAP_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_TIM_ICAP_TypeDef* ICAP1,
											BSP_TIM_ICAP_TypeDef* ICAP2,
											BSP_TIM_ICAP_TypeDef* ICAP3,
											BSP_TIM_ICAP_TypeDef* ICAP4,
											u8 PreemptionPriority, u8 SubPriority);
#endif
