#include "Driver_SRF_05.h"
#include "delay.h"

ultrasonicStruct_t SRF_05_Data;
//�����������ʼ��
void SRF_05_Init(void){
	//GPIO
	BSP_GPIO_Init(SRF_05_TRIG,GPIO_Mode_Out_PP);
	BSP_GPIO_Init(SRF_05_ECHO,GPIO_Mode_IPD);
	//TIM
	BSP_TIM_INT_Init(SRF_05_USE_TIMER,SRF_05_USE_TIMER_PERIOD,SRF_05_USE_TIMER_PESCALER,SRF_05_USE_TIMER_PREEMPTIONPRIORITY,SRF_05_USE_TIMER_SUBPRIORITY);
	//EXIT
	BSP_GPIO_EXIT_Init(SRF_05_ECHO,EXTI_Trigger_Rising,0x01,0x00);
//	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
//	TIM_Cmd(TIM3,DISABLE);
}
//��ʼ����
void SRF_05_Start(void){
	GPIO_SetBits(GPIO_TO_EXTI_PortSource(SRF_05_TRIG),GPIO_TO_EXTI_PinSource(SRF_05_TRIG)); 		  //��>10US�ĸߵ�ƽ�T  ��ָ���룺GPIO_SetBits(PB,GPIO_Pin_0) ��ͬ
	delay_us(12);		                      //��ʱ11US
	GPIO_ResetBits(GPIO_TO_EXTI_PortSource(SRF_05_TRIG),GPIO_TO_EXTI_PinSource(SRF_05_TRIG));
}
//��ò�������
void Get_Distance(void){
	SRF_05_Data.getDistance = TIM_GetCounter(SRF_05_USE_TIMER)*5*34/200.0;
}

void TIM3_IRQHandler(void){
	if (TIM_GetITStatus(SRF_05_USE_TIMER,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(SRF_05_USE_TIMER, TIM_IT_Update);
	}
}
