#include "BSP_PWM.h"


/******************************�ⲿ���ú���************************************/
void BSP_TIM_PWM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_GPIOSource_TypeDef* GPIO_PWM1,
											BSP_GPIOSource_TypeDef* GPIO_PWM2,
											BSP_GPIOSource_TypeDef* GPIO_PWM3,
											BSP_GPIOSource_TypeDef* GPIO_PWM4);
/*****************************************************************************/

#define NULL 0

/*
***************************************************
��������BSP_TIM_PWM_Init
���ܣ�����TIMx��ʱ��PWM�������
��ڲ�����	BSP_TIMx����ʱ����		 ��������TIM1��TIM8�����߼���ʱ����
					Period���Զ���װֵ
					Prescaler��ʱ��Ԥ��Ƶ��
					GPIO_PWM1��PWM1���źţ���ʹ��ʱ����NULL�����ݲ�����
					GPIO_PWM2��PWM2���źţ���ʹ��ʱ����NULL�����ݲ�����
					GPIO_PWM3��PWM3���źţ���ʹ��ʱ����NULL�����ݲ�����
					GPIO_PWM4��PWM4���źţ���ʹ��ʱ����NULL�����ݲ�����
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��	TIM9->TIM11 ��ʱ��Ƶ��ΪAPB2ʱ�ӵ�2������168MHz
			TIM2->TIM7, TIM12->TIM14 ��ʱ��Ƶ��ΪAPB1ʱ�ӵ�2������84MHz
			
			TIM2��TIM5��32λ��װ��ֵ
			TIM3��TIM4��TIM6��TIM7��TIM9->TIM14��16λ��װ��ֵ
			
			TIM2->TIM5 PWMͨ����4��
			TIM9��TIM12 PWMͨ����2��
			TIM10��TIM11��TIM13��TIM14 PWMͨ����1��
***************************************************
*/
void BSP_TIM_PWM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_GPIOSource_TypeDef* GPIO_PWM1,
											BSP_GPIOSource_TypeDef* GPIO_PWM2,
											BSP_GPIOSource_TypeDef* GPIO_PWM3,
											BSP_GPIOSource_TypeDef* GPIO_PWM4){
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	
	BSP_TIM_RCC_Init(BSP_TIMx);	//ʹ�ܶ�ʱ��TIMxʱ��
	
	/* ����PWM������� */
	if(GPIO_PWM1 != NULL){
		BSP_GPIO_Init(GPIO_PWM1,GPIO_Mode_AF_PP);	//����PWM1����Ϊ��������ģʽ
		GPIO_PinAFConfig(GPIO_PWM1->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM1),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM1���Ÿ���Ϊ��ʱ��TIMx
	}
	if(GPIO_PWM2 != NULL){
		BSP_GPIO_Init(GPIO_PWM2,GPIO_Mode_AF_PP);	//����PWM2����Ϊ��������ģʽ
		GPIO_PinAFConfig(GPIO_PWM2->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM2),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM2���Ÿ���Ϊ��ʱ��TIMx
	}
	if(GPIO_PWM3 != NULL){
		BSP_GPIO_Init(GPIO_PWM3,GPIO_Mode_AF_PP);	//����PWM3����Ϊ��������ģʽ
		GPIO_PinAFConfig(GPIO_PWM3->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM3),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM3���Ÿ���Ϊ��ʱ��TIMx
	}
	if(GPIO_PWM4 != NULL){
		BSP_GPIO_Init(GPIO_PWM4,GPIO_Mode_AF_PP);	//����PWM4����Ϊ��������ģʽ
		GPIO_PinAFConfig(GPIO_PWM4->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM4),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM4���Ÿ���Ϊ��ʱ��TIMx
	}
	
	/* ���ö�ʱ��TIMx */
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  	//��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = Period;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseStructure);//��ʼ����ʱ��TIMx
	
	/* ��ʼ��TIMx ��ͨ��PWMģʽ */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
	if(GPIO_PWM1 != NULL){
		TIM_OC1Init(BSP_TIMx, &TIM_OCInitStructure);  		//����ָ���Ĳ�����ʼ������TIMx OC1
		TIM_OC1PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	}
	if(GPIO_PWM2 != NULL){
		TIM_OC2Init(BSP_TIMx, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIMx OC2
		TIM_OC2PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	}
	if(GPIO_PWM3 != NULL){
		TIM_OC3Init(BSP_TIMx, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIMx OC3
		TIM_OC3PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//ʹ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���
	}
	if(GPIO_PWM4 != NULL){
		TIM_OC4Init(BSP_TIMx, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIMx OC4
		TIM_OC4PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//ʹ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���
	}
	
	TIM_ARRPreloadConfig(BSP_TIMx,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(BSP_TIMx, ENABLE);  //ʹ��TIMx��ʱ��
	TIM_CtrlPWMOutputs(BSP_TIMx,ENABLE);//TIMx PWM���ʹ��
}



