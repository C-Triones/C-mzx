#include "Driver_SRF_05.h"

int count=0;
//void EXTI9_5_IRQHandler(void)
//{
//	
//     if(EXTI_GetITStatus(EXTI_Line9) != RESET)
//	{
//			TIM_SetCounter(SRF_05_USE_TIMER,0);
//			TIM_Cmd(SRF_05_USE_TIMER, ENABLE);   //开启时钟	Tim1
//		
//			   count=	1;               
//            while(count)	                 //等待低电平
//			{
//					if(TIM_GetCounter(SRF_05_USE_TIMER)>=10) //9*10us=90us
//					{ 
//					    TIM_Cmd(SRF_05_USE_TIMER, DISABLE); 	// 关闭时钟 Tim1
//						count=0;					// 循环数清零
//					} 
//					else  count=GPIO_ReadInputDataBit(GPIO_TO_EXTI_PortSource(SRF_05_ECHO),GPIO_TO_EXTI_PinSource(SRF_05_ECHO)); //检测PB1是否高电平 高 则count为1 低 则count为0  	
//						       
//			}
//			TIM_Cmd(SRF_05_USE_TIMER, DISABLE);			                                 //定时器 Tim1 关闭
////			Get_Distance();
//		
//	  //EXTI->IMR&=~(1<<1);  
//	
//	EXTI_ClearITPendingBit(EXTI_Line9);  //清除EXTI1线路挂起位
//	
//	}	

//}
