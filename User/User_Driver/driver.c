#include "driver.h"
void driver_Init(void)
{
	driver_InitOLED();                  /*OLED��ʾ����ʼ��*/
	driver_InitPhotoelectricSwitchHard();	  /*��翪�س�ʼ��*/
	ADC_Configuration();
	driver_echo();
	driver_InitSteeringEngineSpeed();   /*���߶����ʼ��*/
	driver_InitFanMotor();
	driver_InitKeyHard();
  wifi_Init();
	BSP_GPIO_Init(BSP_GPIOD7,GPIO_Mode_Out_PP);
}
