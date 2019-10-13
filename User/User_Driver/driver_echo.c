#include "driver.h"
#include "app_echo.h"
ultrasonicStruct_t SRF_04_Data1;
ultrasonicStruct_t SRF_04_Data2;
ultrasonicStruct_t SRF_04_Data3;
ultrasonicStruct_t SRF_04_Data4;
ultrasonicStruct_t SRF_04_Data5;
ultrasonicStruct_t SRF_04_Data6;
uint8_t srfFlg = 0;
void echo_deviceInit(void);
void driver_echo(){
	//GPIO
	BSP_GPIO_Init(SRF04_TRIG1,GPIO_Mode_Out_PP);//TRIG1
	BSP_GPIO_Init(SRF04_ECHO1,GPIO_Mode_IPD);//ECHO1
	BSP_GPIO_Init(SRF04_TRIG2,GPIO_Mode_Out_PP);//TRIG2
	BSP_GPIO_Init(SRF04_ECHO2,GPIO_Mode_IPD);//ECHO2
	BSP_GPIO_Init(SRF04_TRIG3,GPIO_Mode_Out_PP);//TRIG3
	BSP_GPIO_Init(SRF04_ECHO3,GPIO_Mode_IPD);//ECHO3
	BSP_GPIO_Init(SRF04_TRIG4,GPIO_Mode_Out_PP);//TRIG4
	BSP_GPIO_Init(SRF04_ECHO4,GPIO_Mode_IPD);//ECHO4
	BSP_GPIO_Init(SRF04_TRIG5,GPIO_Mode_Out_PP);//TRIG5
	BSP_GPIO_Init(SRF04_ECHO5,GPIO_Mode_IPD);//ECHO5
	BSP_GPIO_Init(SRF04_TRIG6,GPIO_Mode_Out_PP);//TRIG6
	BSP_GPIO_Init(SRF04_ECHO6,GPIO_Mode_IPD);//ECHO6
	//TIM
	BSP_TIM_INT_Init(ECHO_TIMER,ECHO_TIMER_PERIOD,ECHO_TIMER_PESCALER,ECHO_TIMER_PREEMPTIONPRIORITY,ECHO_TIMER_TIMER_SUBPRIORITY);
//	BSP_TIM_INT_Init(TIM5,2,36000,2,0);
	//EXIT
	BSP_GPIO_EXTI_Init(SRF04_ECHO1,EXTI_Trigger_Rising_Falling,0x03,0x00);
	BSP_GPIO_EXTI_Init(SRF04_ECHO2,EXTI_Trigger_Rising_Falling,0x03,0x00);
	BSP_GPIO_EXTI_Init(SRF04_ECHO3,EXTI_Trigger_Rising_Falling,0x03,0x00);
	BSP_GPIO_EXTI_Init(SRF04_ECHO4,EXTI_Trigger_Rising_Falling,0x03,0x00);
	BSP_GPIO_EXTI_Init(SRF04_ECHO5,EXTI_Trigger_Rising_Falling,0x03,0x00);
	BSP_GPIO_EXTI_Init(SRF04_ECHO6,EXTI_Trigger_Rising_Falling,0x03,0x00);
	TIM_ClearFlag(ECHO_TIMER,TIM_FLAG_Update);
	TIM_Cmd(ECHO_TIMER,DISABLE);
	TIM4->CNT = 0;
	TRIG1 = 0;
	TRIG2 = 0;
	TRIG3 = 0;
	TRIG4 = 0;
	TRIG5 = 0;
	TRIG6 = 0;
	echo_deviceInit();
}
void echo_deviceInit(void){
	SRF_04_Data1.device = 1;
	SRF_04_Data2.device = 2;
	SRF_04_Data3.device = 3;
	SRF_04_Data4.device = 4;
	SRF_04_Data5.device = 5;
	SRF_04_Data6.device = 6;
}

void app_echoOpentime(TIM_TypeDef* TIMx,ultrasonicStruct_t *SRFData){
	TIMx->CNT = 0;
	SRFData->msCount = 0;
	srfFlg = 1;
	TIM_Cmd(TIMx,ENABLE);
}



u32 echoRes(ultrasonicStruct_t *SRFData){
	u32 resEcho;
	switch(SRFData->device){
		case 1:resEcho = ECHO1;break;
		case 2:resEcho = ECHO2;break;
		case 3:resEcho = ECHO3;break;
		case 4:resEcho = ECHO4;break;
		case 5:resEcho = ECHO5;break;
		case 6:resEcho = ECHO6;break;
	}
	return resEcho;
}

u32 app_echoGettime(TIM_TypeDef* TIMx,ultrasonicStruct_t *SRFData){
	u32 time =0;
	time = SRFData->msCount*1000;
	time += TIMx->CNT;
	return time;
}

float meanRecursiveFilter(s16 newVuale,uint8_t N,ultrasonicStruct_t *srfData){
	uint32_t count=  0;
	float outVaule;
	srfData->gyoSum[srfData->axis++] = newVuale;
	if(srfData->axis == N)srfData->axis = 0;
	for(count = 0;count< N;count++){
		outVaule +=srfData-> gyoSum[count];
	}
	return outVaule/N;
}	

float app_echoGetDistance(TIM_TypeDef* TIMx,ultrasonicStruct_t *SRFData){
	float distance = 0,time = 0;
	if(echoRes(SRFData) == 1)app_echoOpentime(TIMx,SRFData);
	else{
		TIM_Cmd(TIMx,DISABLE);
		if(srfFlg){
			time = app_echoGettime(TIMx,SRFData);
			distance = time*0.017;
			if(distance > 300)distance = 300;
		}
		srfFlg = 0;
	}
//	distance = meanRecursiveFilter(distance,5,SRFData);
//	distance = distance*1.8; //校准原来距离
	return distance;
}

void EXTI9_5_IRQDivision(void){
	if(EXTI_GetITStatus(GPIO_TO_EXTI_Line(SRF04_ECHO2))!= RESET){
		if(ultrasonicTask.step == 2)
		SRF_04_Data2.getDistance = app_echoGetDistance(ECHO_TIMER,&SRF_04_Data2);
		EXTI_ClearITPendingBit(GPIO_TO_EXTI_Line(SRF04_ECHO2));
	}else if(EXTI_GetITStatus(GPIO_TO_EXTI_Line(SRF04_ECHO3))!= RESET){
		if(ultrasonicTask.step == 3)
		SRF_04_Data3.getDistance = app_echoGetDistance(ECHO_TIMER,&SRF_04_Data3);
		EXTI_ClearITPendingBit(GPIO_TO_EXTI_Line(SRF04_ECHO3));
	}else if(EXTI_GetITStatus(GPIO_TO_EXTI_Line(SRF04_ECHO4))!= RESET){
		if(ultrasonicTask.step == 4)
		SRF_04_Data4.getDistance = app_echoGetDistance(ECHO_TIMER,&SRF_04_Data4);
		EXTI_ClearITPendingBit(GPIO_TO_EXTI_Line(SRF04_ECHO4));
	}else if(EXTI_GetITStatus(GPIO_TO_EXTI_Line(SRF04_ECHO5))!= RESET){
		if(ultrasonicTask.step == 5)
		SRF_04_Data5.getDistance = app_echoGetDistance(ECHO_TIMER,&SRF_04_Data5);
		EXTI_ClearITPendingBit(GPIO_TO_EXTI_Line(SRF04_ECHO5));
	}else if(EXTI_GetITStatus(GPIO_TO_EXTI_Line(SRF04_ECHO6))!= RESET){
		if(ultrasonicTask.step == 6)
		SRF_04_Data6.getDistance = app_echoGetDistance(ECHO_TIMER,&SRF_04_Data6);
		EXTI_ClearITPendingBit(GPIO_TO_EXTI_Line(SRF04_ECHO6));
	}
}

void EXTI9_5_IRQHandler(void){
	EXTI9_5_IRQDivision();
}

void TIM4_IRQHandler(void){
	if (TIM_GetITStatus(ECHO_TIMER,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(ECHO_TIMER, TIM_IT_Update);
		SRF_04_Data1.msCount++;
		SRF_04_Data2.msCount++;
		SRF_04_Data3.msCount++;
		SRF_04_Data4.msCount++;
		SRF_04_Data5.msCount++;
		SRF_04_Data6.msCount++;
	}
}

void EXTI4_IRQHandler(void){
	if(EXTI_GetITStatus(GPIO_TO_EXTI_Line(SRF04_ECHO1))!= RESET){
		if(ultrasonicTask.step == 1)
		SRF_04_Data1.getDistance = app_echoGetDistance(ECHO_TIMER,&SRF_04_Data1);
		EXTI_ClearITPendingBit(GPIO_TO_EXTI_Line(SRF04_ECHO1));
	}
}
