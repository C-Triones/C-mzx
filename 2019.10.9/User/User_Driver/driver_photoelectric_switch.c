#include "driver.h"

/* 按键口对应的RCC时钟 */
#define RCC_ALL_PHOTOELECTRIC_SWITCH 	(RCC_APB2Periph_GPIOE)
/*前左45*/
#define FRONT_LEFT_OBLIQUE_PORT    GPIOE
#define FRONT_LEFT_OBLIQUE_PIN	    GPIO_Pin_6
/*前中*/
#define FRONT_MIDDLE_PORT    GPIOE
#define FRONT_MIDDLE_PIN	    GPIO_Pin_5
/*前右45*/	 
#define FRONT_RIGHT_OBLIQUE_PORT    GPIOE
#define FRONT_RIGHT_OBLIQUE_PIN	    GPIO_Pin_4
/*前左90*/
#define FRONT_LEFT_PORT    GPIOE
#define FRONT_LEFT_PIN	    GPIO_Pin_3
/*前右90*/
#define FRONT_RIGHT_PORT    GPIOE
#define FRONT_RIGHT_PIN	    GPIO_Pin_2
/*后左45*/

photoelectricSwitchList_t photoelectricSwitch;
/*
*********************************************************************************************************
*	函 数 名: driver_InitPhotoelectricSwitchHard
*	功能说明: 配置按键对应的GPIO
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void driver_InitPhotoelectricSwitchHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 第1步：打开GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_ALL_PHOTOELECTRIC_SWITCH, ENABLE);

	/* 第2步：配置所有的按键GPIO为浮动输入模式(实际上CPU复位后就是输入状态) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	/* 输入浮空模式 */
	
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
	photoelectricSwitch.frontLeftOblique = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_LEFT_OBLIQUE_PORT,FRONT_LEFT_OBLIQUE_PIN);   	/*前左45*/
	photoelectricSwitch.frontMiddle = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_MIDDLE_PORT,FRONT_MIDDLE_PIN);					 	/*前中*/
	photoelectricSwitch.frontRightOblique = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_RIGHT_OBLIQUE_PORT,FRONT_RIGHT_OBLIQUE_PIN);	/*前右45*/
	photoelectricSwitch.frontLeft = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_LEFT_PORT,FRONT_LEFT_PIN);								/*前左90*/
	photoelectricSwitch.frontRight = (photoelectricSwitchValue_e)GPIO_ReadInputDataBit(FRONT_RIGHT_PORT,FRONT_RIGHT_PIN);							/*前右90*/
}
