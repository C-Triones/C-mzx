#include "BSP_Timer.h"

/*************************************************************
TIM1, TIM8->TIM11 的时钟频率为APB2时钟的2倍，即168MHz
TIM2->TIM7, TIM12->TIM14 的时钟频率为APB1时钟的2倍，即84MHz

TIM2，TIM5：32位重装载值
TIM1，TIM3，TIM4，TIM6->TIM8，TIM9->TIM14：16位重装载值
*************************************************************/

/******************************外部调用函数************************************/
void BSP_TIM_RCC_Init(TIM_TypeDef* BSP_TIMx);
void BSP_TIM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler);
void BSP_TIM_INT_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,u8 PreemptionPriority,u8 SubPriority);
uint32_t	TIM_TO_GPIO_PinRemap(TIM_TypeDef* BSP_TIMx);
void BSP_TIM_ICAP_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,
											BSP_TIM_ICAP_TypeDef* ICAP1,
											BSP_TIM_ICAP_TypeDef* ICAP2,
											BSP_TIM_ICAP_TypeDef* ICAP3,
											BSP_TIM_ICAP_TypeDef* ICAP4,
											u8 PreemptionPriority, u8 SubPriority);
/*****************************************************************************/


/*
***************************************************
函数名：BSP_TIM_RCC_Init
功能：配置TIMx定时器时钟
入口参数：	BSP_TIMx：定时器号
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_TIM_RCC_Init(TIM_TypeDef* BSP_TIMx){
	if(BSP_TIMx == TIM1)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);		//使能定时器TIM1的时钟
	else if(BSP_TIMx == TIM2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//使能定时器TIM2的时钟
	else if(BSP_TIMx == TIM3)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//使能定时器TIM3的时钟
	else if(BSP_TIMx == TIM4)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		//使能定时器TIM4的时钟
	else if(BSP_TIMx == TIM5)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		//使能定时器TIM5的时钟
	else if(BSP_TIMx == TIM6)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);		//使能定时器TIM6的时钟
	else if(BSP_TIMx == TIM7)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);		//使能定时器TIM7的时钟
	else if(BSP_TIMx == TIM8)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);		//使能定时器TIM8的时钟
	else if(BSP_TIMx == TIM9)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);		//使能定时器TIM9的时钟
	else if(BSP_TIMx == TIM10)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);	//使能定时器TIM10的时钟
	else if(BSP_TIMx == TIM11)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);	//使能定时器TIM11的时钟
	else if(BSP_TIMx == TIM12)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);	//使能定时器TIM12的时钟
	else if(BSP_TIMx == TIM13)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);	//使能定时器TIM13的时钟
	else if(BSP_TIMx == TIM14)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);	//使能定时器TIM14的时钟
}

/*
***************************************************
函数名：TIM_TO_NVIC_IRQChannel
功能：配置TIMx定时器NVIC中断通道
入口参数：	BSP_TIMx：定时器号（不包括TIM1和TIM8两个高级定时器）
定时器9后无法配置中断(大容量除外)
返回值：NVIC_IRQChannel
应用范围：内部调用
备注：
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
		NVIC_IRQChannel = TIM6_IRQn;
	else if(BSP_TIMx == TIM7)		
		NVIC_IRQChannel = TIM7_IRQn;
	else if(BSP_TIMx == TIM1)   
		NVIC_IRQChannel = TIM1_UP_IRQn;
	else if(BSP_TIMx == TIM8)   
		NVIC_IRQChannel = TIM8_UP_IRQn;
	return NVIC_IRQChannel;	
}

/*
***************************************************
函数名：TIM_TO_GPIO_AF
功能：输出TIMx定时器GPIO_AF
入口参数：	BSP_TIMx：定时器号（不包括TIM1和TIM8两个高级定时器）
返回值：GPIO_AF
应用范围：外部调用
备注：
***************************************************
*/
uint32_t TIM_TO_GPIO_PinRemap(TIM_TypeDef* BSP_TIMx){
	uint32_t GPIO_PinReamp;
	
	if(BSP_TIMx == TIM1)				
		GPIO_PinReamp = GPIO_FullRemap_TIM1;
	else if(BSP_TIMx == TIM2)		
		GPIO_PinReamp = GPIO_FullRemap_TIM2;
	else if(BSP_TIMx == TIM3)		
		GPIO_PinReamp = GPIO_FullRemap_TIM3;
	else if(BSP_TIMx == TIM4)		
		GPIO_PinReamp = GPIO_Remap_TIM4;
	else if(BSP_TIMx == TIM5)		
		GPIO_PinReamp = GPIO_Remap_TIM5CH4_LSI;
	else if(BSP_TIMx == TIM9)		
		GPIO_PinReamp = GPIO_Remap_TIM9;
	else if(BSP_TIMx == TIM10)	
		GPIO_PinReamp = GPIO_Remap_TIM10;
	else if(BSP_TIMx == TIM11)	
		GPIO_PinReamp = GPIO_Remap_TIM11;
	else if(BSP_TIMx == TIM12)	
		GPIO_PinReamp = GPIO_Remap_TIM12;
	else if(BSP_TIMx == TIM13)	
		GPIO_PinReamp = GPIO_Remap_TIM13;
	else if(BSP_TIMx == TIM14)	
		GPIO_PinReamp = GPIO_Remap_TIM14;
	
	return GPIO_PinReamp;	
}

/*
***************************************************
函数名：BSP_TIM_Init
功能：配置TIMx定时器
入口参数：	BSP_TIMx：定时器号（不包括TIM1和TIM8两个高级定时器）
					Period：自动重装值
					Prescaler：时钟预分频数
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_TIM_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	BSP_TIM_RCC_Init(BSP_TIMx);		//使能定时器TIMx时钟
	
	TIM_TimeBaseInitStructure.TIM_Period 			= Period; 			//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler 		= Prescaler;  	//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode 		= TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision 	= TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseInitStructure);
	
	TIM_ARRPreloadConfig(BSP_TIMx, ENABLE);	
	TIM_Cmd(BSP_TIMx,ENABLE); 		//使能定时器TIMx	
}

/*
***************************************************
函数名：BSP_TIM_INT_Init
功能：配置TIMx定时器中断
入口参数：	BSP_TIMx：定时器号（不包括TIM1和TIM8两个高级定时器）
					Period：自动重装值
					Prescaler：时钟预分频数
					PreemptionPriority：抢占优先级
					SubPriority：子优先级
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_TIM_INT_Init(TIM_TypeDef* BSP_TIMx,uint32_t Period,u16 Prescaler,u8 PreemptionPriority,u8 SubPriority){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	BSP_TIM_RCC_Init(BSP_TIMx);		//使能定时器TIMx时钟
	
	TIM_TimeBaseInitStructure.TIM_Period 			= Period; 			//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler 		= Prescaler;  	//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode 		= TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision 	= TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(BSP_TIMx,TIM_IT_Update,ENABLE); //允许定时器TIMx更新中断
	TIM_Cmd(BSP_TIMx,ENABLE); 		//使能定时器TIMx
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM_TO_NVIC_IRQChannel(BSP_TIMx); //定时器TIMx中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority; //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; //子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);		
}
	
/*
***************************************************
函数名：BSP_TIM_ICAP_Init
功能：配置定时器TIMx输出捕获
入口参数：	BSP_TIMx：定时器号		 （不包括TIM1，TIM8两个高级定时器）
					Period：自动重装值
					Prescaler：时钟预分频数
					GPIO_ICAP1：ICAP1引脚号（不使用时请用NULL做传递参数）
					GPIO_ICAP2：ICAP2引脚号（不使用时请用NULL做传递参数）
					GPIO_ICAP3：ICAP3引脚号（不使用时请用NULL做传递参数）
					GPIO_ICAP4：ICAP4引脚号（不使用时请用NULL做传递参数）
					PreemptionPriority：抢占优先级
					SubPriority：子优先级
返回值：无
应用范围：外部调用
备注：
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
	
	/*************初始化TIMx时钟***************/
	BSP_TIM_RCC_Init(BSP_TIMx);	//使能定时器TIMx时钟
	
	/*************配置ICAP输出引脚***************/
	if(ICAP1 != NULL){
		BSP_GPIO_Init(ICAP1->ICAP_GPIO,GPIO_Mode_AF_PP);	//配置ICAP1引脚为复用推挽模式
		GPIO_Pin_TO_PinAFConfig(TIM_TO_GPIO_PinRemap(BSP_TIMx));	//ICAP1引脚复用为定时器TIMx
	}
	if(ICAP2 != NULL){
		BSP_GPIO_Init(ICAP2->ICAP_GPIO,GPIO_Mode_AF_PP);	//配置ICAP2引脚为复用推挽模式
		GPIO_Pin_TO_PinAFConfig(TIM_TO_GPIO_PinRemap(BSP_TIMx));	//ICAP2引脚复用为定时器TIMx
	}
	if(ICAP3 != NULL){
		BSP_GPIO_Init(ICAP1->ICAP_GPIO,GPIO_Mode_AF_PP);	//配置ICAP3引脚为复用推挽模式
		GPIO_Pin_TO_PinAFConfig(TIM_TO_GPIO_PinRemap(BSP_TIMx));	//ICAP3引脚复用为定时器TIMx
	}
	if(ICAP4 != NULL){
		BSP_GPIO_Init(ICAP4->ICAP_GPIO,GPIO_Mode_AF_PP);	//配置ICAP4引脚为复用推挽模式
		GPIO_Pin_TO_PinAFConfig(TIM_TO_GPIO_PinRemap(BSP_TIMx));	//ICAP4引脚复用为定时器TIMx
	}
	
	/*************配置定时器TIMx***************/
	TIM_TimeBaseStructure.TIM_Prescaler = Period;  	//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = Prescaler;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BSP_TIMx,&TIM_TimeBaseStructure);//初始化定时器TIMx
	
	
	/*************初始化TIMx各通道的输入捕获参数***************/
	if(ICAP1 != NULL){
		TIM_IT |= TIM_IT_CC1;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_1; 						//选择输入端 IC1映射到TI1上
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//上升沿捕获
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//配置输入分频,不分频 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//配置输入滤波器 不滤波
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	if(ICAP2 != NULL){
		TIM_IT |= TIM_IT_CC2;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_2; 						//选择输入端 IC2映射到TI2上
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//上升沿捕获
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//配置输入分频,不分频 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//配置输入滤波器 不滤波
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	if(ICAP3 != NULL){
		TIM_IT |= TIM_IT_CC3;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_3; 						//选择输入端 IC3映射到TI3上
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//上升沿捕获
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI3上
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//配置输入分频,不分频 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//配置输入滤波器 不滤波
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	if(ICAP4 != NULL){
		TIM_IT |= TIM_IT_CC4;
		TIM_ICInitStructure.TIM_Channel 		= TIM_Channel_4; 						//选择输入端 IC4映射到TI4上
		TIM_ICInitStructure.TIM_ICPolarity 	= ICAP1->TIM_ICPolarity;			//上升沿捕获
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI4上
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					//配置输入分频,不分频 
		TIM_ICInitStructure.TIM_ICFilter 		= 0x00;											//配置输入滤波器 不滤波
		TIM_ICInit(BSP_TIMx, &TIM_ICInitStructure);
	}
	
	TIM_ITConfig(TIM5,TIM_IT_Update | TIM_IT,ENABLE);//允许更新中断 ,允许通道捕获中断
//	TIM_Cmd(BSP_TIMx, ENABLE);  //使能TIMx定时器
	
	
	/*********************配置NVIC寄存器***********************/
	if( (PreemptionPriority != 0xff) && (SubPriority != 0xff) ){
		NVIC_InitStructure.NVIC_IRQChannel = TIM_TO_NVIC_IRQChannel(BSP_TIMx);	//定时器TIMx中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
	}
}
