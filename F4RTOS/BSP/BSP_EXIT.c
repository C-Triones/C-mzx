#include "BSP_EXIT.h"

/******************************�ⲿ���ú���************************************/
void BSP_GPIO_EXIT_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,EXTITrigger_TypeDef triger,
												u8 PreemptionPriority,u8 SubPriority);
/*****************************************************************************/


/*
***************************************************
��������GPIO_TO_EXTI_PinSource
���ܣ�����ⲿ�ж�������Դ
��ڲ�����	GPIO�����ź�
����ֵ��EXTI_PinSource
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
uint32_t	GPIO_TO_EXTI_PinSource(BSP_GPIOSource_TypeDef* GPIO){
	uint32_t EXTI_PinSource;
	switch(GPIO->Pin){
		case GPIO_Pin_0: 	EXTI_PinSource = EXTI_PinSource0;	break;
		case GPIO_Pin_1: 	EXTI_PinSource = EXTI_PinSource1;	break;
		case GPIO_Pin_2: 	EXTI_PinSource = EXTI_PinSource2;	break;
		case GPIO_Pin_3: 	EXTI_PinSource = EXTI_PinSource3;	break;
		case GPIO_Pin_4: 	EXTI_PinSource = EXTI_PinSource4;	break;
		case GPIO_Pin_5: 	EXTI_PinSource = EXTI_PinSource5;	break;
		case GPIO_Pin_6: 	EXTI_PinSource = EXTI_PinSource6;	break;
		case GPIO_Pin_7: 	EXTI_PinSource = EXTI_PinSource7;	break;
		case GPIO_Pin_8: 	EXTI_PinSource = EXTI_PinSource8;	break;
		case GPIO_Pin_9: 	EXTI_PinSource = EXTI_PinSource9;	break;
		case GPIO_Pin_10: EXTI_PinSource = EXTI_PinSource10;break;
		case GPIO_Pin_11: EXTI_PinSource = EXTI_PinSource11;break;
		case GPIO_Pin_12: EXTI_PinSource = EXTI_PinSource12;break;
		case GPIO_Pin_13: EXTI_PinSource = EXTI_PinSource13;break;
		case GPIO_Pin_14: EXTI_PinSource = EXTI_PinSource14;break;
		case GPIO_Pin_15: EXTI_PinSource = EXTI_PinSource15;break;
	}
	return EXTI_PinSource;
}

/*
***************************************************
��������GPIO_TO_NVIC_IRQChannel
���ܣ����NVIC�ж�ͨ��
��ڲ�����	GPIO�����ź�
����ֵ��NVIC_IRQChannel
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
uint8_t	GPIO_TO_NVIC_IRQChannel(BSP_GPIOSource_TypeDef* GPIO){
	uint8_t NVIC_IRQChannel;
	switch(GPIO->Pin){
		case GPIO_Pin_0: 	NVIC_IRQChannel = EXTI0_IRQn;			break;
		case GPIO_Pin_1: 	NVIC_IRQChannel = EXTI1_IRQn;			break;
		case GPIO_Pin_2: 	NVIC_IRQChannel = EXTI2_IRQn;			break;
		case GPIO_Pin_3: 	NVIC_IRQChannel = EXTI3_IRQn;			break;
		case GPIO_Pin_4: 	NVIC_IRQChannel = EXTI4_IRQn;			break;
		case GPIO_Pin_5: 	NVIC_IRQChannel = EXTI9_5_IRQn;		break;
		case GPIO_Pin_6: 	NVIC_IRQChannel = EXTI9_5_IRQn;		break;
		case GPIO_Pin_7: 	NVIC_IRQChannel = EXTI9_5_IRQn;		break;
		case GPIO_Pin_8: 	NVIC_IRQChannel = EXTI9_5_IRQn;		break;
		case GPIO_Pin_9: 	NVIC_IRQChannel = EXTI9_5_IRQn;		break;
		case GPIO_Pin_10: NVIC_IRQChannel = EXTI15_10_IRQn;	break;
		case GPIO_Pin_11: NVIC_IRQChannel = EXTI15_10_IRQn;	break;
		case GPIO_Pin_12: NVIC_IRQChannel = EXTI15_10_IRQn;	break;
		case GPIO_Pin_13: NVIC_IRQChannel = EXTI15_10_IRQn;	break;
		case GPIO_Pin_14: NVIC_IRQChannel = EXTI15_10_IRQn;	break;
		case GPIO_Pin_15: NVIC_IRQChannel = EXTI15_10_IRQn;	break;
	}
	return NVIC_IRQChannel;	
}

/*
***************************************************
��������GPIO_TO_EXTI_PortSource
���ܣ����EXTI�ܽ���Դ
��ڲ�����	GPIO�����ź�
����ֵ��EXTI_PortSource
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
uint8_t GPIO_TO_EXTI_PortSource(BSP_GPIOSource_TypeDef* GPIO){
	uint8_t EXTI_PortSource;
	if 			(GPIO->GPIOx==GPIOA)	EXTI_PortSource = EXTI_PortSourceGPIOA;	
	else if (GPIO->GPIOx==GPIOB) 	EXTI_PortSource = EXTI_PortSourceGPIOB;
	else if (GPIO->GPIOx==GPIOC) 	EXTI_PortSource = EXTI_PortSourceGPIOC;
	else if (GPIO->GPIOx==GPIOD) 	EXTI_PortSource = EXTI_PortSourceGPIOD;
	else if (GPIO->GPIOx==GPIOE) 	EXTI_PortSource = EXTI_PortSourceGPIOE;
	else if (GPIO->GPIOx==GPIOF) 	EXTI_PortSource = EXTI_PortSourceGPIOF;
	else if (GPIO->GPIOx==GPIOG) 	EXTI_PortSource = EXTI_PortSourceGPIOG;
	else if (GPIO->GPIOx==GPIOH) 	EXTI_PortSource = EXTI_PortSourceGPIOH;
	else if (GPIO->GPIOx==GPIOI) 	EXTI_PortSource = EXTI_PortSourceGPIOI;
	return EXTI_PortSource;
}

/*
***************************************************
��������BSP_GPIO_EXIT_Init
���ܣ������ⲿ�ж�
��ڲ�����	GPIO�����ź�
					triger��������ʽ��EXTI_Trigger_Rising��EXTI_Trigger_Falling��EXTI_Trigger_Rising_Falling��
					PreemptionPriority����ռ���ȼ�
					SubPriority�������ȼ�
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_GPIO_EXIT_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,EXTITrigger_TypeDef triger,u8 PreemptionPriority,u8 SubPriority){
	NVIC_InitTypeDef	NVIC_InitStructure;
	EXTI_InitTypeDef 	EXTI_InitStructure;
	
	BSP_GPIO_Init(BSP_GPIO,GPIO_Mode_IPD);  //��ʼ������

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	/* GPIO���ӵ��ж��� */
	SYSCFG_EXTILineConfig( GPIO_TO_EXTI_PortSource(BSP_GPIO) , GPIO_TO_EXTI_PinSource(BSP_GPIO));
	
	/* ����EXTI_Line */
	EXTI_InitStructure.EXTI_Line = (uint32_t)BSP_GPIO->Pin;	//LINE
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = triger; 					//�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//ʹ��LINE
  EXTI_Init(&EXTI_InitStructure);	//����
	
	/* ����NVIC �ж����ȼ����� */
	NVIC_InitStructure.NVIC_IRQChannel = GPIO_TO_NVIC_IRQChannel(BSP_GPIO);	//�ⲿ�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;	//��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;								//�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);	//����
}
