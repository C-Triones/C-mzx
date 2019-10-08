#include "BSP_GPIO.h"
#include "BSP_GPIO_Define.h"

/******************************�ⲿ���ú���************************************/
uint8_t GPIO_Pin_TO_GPIO_PinSource(BSP_GPIOSource_TypeDef* BSP_GPIO);
void GPIO_Pin_TO_PinAFConfig(uint32_t GPIO_Remap);
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
		GPIO_RCC = RCC_APB2Periph_GPIOA;
	else if(BSP_GPIO->GPIOx == GPIOB)	
		GPIO_RCC = RCC_APB2Periph_GPIOB;
	else if(BSP_GPIO->GPIOx == GPIOC)	
		GPIO_RCC = RCC_APB2Periph_GPIOC;
	else if(BSP_GPIO->GPIOx == GPIOD)	
		GPIO_RCC = RCC_APB2Periph_GPIOD;
	else if(BSP_GPIO->GPIOx == GPIOE)	
		GPIO_RCC = RCC_APB2Periph_GPIOE;
	else if(BSP_GPIO->GPIOx == GPIOF)
		GPIO_RCC = RCC_APB2Periph_GPIOF;
	else if(BSP_GPIO->GPIOx == GPIOG)	
		GPIO_RCC = RCC_APB2Periph_GPIOG;
	
	RCC_APB2PeriphClockCmd(GPIO_RCC,ENABLE);
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
		case GPIO_Pin_10: 	GPIO_PinSource = GPIO_PinSource10;break;
		case GPIO_Pin_11: 	GPIO_PinSource = GPIO_PinSource11;break;
		case GPIO_Pin_12: 	GPIO_PinSource = GPIO_PinSource12;break;
		case GPIO_Pin_13: 	GPIO_PinSource = GPIO_PinSource13;break;
		case GPIO_Pin_14: 	GPIO_PinSource = GPIO_PinSource14;break;
		case GPIO_Pin_15: 	GPIO_PinSource = GPIO_PinSource15;break;
	}		
	return GPIO_PinSource;
}

/*
***************************************************
��������GPIO_Pin_TO_GPIO_PinSource
���ܣ�����GPIO���Ÿ�������
��ڲ�����	GPIO_Remap�������蹦��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void GPIO_Pin_TO_PinAFConfig(uint32_t GPIO_Remap){
	GPIO_PinRemapConfig(GPIO_Remap,ENABLE);
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
void BSP_GPIO_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,BSP_GPIOMode_TypeDef BSP_GPIO_Mode){
	GPIO_InitTypeDef  GPIO_InitStructure;
	BSP_GPIO_RCC_Init(BSP_GPIO);	//����GPIO�˿�ʱ��;
	/* GPIO��ʼ������ */
	GPIO_InitStructure.GPIO_Pin = BSP_GPIO->Pin;			//��Ӧ����
	GPIO_InitStructure.GPIO_Mode = BSP_GPIO_Mode;			//���ö�ӦGPIO���������˿�ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_Init(BSP_GPIO->GPIOx, &GPIO_InitStructure);	//��ʼ��
}

