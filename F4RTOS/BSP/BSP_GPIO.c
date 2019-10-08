#include "BSP_GPIO.h"
#include "BSP_GPIO_Define.h"

/******************************�ⲿ���ú���************************************/
uint8_t GPIO_Pin_TO_GPIO_PinSource(BSP_GPIOSource_TypeDef* BSP_GPIO);
void GPIO_Pin_TO_PinAFConfig(BSP_GPIOSource_TypeDef* BSP_GPIO,uint8_t GPIO_AF);
void BSP_GPIO_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,BSP_GPIOMode_TypeDef GPIO_Mode);
/*****************************************************************************/


/*
***************************************************
��������BSP_GPIO_RCC_Init
���ܣ�����GPIO�˿�ʱ��
��ڲ�����	BSP_GPIO��GPIO�����ź�
����ֵ����
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
void BSP_GPIO_RCC_Init(BSP_GPIOSource_TypeDef* BSP_GPIO){
	uint32_t GPIO_RCC;
	
	if(BSP_GPIO->GPIOx == GPIOA)			
		GPIO_RCC = RCC_AHB1Periph_GPIOA;
	else if(BSP_GPIO->GPIOx == GPIOB)	
		GPIO_RCC = RCC_AHB1Periph_GPIOB;
	else if(BSP_GPIO->GPIOx == GPIOC)	
		GPIO_RCC = RCC_AHB1Periph_GPIOC;
	else if(BSP_GPIO->GPIOx == GPIOD)	
		GPIO_RCC = RCC_AHB1Periph_GPIOD;
	else if(BSP_GPIO->GPIOx == GPIOE)	
		GPIO_RCC = RCC_AHB1Periph_GPIOE;
	else if(BSP_GPIO->GPIOx == GPIOF)
		GPIO_RCC = RCC_AHB1Periph_GPIOF;
	else if(BSP_GPIO->GPIOx == GPIOG)	
		GPIO_RCC = RCC_AHB1Periph_GPIOG;
	else if(BSP_GPIO->GPIOx == GPIOH)	
		GPIO_RCC = RCC_AHB1Periph_GPIOH;
	else if(BSP_GPIO->GPIOx == GPIOI)	
		GPIO_RCC = RCC_AHB1Periph_GPIOI;
	
	RCC_AHB1PeriphClockCmd(GPIO_RCC,ENABLE);
}

/*
***************************************************
��������GPIO_Pin_TO_GPIO_PinSource
���ܣ�����GPIO������Դ
��ڲ�����	BSP_GPIO��GPIO�����ź�
����ֵ��GPIO_PinSource
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t GPIO_Pin_TO_GPIO_PinSource(BSP_GPIOSource_TypeDef* BSP_GPIO){
	uint8_t GPIO_PinSource;
	switch(BSP_GPIO->Pin){
		case GPIO_Pin_0: 	GPIO_PinSource = GPIO_PinSource0;	break;
		case GPIO_Pin_1: 	GPIO_PinSource = GPIO_PinSource1;	break;
		case GPIO_Pin_2: 	GPIO_PinSource = GPIO_PinSource2;	break;
		case GPIO_Pin_3: 	GPIO_PinSource = GPIO_PinSource3;	break;
		case GPIO_Pin_4: 	GPIO_PinSource = GPIO_PinSource4;	break;
		case GPIO_Pin_5: 	GPIO_PinSource = GPIO_PinSource5;	break;
		case GPIO_Pin_6: 	GPIO_PinSource = GPIO_PinSource6;	break;
		case GPIO_Pin_7: 	GPIO_PinSource = GPIO_PinSource7;	break;
		case GPIO_Pin_8: 	GPIO_PinSource = GPIO_PinSource8;	break;
		case GPIO_Pin_9: 	GPIO_PinSource = GPIO_PinSource9;	break;
		case GPIO_Pin_10: GPIO_PinSource = GPIO_PinSource10;break;
		case GPIO_Pin_11: GPIO_PinSource = GPIO_PinSource11;break;
		case GPIO_Pin_12: GPIO_PinSource = GPIO_PinSource12;break;
		case GPIO_Pin_13: GPIO_PinSource = GPIO_PinSource13;break;
		case GPIO_Pin_14: GPIO_PinSource = GPIO_PinSource14;break;
		case GPIO_Pin_15: GPIO_PinSource = GPIO_PinSource15;break;
	}		
	return GPIO_PinSource;
}

/*
***************************************************
��������GPIO_Pin_TO_GPIO_PinSource
���ܣ�����GPIO���Ÿ�������
��ڲ�����	BSP_GPIO��GPIO�����ź�
					GPIO_AF��	�������蹦��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void GPIO_Pin_TO_PinAFConfig(BSP_GPIOSource_TypeDef* BSP_GPIO,uint8_t GPIO_AF){
	GPIO_PinAFConfig(BSP_GPIO->GPIOx,GPIO_Pin_TO_GPIO_PinSource(BSP_GPIO),GPIO_AF);
}

/*
***************************************************
��������BSP_GPIO_Init
���ܣ�GPIO���ų�ʼ��
��ڲ�����	BSP_GPIO��GPIO�����ź�
					GPIO_Mode���������õĹ���
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_GPIO_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,BSP_GPIOMode_TypeDef GPIO_Mode){
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	GPIOMode_TypeDef 	BSP_GPIO_Mode;//	 = (uint8_t)((GPIO_Mode&0xff0000)>>16);
	GPIOOType_TypeDef BSP_GPIO_OType;// = (uint8_t)((GPIO_Mode&0x00ff00)>>8);
	GPIOPuPd_TypeDef 	BSP_GPIO_PuPd;// = (uint8_t)(GPIO_Mode&0x0000ff);
	
	switch( (uint8_t)((GPIO_Mode&0xff0000)>>16) ){
		case 0x00: BSP_GPIO_Mode = GPIO_Mode_IN; 	break;
		case 0x01: BSP_GPIO_Mode = GPIO_Mode_OUT;	break;
		case 0x02: BSP_GPIO_Mode = GPIO_Mode_AF;	break;
		case 0x03: BSP_GPIO_Mode = GPIO_Mode_AN;	break;
	}
	switch( (uint8_t)((GPIO_Mode&0x00ff00)>>8) ){
		case 0x00: BSP_GPIO_OType = GPIO_OType_PP;	break;
		case 0x01: BSP_GPIO_OType = GPIO_OType_OD;	break;
	}
	switch( (uint8_t)(GPIO_Mode&0x0000ff) ){
		case 0x00: BSP_GPIO_PuPd = GPIO_PuPd_NOPULL;	break;
		case 0x01: BSP_GPIO_PuPd = GPIO_PuPd_UP;	break;
		case 0x02: BSP_GPIO_PuPd = GPIO_PuPd_DOWN;	break;
	}
	BSP_GPIO_RCC_Init(BSP_GPIO);	//����GPIO�˿�ʱ��;
	
	/* GPIO��ʼ������ */
  GPIO_InitStructure.GPIO_Pin = BSP_GPIO->Pin;			//��Ӧ����
  GPIO_InitStructure.GPIO_Mode = BSP_GPIO_Mode;			//���ö�ӦGPIO���������˿�ģʽ
  GPIO_InitStructure.GPIO_OType = BSP_GPIO_OType;		//���ö�ӦGPIO�����쿪©ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = BSP_GPIO_PuPd;			//���ö�ӦGPIO��������ģʽ
  GPIO_Init(BSP_GPIO->GPIOx, &GPIO_InitStructure);	//��ʼ��
}
