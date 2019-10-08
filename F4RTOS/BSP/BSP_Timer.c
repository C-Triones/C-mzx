#include "BSP_Timer.h"

/*************************************************************
TIM1, TIM8->TIM11 ��ʱ��Ƶ��ΪAPB2ʱ�ӵ�2������168MHz
TIM2->TIM7, TIM12->TIM14 ��ʱ��Ƶ��ΪAPB1ʱ�ӵ�2������84MHz

TIM2��TIM5��32λ��װ��ֵ
TIM1��TIM3��TIM4��TIM6->TIM8��TIM9->TIM14��16λ��װ��ֵ
*************************************************************/

/******************************�ⲿ���ú���************************************/
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
/*****************************************************************************/


/*
***************************************************
��������BSP_TIM_RCC_Init
���ܣ�����TIMx��ʱ��ʱ��
��ڲ�����	BSP_TIMx����ʱ����
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_TIM_RCC_Init(TIM_TypeDef* BSP_TIMx){
	if(BSP_TIMx == TIM1)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);		//ʹ�ܶ�ʱ��TIM1��ʱ��
	else if(BSP_TIMx == TIM2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//ʹ�ܶ�ʱ��TIM2��ʱ��
	else if(BSP_TIMx == TIM3)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//ʹ�ܶ�ʱ��TIM3��ʱ��
	else if(BSP_TIMx == TIM4)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		//ʹ�ܶ�ʱ��TIM4��ʱ��
	else if(BSP_TIMx == TIM5)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		//ʹ�ܶ�ʱ��TIM5��ʱ��
	else if(BSP_TIMx == TIM6)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);		//ʹ�ܶ�ʱ��TIM6��ʱ��
	else if(BSP_TIMx == TIM7)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);		//ʹ�ܶ�ʱ��TIM7��ʱ��
	else if(BSP_TIMx == TIM8)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);		//ʹ�ܶ�ʱ��TIM8��ʱ��
	else if(BSP_TIMx == TIM9)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);		//ʹ�ܶ�ʱ��TIM9��ʱ��
	else if(BSP_TIMx == TIM10)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);	//ʹ�ܶ�ʱ��TIM10��ʱ��
	else if(BSP_TIMx == TIM11)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);	//ʹ�ܶ�ʱ��TIM11��ʱ��
	else if(BSP_TIMx == TIM12)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);	//ʹ�ܶ�ʱ��TIM12��ʱ��
	else if(BSP_TIMx == TIM13)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);	//ʹ�ܶ�ʱ��TIM13��ʱ��
	else if(BSP_TIMx == TIM14)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);	//ʹ�ܶ�ʱ��TIM14��ʱ��
}

/*
***************************************************
��������TIM_TO_NVIC_IRQChannel
���ܣ�����TIMx��ʱ��NVIC�ж�ͨ��
��ڲ�����	BSP_TIMx����ʱ���ţ�������TIM1��TIM8�����߼���ʱ����
����ֵ��NVIC_IRQChannel
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
uint8_t	TIM_TO_NVIC_IRQChannel(TIM_TypeDef* BSP_TIMx){
	uint8_t NVIC_IRQChannel;
	
	if(BSP_TIMx == TIM2)				
		NVIC_IRQChannel = TIM2_IRQn;
	else if(BSP_TIMx == TIM3)		
		NVIC_IRQChannel = TIM3_IRQn;
	else if(BSP_TIMx == TIM4)		
		NVIC_IRQChannel = TIM4_IRQn;
	else if(BSP_TIMx == TIM5)		
		NVIC_IRQChannel = TIM5_IRQn;
	else if(BSP_TIMx == TIM6)		
		NVIC_IRQChannel = TIM6_DAC_IRQn;
	else if(BSP_TIMx == TIM7)		
		NVIC_IRQChannel = TIM7_IRQn;
	else if(BSP_TIMx == TIM9)		
		NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	else if(BSP_TIMx == TIM10)	
		NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	else if(BSP_TIMx == TIM11)	
		NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn;
	else if(BSP_TIMx == TIM12)	
		NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
	else if(BSP_TIMx == TIM13)	
		NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	else if(BSP_TIMx == TIM14)	
		NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;
	else if(BSP_TIMx == TIM1)   
		NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	else if(BSP_TIMx == TIM8)   
		NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	return NVIC_IRQChannel;	
}

/*
***************************************************
��������TIM_TO_GPIO_AF
���ܣ����TIMx��ʱ��GPIO_AF
��ڲ�����	BSP_TIMx����ʱ���ţ�������TIM1��TIM8�����߼���ʱ����
����ֵ��GPIO_AF
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t	TIM_TO_GPIO_AF(TIM_TypeDef* BSP_TIMx){
	uint8_t GPIO_AF;
	
	if(BSP_TIMx == TIM1)				
		GPIO_AF = GPIO_AF_TIM1;
	else if(BSP_TIMx == TIM2)		
		GPIO_AF = GPIO_AF_TIM2;
	else if(BSP_TIMx == TIM3)		
		GPIO_AF = GPIO_AF_TIM3;
	else if(BSP_TIMx == TIM4)		
		GPIO_AF = GPIO_AF_TIM4;
	else if(BSP_TIMx == TIM5)		
		GPIO_AF = GPIO_AF_TIM5;
	else if(BSP_TIMx == TIM8)		
		GPIO_AF = GPIO_AF_TIM8;
	else if(BSP_TIMx == TIM9)		
		GPIO_AF = GPIO_AF_TIM9;
	else if(BSP_TIMx == TIM10)	
		GPIO_AF = GPIO_AF_TIM10;
	else if(BSP_TIMx == TIM11)	
		GPIO_AF = GPIO_AF_TIM11;
	else if(BSP_TIMx == TIM12)	
		GPIO_AF = GPIO_AF_TIM12;
	else if(BSP_TIMx == TIM13)	
		GPIO_AF = GPIO_AF_TIM13;
	else if(BSP_TIMx == TIM14)	
		GPIO_AF = GPIO_AF_TIM14;
	
	return GPIO_AF;	
}

/*
***************************************************
��������BSP_TIM_Init
���ܣ�����TIMx��ʱ��
��ڲ�����	BSP_TIMx����ʱ���ţ�������TIM1��TIM8�����߼���ʱ����
					Period���Զ���װֵ
					Prescaler��ʱ��Ԥ��Ƶ��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_TIM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	BSP_TIM_RCC_Init(BSP_TIMx);		//ʹ�ܶ�ʱ��TIMxʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period 				= Period; 			//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler 		= Prescaler;  	//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode 	= TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseInitStructure);
	
	TIM_ARRPreloadConfig(BSP_TIMx, ENABLE);	
	TIM_Cmd(BSP_TIMx,ENABLE); 		//ʹ�ܶ�ʱ��TIMx	
}

/*
***************************************************
��������BSP_TIM_INT_Init
���ܣ�����TIMx��ʱ���ж�
��ڲ�����	BSP_TIMx����ʱ���ţ�������TIM1��TIM8�����߼���ʱ����
					Period���Զ���װֵ
					Prescaler��ʱ��Ԥ��Ƶ��
					PreemptionPriority����ռ���ȼ�
					SubPriority�������ȼ�
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_TIM_INT_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,u8 PreemptionPriority,u8 SubPriority){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	BSP_TIM_RCC_Init(BSP_TIMx);		//ʹ�ܶ�ʱ��TIMxʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period 				= Period; 			//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler 		= Prescaler;  	//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode 	= TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(BSP_TIMx,TIM_IT_Update,ENABLE); //����ʱ��TIMx�����ж�
	TIM_Cmd(BSP_TIMx,ENABLE); 		//ʹ�ܶ�ʱ��TIMx
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM_TO_NVIC_IRQChannel(BSP_TIMx); //��ʱ��TIMx�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority; //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);		
}
	
/*
***************************************************
��������BSP_TIM_ICAP_Init
���ܣ����ö�ʱ��TIMx�������
��ڲ�����	BSP_TIMx����ʱ����		 ��������TIM1��TIM8�����߼���ʱ����
					Period���Զ���װֵ
					Prescaler��ʱ��Ԥ��Ƶ��
					GPIO_ICAP1��ICAP1���źţ���ʹ��ʱ����NULL�����ݲ�����
					GPIO_ICAP2��ICAP2���źţ���ʹ��ʱ����NULL�����ݲ�����
					GPIO_ICAP3��ICAP3���źţ���ʹ��ʱ����NULL�����ݲ�����
					GPIO_ICAP4��ICAP4���źţ���ʹ��ʱ����NULL�����ݲ�����
					PreemptionPriority����ռ���ȼ�
					SubPriority�������ȼ�
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_TIM_ICAP_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_TIM_ICAP_TypeDef* ICAP1,
											BSP_TIM_ICAP_TypeDef* ICAP2,
											BSP_TIM_ICAP_TypeDef* ICAP3,
											BSP_TIM_ICAP_TypeDef* ICAP4,
											u8 PreemptionPriority, u8 SubPriority){
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_ICInitTypeDef					TIM_ICInitStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;
	uint16_t TIM_IT;
	
	/*************��ʼ��TIMxʱ��***************/
	BSP_TIM_RCC_Init(BSP_TIMx);	//ʹ�ܶ�ʱ��TIMxʱ��
	
	/*************����ICAP�������***************/
	if(ICAP1 != NULL){
		BSP_GPIO_Init(ICAP1->ICAP_GPIO,GPIO_Mode_AF_PP);	//����ICAP1����Ϊ��������ģʽ
		GPIO_PinAFConfig(ICAP1->ICAP_GPIO->GPIOx,GPIO_Pin_TO_GPIO_PinSource(ICAP1->ICAP_GPIO),TIM_TO_GPIO_AF(BSP_TIMx));	//ICAP1���Ÿ���Ϊ��ʱ��TIMx
	}
	if(ICAP2 != NULL){
		BSP_GPIO_Init(ICAP2->ICAP_GPIO,GPIO_Mode_AF_PP);	//����ICAP2����Ϊ��������ģʽ
		GPIO_PinAFConfig(ICAP2->ICAP_GPIO->GPIOx,GPIO_Pin_TO_GPIO_PinSource(ICAP2->ICAP_GPIO),TIM_TO_GPIO_AF(BSP_TIMx));	//ICAP2���Ÿ���Ϊ��ʱ��TIMx
	}
	if(ICAP3 != NULL){
		BSP_GPIO_Init(ICAP1->ICAP_GPIO,GPIO_Mode_AF_PP);	//����ICAP3����Ϊ��������ģʽ
		GPIO_PinAFConfig(ICAP3->ICAP_GPIO->GPIOx,GPIO_Pin_TO_GPIO_PinSource(ICAP3->ICAP_GPIO),TIM_TO_GPIO_AF(BSP_TIMx));	//ICAP3���Ÿ���Ϊ��ʱ��TIMx
	}
	if(ICAP4 != NULL){
		BSP_GPIO_Init(ICAP4->ICAP_GPIO,GPIO_Mode_AF_PP);	//����ICAP4����Ϊ��������ģʽ
		GPIO_PinAFConfig(ICAP4->ICAP_GPIO->GPIOx,GPIO_Pin_TO_GPIO_PinSource(ICAP4->ICAP_GPIO),TIM_TO_GPIO_AF(BSP_TIMx));	//ICAP4���Ÿ���Ϊ��ʱ��TIMx
	}
	
	/*************���ö�ʱ��TIMx***************/
	TIM_TimeBaseStructure.TIM_Prescaler = Period;  	//��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = Prescaler;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseStructure);//��ʼ����ʱ��TIMx
	
	
	/*************��ʼ��TIMx��ͨ�������벶�����***************/
	if(ICAP1 != NULL){
		TIM_IT |= TIM_IT_CC1;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_1; 						//ѡ������� IC1ӳ�䵽TI1��
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//�����ز���
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//���������Ƶ,����Ƶ 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//���������˲��� ���˲�
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	if(ICAP2 != NULL){
		TIM_IT |= TIM_IT_CC2;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_2; 						//ѡ������� IC2ӳ�䵽TI2��
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//�����ز���
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI2��
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//���������Ƶ,����Ƶ 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//���������˲��� ���˲�
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	if(ICAP3 != NULL){
		TIM_IT |= TIM_IT_CC3;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_3; 						//ѡ������� IC3ӳ�䵽TI3��
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//�����ز���
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI3��
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//���������Ƶ,����Ƶ 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//���������˲��� ���˲�
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	if(ICAP4 != NULL){
		TIM_IT |= TIM_IT_CC4;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_4; 						//ѡ������� IC4ӳ�䵽TI4��
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//�����ز���
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI4��
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//���������Ƶ,����Ƶ 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//���������˲��� ���˲�
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	
	TIM_ITConfig(TIM5,TIM_IT_Update | TIM_IT,ENABLE);//��������ж� ,����ͨ�������ж�
	TIM_Cmd(BSP_TIMx, ENABLE);  //ʹ��TIMx��ʱ��
	
	
	/*********************����NVIC�Ĵ���***********************/
	if( (PreemptionPriority != 0xff) && (SubPriority != 0xff) ){
		NVIC_InitStructure.NVIC_IRQChannel = TIM_TO_NVIC_IRQChannel(BSP_TIMx);	//��ʱ��TIMx�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
	}
}
