#ifndef __PWM_H
#define __PWM_H

#include "stm32f4xx.h"
#include "stdlib.h"
#include "stdio.h"

#include "BSP_GPIO.h"
#include "BSP_Timer.h"

/*************************************************************
TIM1, TIM8->TIM11��ʱ��Ƶ��ΪAPB2ʱ�ӵ�2������168MHz
TIM2->TIM7, TIM12->TIM14��ʱ��Ƶ��ΪAPB1ʱ�ӵ�2������84MHz
TIM2->TIM5 PWMͨ����4��
TIM9��TIM12 PWMͨ����2��
TIM10��TIM11��TIM13��TIM14 PWMͨ����1��
*************************************************************/

/***********TIMx PWMռ�ձȼĴ���**********/

//��ʱ��TIM2 PWMռ�ձȼĴ���
#define TIM2_PWM1 TIM2->CCR1
#define TIM2_PWM2 TIM2->CCR2
#define TIM2_PWM3 TIM2->CCR3
#define TIM2_PWM4 TIM2->CCR4

//��ʱ��TIM3 PWMռ�ձȼĴ���
#define TIM3_PWM1 TIM3->CCR1
#define TIM3_PWM2 TIM3->CCR2
#define TIM3_PWM3 TIM3->CCR3
#define TIM3_PWM4 TIM3->CCR4

//��ʱ��TIM4 PWMռ�ձȼĴ���
#define TIM4_PWM1 TIM4->CCR1
#define TIM4_PWM2 TIM4->CCR2
#define TIM4_PWM3 TIM4->CCR3
#define TIM4_PWM4 TIM4->CCR4

//��ʱ��TIM5 PWMռ�ձȼĴ���
#define TIM5_PWM1 TIM5->CCR1
#define TIM5_PWM2 TIM5->CCR2
#define TIM5_PWM3 TIM5->CCR3
#define TIM5_PWM4 TIM5->CCR4

//��ʱ��TIM9 PWMռ�ձȼĴ���
#define TIM9_PWM1 TIM9->CCR1
#define TIM9_PWM2 TIM9->CCR2

//��ʱ��TIM10 PWMռ�ձȼĴ���
#define TIM10_PWM1 TIM10->CCR1

//��ʱ��TIM11 PWMռ�ձȼĴ���
#define TIM11_PWM1 TIM11->CCR1

//��ʱ��TIM12 PWMռ�ձȼĴ���
#define TIM12_PWM1 TIM12->CCR1
#define TIM12_PWM2 TIM12->CCR2

//��ʱ��TIM13 PWMռ�ձȼĴ���
#define TIM13_PWM1 TIM13->CCR1

//��ʱ��TIM14 PWMռ�ձȼĴ���
#define TIM14_PWM1 TIM14->CCR1

void BSP_TIM_PWM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_GPIOSource_TypeDef* GPIO_PWM1,
											BSP_GPIOSource_TypeDef* GPIO_PWM2,
											BSP_GPIOSource_TypeDef* GPIO_PWM3,
											BSP_GPIOSource_TypeDef* GPIO_PWM4);

#endif
