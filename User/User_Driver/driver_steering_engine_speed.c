#include "driver.h"



/*
 * ��������TIM3_GPIO_Config
 * ����  ������TIM3�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM23_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /********TIM3���Ÿ���********/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	/*GPIO����Ϊ�����������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	/*GPIO����Ϊ�����������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*
 * �������TTIM23_PWM_Init
 * ����  ������TIM23�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM23_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//�ϵ��õ����ֹ
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 260;  //צ��1      
	u16 CCR4_Val = 250;  //צ��2
	u16 CCR5_Val = 120;  //���


	TIM_TimeBaseStructure.TIM_Period = (3200 - 1); 
	TIM_TimeBaseStructure.TIM_Prescaler = (450 - 1);
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//���ö�ʱ������ģʽ�����ϼ���ģʽ		
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/*����ΪPWMģʽ1*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/*����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ*/	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
 
 
	/* ��������ֵ�������������������ֵʱ����ƽ�������� */
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	/*ʹ��ͨ��1*/
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/*����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM*/
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  
	/*ʹ��ͨ��2*/
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/* ��������ֵ�������������������ֵʱ����ƽ�������� */
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val; 
	/*ʹ��ͨ��3*/
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/*����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM*/
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  
	/*ʹ��ͨ��4*/
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/*����ͨ��1�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM*/
	TIM_OCInitStructure.TIM_Pulse = CCR5_Val;	  
	/*ʹ��ͨ��1*/
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	  
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/*ʹ��TIM2���ؼĴ���ARR*/
	TIM_ARRPreloadConfig(TIM2, ENABLE);		
	/*ʹ��TIM3���ؼĴ���ARR*/
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 

  /*ʹ�ܶ�ʱ��2*/
	TIM_Cmd(TIM2, ENABLE);
	/*ʹ�ܶ�ʱ��3*/
	TIM_Cmd(TIM3, ENABLE);              
}

void driver_InitSteeringEngineSpeed(void)
{
	TIM23_GPIO_Config();
	TIM23_PWM_Init();
}

