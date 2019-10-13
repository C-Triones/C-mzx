#include "driver.h"



/*
 * 函数名：TIM3_GPIO_Config
 * 描述  ：配置TIM3复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM23_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /********TIM3引脚复用********/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	/*GPIO设置为复用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	/*GPIO设置为复用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*
 * 函数名TIM23_PWM_Init
 * 描述  ：配置TIM23输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM23_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//上电让电机静止
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 260;  //爪子1      
	u16 CCR4_Val = 250;  //爪子2
	u16 CCR5_Val = 120;  //相机


	TIM_TimeBaseStructure.TIM_Period = (3200 - 1); 
	TIM_TimeBaseStructure.TIM_Prescaler = (450 - 1);
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置定时器计数模式：向上计数模式		
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/*配置为PWM模式1*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/*当定时器计数值小于CCR1_Val时为高电平*/	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
 
 
	/* 设置跳变值，当计数器计数到这个值时，电平发生跳变 */
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	/*使能通道1*/
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/*设置通道2的电平跳变值，输出另外一个占空比的PWM*/
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  
	/*使能通道2*/
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/* 设置跳变值，当计数器计数到这个值时，电平发生跳变 */
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val; 
	/*使能通道3*/
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/*设置通道4的电平跳变值，输出另外一个占空比的PWM*/
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  
	/*使能通道4*/
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/*设置通道1的电平跳变值，输出另外一个占空比的PWM*/
	TIM_OCInitStructure.TIM_Pulse = CCR5_Val;	  
	/*使能通道1*/
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	  
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/*使能TIM2重载寄存器ARR*/
	TIM_ARRPreloadConfig(TIM2, ENABLE);		
	/*使能TIM3重载寄存器ARR*/
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 

  /*使能定时器2*/
	TIM_Cmd(TIM2, ENABLE);
	/*使能定时器3*/
	TIM_Cmd(TIM3, ENABLE);              
}

void driver_InitSteeringEngineSpeed(void)
{
	TIM23_GPIO_Config();
	TIM23_PWM_Init();
}

