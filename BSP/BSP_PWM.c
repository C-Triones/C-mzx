#include "BSP_PWM.h"


/******************************外部调用函数************************************/
void BSP_TIM_PWM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_GPIOSource_TypeDef* GPIO_PWM1,
											BSP_GPIOSource_TypeDef* GPIO_PWM2,
											BSP_GPIOSource_TypeDef* GPIO_PWM3,
											BSP_GPIOSource_TypeDef* GPIO_PWM4);
/*****************************************************************************/

#define NULL 0

/*
***************************************************
函数名：BSP_TIM_PWM_Init
功能：配置TIMx定时器PWM输出功能
入口参数：	BSP_TIMx：定时器号		 （不包括TIM1，TIM8两个高级定时器）
					Period：自动重装值
					Prescaler：时钟预分频数
					GPIO_PWM1：PWM1引脚号（不使用时请用NULL做传递参数）
					GPIO_PWM2：PWM2引脚号（不使用时请用NULL做传递参数）
					GPIO_PWM3：PWM3引脚号（不使用时请用NULL做传递参数）
					GPIO_PWM4：PWM4引脚号（不使用时请用NULL做传递参数）
返回值：无
应用范围：外部调用
备注：	TIM9->TIM11 的时钟频率为APB2时钟的2倍，即168MHz
			TIM2->TIM7, TIM12->TIM14 的时钟频率为APB1时钟的2倍，即84MHz
			
			TIM2，TIM5：32位重装载值
			TIM3，TIM4，TIM6，TIM7，TIM9->TIM14：16位重装载值
			
			TIM2->TIM5 PWM通道有4个
			TIM9，TIM12 PWM通道有2个
			TIM10，TIM11，TIM13，TIM14 PWM通道有1个
***************************************************
*/
void BSP_TIM_PWM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_GPIOSource_TypeDef* GPIO_PWM1,
											BSP_GPIOSource_TypeDef* GPIO_PWM2,
											BSP_GPIOSource_TypeDef* GPIO_PWM3,
											BSP_GPIOSource_TypeDef* GPIO_PWM4){
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	
	BSP_TIM_RCC_Init(BSP_TIMx);	//使能定时器TIMx时钟
	
	/* 配置PWM输出引脚 */
	if(GPIO_PWM1 != NULL){
		BSP_GPIO_Init(GPIO_PWM1,GPIO_Mode_AF_PP);	//配置PWM1引脚为复用推挽模式
		GPIO_PinAFConfig(GPIO_PWM1->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM1),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM1引脚复用为定时器TIMx
	}
	if(GPIO_PWM2 != NULL){
		BSP_GPIO_Init(GPIO_PWM2,GPIO_Mode_AF_PP);	//配置PWM2引脚为复用推挽模式
		GPIO_PinAFConfig(GPIO_PWM2->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM2),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM2引脚复用为定时器TIMx
	}
	if(GPIO_PWM3 != NULL){
		BSP_GPIO_Init(GPIO_PWM3,GPIO_Mode_AF_PP);	//配置PWM3引脚为复用推挽模式
		GPIO_PinAFConfig(GPIO_PWM3->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM3),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM3引脚复用为定时器TIMx
	}
	if(GPIO_PWM4 != NULL){
		BSP_GPIO_Init(GPIO_PWM4,GPIO_Mode_AF_PP);	//配置PWM4引脚为复用推挽模式
		GPIO_PinAFConfig(GPIO_PWM4->GPIOx,GPIO_Pin_TO_GPIO_PinSource(GPIO_PWM4),TIM_TO_GPIO_AF(BSP_TIMx));	//PWM4引脚复用为定时器TIMx
	}
	
	/* 配置定时器TIMx */
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  	//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = Period;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseStructure);//初始化定时器TIMx
	
	/* 初始化TIMx 各通道PWM模式 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	if(GPIO_PWM1 != NULL){
		TIM_OC1Init(BSP_TIMx, &TIM_OCInitStructure);  		//根据指定的参数初始化外设TIMx OC1
		TIM_OC1PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//使能TIMx在CCR1上的预装载寄存器
	}
	if(GPIO_PWM2 != NULL){
		TIM_OC2Init(BSP_TIMx, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIMx OC2
		TIM_OC2PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//使能TIMx在CCR2上的预装载寄存器
	}
	if(GPIO_PWM3 != NULL){
		TIM_OC3Init(BSP_TIMx, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIMx OC3
		TIM_OC3PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//使能TIMx在CCR3上的预装载寄存器
	}
	if(GPIO_PWM4 != NULL){
		TIM_OC4Init(BSP_TIMx, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIMx OC4
		TIM_OC4PreloadConfig(BSP_TIMx, TIM_OCPreload_Enable);	//使能TIMx在CCR4上的预装载寄存器
	}
	
	TIM_ARRPreloadConfig(BSP_TIMx,ENABLE);//ARPE使能 
	
	TIM_Cmd(BSP_TIMx, ENABLE);  //使能TIMx定时器
	TIM_CtrlPWMOutputs(BSP_TIMx,ENABLE);//TIMx PWM输出使能
}



