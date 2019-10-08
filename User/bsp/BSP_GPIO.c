#include "BSP_GPIO.h"
#include "BSP_GPIO_Define.h"

/******************************外部调用函数************************************/
uint8_t GPIO_Pin_TO_GPIO_PinSource(BSP_GPIOSource_TypeDef* BSP_GPIO);
void GPIO_Pin_TO_PinAFConfig(uint32_t GPIO_Remap);
void BSP_GPIO_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,BSP_GPIOMode_TypeDef GPIO_Mode);
/*****************************************************************************/

/*
***************************************************
函数名：BSP_GPIO_RCC_Init
功能：配置GPIO端口时钟
入口参数：	BSP_GPIO：GPIO的引脚号
返回值：无
应用范围：内部调用
备注：
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
函数名：GPIO_Pin_TO_GPIO_PinSource
功能：配置GPIO引脚资源
入口参数：	BSP_GPIO：GPIO的引脚号
返回值：GPIO_PinSource
应用范围：外部调用
备注：
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
函数名：GPIO_Pin_TO_GPIO_PinSource
功能：配置GPIO引脚复用外设
入口参数：	GPIO_Remap复用外设功能
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void GPIO_Pin_TO_PinAFConfig(uint32_t GPIO_Remap){
	GPIO_PinRemapConfig(GPIO_Remap,ENABLE);
}

/*
***************************************************
函数名：BSP_GPIO_Init
功能：GPIO引脚初始化
入口参数：	BSP_GPIO：GPIO的引脚号
					GPIO_Mode：所需配置的功能
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_GPIO_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,BSP_GPIOMode_TypeDef BSP_GPIO_Mode){
	GPIO_InitTypeDef  GPIO_InitStructure;
	BSP_GPIO_RCC_Init(BSP_GPIO);	//开启GPIO端口时钟;
	/* GPIO初始化设置 */
	GPIO_InitStructure.GPIO_Pin = BSP_GPIO->Pin;			//对应引脚
	GPIO_InitStructure.GPIO_Mode = BSP_GPIO_Mode;			//设置对应GPIO的输出输入端口模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_Init(BSP_GPIO->GPIOx, &GPIO_InitStructure);	//初始化
}

