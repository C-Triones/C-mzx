#include "stm32f4xx.h"
//#include "Driver_SRF_05.h"
//#include "Driver_Servo.h"
//#include "vl53l0x.h"
#include "delay.h"
#include "Driver_LED.h"
#include "HJ_USART.h"
int main(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemInit();
	delay_init(168);
//	SysTick_Init();
//	SRF_05_Init();
	Led_Init();
//	servo_Init();
//	servoStart();
	wifi_Init();
//	sensor_init();
//	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	while(1){
//		servoTest();
//		VL53L0X_PerformSingleRangingMeasurement(&vl53l0x_dev, &vl53l0xData);
//		Led_On();
//		SRF_05_Start();
		wifiControl(command);
	}
}
