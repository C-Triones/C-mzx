#include "driver.h"
void driver_Init(void)
{
	driver_InitOLED();                  /*OLED显示屏初始化*/
	driver_InitPhotoelectricSwitchHard();	  /*光电开关初始化*/
	ADC_Configuration();
	driver_echo();
	driver_InitSteeringEngineSpeed();   /*行走舵机初始化*/
	driver_InitFanMotor();
	driver_InitKeyHard();
  wifi_Init();
	BSP_GPIO_Init(BSP_GPIOD7,GPIO_Mode_Out_PP);
}
