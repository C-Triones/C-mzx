#include "driver.h"

void driver_FanMotorGPIOConfig(void)
{
	BSP_GPIO_Init(BSP_GPIOD12,GPIO_Mode_Out_PP);
	BSP_GPIO_Init(BSP_GPIOD13,GPIO_Mode_Out_PP);
	Motor1 = 0;
	Motor2 = 0;
				
	BSP_GPIO_Init(BSP_GPIOD14,GPIO_Mode_Out_PP);
	BSP_GPIO_Init(BSP_GPIOD15,GPIO_Mode_Out_PP);
	Motor3 = 0;
	Motor4 = 0;
}

void driver_InitFanMotor(void)
{
	driver_FanMotorGPIOConfig();
}

void driver_FanMotorFront(void)
{
	Motor1 = 1;
	Motor2 = 1;
	Motor3 = 1;
	Motor4 = 1;
}
void driver_FanMotorBehind(void)
{
	Motor3 = 1;
	Motor4 = 1;
}

void driver_FanMotorOff(void)
{
	Motor1 = 0;
	Motor2 = 0;
	Motor3 = 0;
	Motor4 = 0;
}

