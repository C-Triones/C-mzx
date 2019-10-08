#include "driver.h"

/* 按键口对应的RCC时钟 */
#define RCC_ALL_KEY	(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOD)

#define KEY_ENTER_PORT    GPIOE                     
#define KEY_ENTER_PIN	    GPIO_Pin_2

#define KEY_BACK_PORT    GPIOE 
#define KEY_BACK_PIN	    GPIO_Pin_1

#define KEY_UP_PORT       GPIOA
#define KEY_UP_PIN	      GPIO_Pin_5

#define KEY_DOWN_PORT     GPIOE
#define KEY_DOWN_PIN	    GPIO_Pin_3

#define KEY_SAVE_PORT    GPIOE
#define KEY_SAVE_PIN	    GPIO_Pin_0


#define SMOOTHING_TIME 10

key_t key;                                                                                                                                                                                                                                                                                                                                                                        
/*
*********************************************************************************************************
*	函 数 名: driver_InitPhotoelectricSwitchHard
*	功能说明: 配置按键对应的GPIO
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void driver_InitKeyHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 第1步：打开GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY, ENABLE);

	/* 第2步：配置所有的按键GPIO为浮动输入模式(实际上CPU复位后就是输入状态) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	/* 输入浮空模式 */
	
	GPIO_InitStructure.GPIO_Pin = KEY_ENTER_PIN;
	GPIO_Init(KEY_ENTER_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KEY_BACK_PIN;
	GPIO_Init(KEY_BACK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_UP_PIN;
	GPIO_Init(KEY_UP_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_DOWN_PIN;
	GPIO_Init(KEY_DOWN_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KEY_SAVE_PIN;
	GPIO_Init(KEY_SAVE_PORT, &GPIO_InitStructure);
}

uint8_t driverKeyReturn(keyValue_e* key,uint8_t* keepTime)
{
	uint8_t keyOutputValue = NULL;
	switch(*key){
	  case PRESS:{
			*keepTime += 1;
			break;
		}
		case NO_PRESS:{
			*keepTime = NULL;
			break;
		}
	}
	
	if(*keepTime <= SMOOTHING_TIME){
		keyOutputValue = NULL;
	}
	else{
		keyOutputValue = 1;
	}
	
	return keyOutputValue;
}
uint8_t driverKeyDetection(uint8_t mode)
{
	static uint8_t keyPress = PRESS;
	if(mode) keyPress = PRESS;
	if(keyPress == PRESS){
		keyPress = NO_PRESS;
		if(driverKeyReturn(&key.nowState.enter,&key.keepTime[KEY_ENTER])){
			return KEY_ENTER;
		}
		else if(driverKeyReturn(&key.nowState.up,&key.keepTime[KEY_UP])){
			return KEY_UP;
		}
		else if(driverKeyReturn(&key.nowState.down,&key.keepTime[KEY_DOWN])){
			return KEY_DOWN;
		}
		else if(driverKeyReturn(&key.nowState.back,&key.keepTime[KEY_BACK])){
			return KEY_BACK;
		}
		else if(driverKeyReturn(&key.nowState.save,&key.keepTime[KEY_SAVE])){
			return KEY_SAVE;
		}
		else return KEY_NULL;
	}
	return KEY_NULL;
}

void driverKeyNowStateUpdate(void)
{
	key.nowState.enter = (keyValue_e)GPIO_ReadInputDataBit( KEY_ENTER_PORT, KEY_ENTER_PIN);
	key.nowState.back = (keyValue_e)GPIO_ReadInputDataBit( KEY_BACK_PORT, KEY_BACK_PIN);
	key.nowState.up = (keyValue_e)GPIO_ReadInputDataBit( KEY_UP_PORT, KEY_UP_PIN);
	key.nowState.down = (keyValue_e)GPIO_ReadInputDataBit( KEY_DOWN_PORT, KEY_DOWN_PIN);
	key.nowState.save = (keyValue_e)GPIO_ReadInputDataBit( KEY_SAVE_PORT, KEY_SAVE_PIN);	
	
	key.realValue = driverKeyDetection(1);
}

