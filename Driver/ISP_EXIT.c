#include "Driver_SRF_05.h"

int count=0;
//void EXTI9_5_IRQHandler(void)
//{
//	
//     if(EXTI_GetITStatus(EXTI_Line9) != RESET)
//	{
//			TIM_SetCounter(SRF_05_USE_TIMER,0);
//			TIM_Cmd(SRF_05_USE_TIMER, ENABLE);   //����ʱ��	Tim1
//		
//			   count=	1;               
//            while(count)	                 //�ȴ��͵�ƽ
//			{
//					if(TIM_GetCounter(SRF_05_USE_TIMER)>=10) //9*10us=90us
//					{ 
//					    TIM_Cmd(SRF_05_USE_TIMER, DISABLE); 	// �ر�ʱ�� Tim1
//						count=0;					// ѭ��������
//					} 
//					else  count=GPIO_ReadInputDataBit(GPIO_TO_EXTI_PortSource(SRF_05_ECHO),GPIO_TO_EXTI_PinSource(SRF_05_ECHO)); //���PB1�Ƿ�ߵ�ƽ �� ��countΪ1 �� ��countΪ0  	
//						       
//			}
//			TIM_Cmd(SRF_05_USE_TIMER, DISABLE);			                                 //��ʱ�� Tim1 �ر�
////			Get_Distance();
//		
//	  //EXTI->IMR&=~(1<<1);  
//	
//	EXTI_ClearITPendingBit(EXTI_Line9);  //���EXTI1��·����λ
//	
//	}	

//}
