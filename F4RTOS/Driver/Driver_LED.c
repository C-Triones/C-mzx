#include "Driver_LED.h"

void Led_Init(void){
	BSP_GPIO_Init(BSP_GPIOF9,GPIO_Mode_Out_PP);
	LED = 1;
}

void Led_On(void){
	LED = ~LED;
}
