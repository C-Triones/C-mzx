#ifndef __HJ_USART_H
#define __HJ_USART_H
#include "BSP_GPIO.h"
#include "Driver_Servo.h"
#define WIFI_RCC RCC_APB2Periph_USART1
#define WIFI_USART USART1
#define WIFI_BAUD 9600
#define WIFI_TX_GPIO BSP_GPIOA9
#define WIFI_RX_GPIO BSP_GPIOA10

void wifi_Init(void);
void wifiControl(u8 command);
extern unsigned char command;


#endif
