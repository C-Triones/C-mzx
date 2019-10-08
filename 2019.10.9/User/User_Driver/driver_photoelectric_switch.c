#include "driver.h"

/* �����ڶ�Ӧ��RCCʱ�� */
#define RCC_ALL_PHOTOELECTRIC_SWITCH 	(RCC_APB2Periph_GPIOE)
/*ǰ��45*/
#define FRONT_LEFT_OBLIQUE_PORT    GPIOE
#define FRONT_LEFT_OBLIQUE_PIN	    GPIO_Pin_6
/*ǰ��*/
#define FRONT_MIDDLE_PORT    GPIOE
#define FRONT_MIDDLE_PIN	    GPIO_Pin_5
/*ǰ��45*/	 
#define FRONT_RIGHT_OBLIQUE_PORT    GPIOE
#define FRONT_RIGHT_OBLIQUE_PIN	    GPIO_Pin_4
/*ǰ��90*/
#define FRONT_LEFT_PORT    GPIOE
#define FRONT_LEFT_PIN	    GPIO_Pin_3
/*ǰ��90*/
#define FRONT_RIGHT_PORT    GPIOE
#define FRONT_RIGHT_PIN	    GPIO_Pin_2
/*����45*/

photoelectricSwitchList_t photoelectricSwitch;
/*
*********************************************************************************************************
*	�� �� ��: driver_InitPhotoelectricSwitchHard
*	����˵��: ���ð�����Ӧ��GPIO
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void driver_InitPhotoelectricSwitchHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��1������GPIOʱ�� */
	RCC_APB2PeriphClockCmd(RCC_ALL_PHOTOELECTRIC_SWITCH, ENABLE);

	/* ��2�����������еİ���GPIOΪ��������ģʽ(ʵ����CPU��λ���������״̬) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	/* ���븡��ģʽ */
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_OBLIQUE_PIN;
	GPIO_Init(FRONT_LEFT_OBLIQUE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FRONT_MIDDLE_PIN;
	GPIO_Init(FRONT_MIDDLE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_OBLIQUE_PIN;
	GPIO_Init(FRONT_RIGHT_OBLIQUE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_PIN;
	GPIO_Init(FRONT_LEFT_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_PIN;
	GPIO_Init(FRONT_RIGHT_PORT, &GPIO_InitStructure);

}

void driverPhotoelectricSwitchNowStateUpdate(void)
{
	photoelectricSwitch.frontLeftOblique = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_LEFT_OBLIQUE_PORT,FRONT_LEFT_OBLIQUE_PIN);   	/*ǰ��45*/
	photoelectricSwitch.frontMiddle = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_MIDDLE_PORT,FRONT_MIDDLE_PIN);					 	/*ǰ��*/
	photoelectricSwitch.frontRightOblique = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_RIGHT_OBLIQUE_PORT,FRONT_RIGHT_OBLIQUE_PIN);	/*ǰ��45*/
	photoelectricSwitch.frontLeft = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_LEFT_PORT,FRONT_LEFT_PIN);								/*ǰ��90*/
	photoelectricSwitch.frontRight = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_RIGHT_PORT,FRONT_RIGHT_PIN);							/*ǰ��90*/
}
