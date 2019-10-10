#ifndef __BSP_H
#define __BSP_H

#include "stm32f4xx.h"
#include "stdlib.h"
#include "stdio.h"

//宏定义串口接收数组长度
#define	Length_USART1_RX_Buff 256
#define	Length_USART2_RX_Buff 512
#define	Length_USART3_RX_Buff 512
#define	Length_UART4_RX_Buff 	256
#define	Length_UART5_RX_Buff 	256
#define	Length_USART6_RX_Buff 128
#define	Length_UART7_RX_Buff 	256
#define	Length_UART8_RX_Buff 	256

//宏定义串口发送数组长度
#define	Length_USART1_TX_Buff 256
#define	Length_USART2_TX_Buff 512
#define	Length_USART3_TX_Buff 512
#define	Length_UART4_TX_Buff 	256
#define	Length_UART5_TX_Buff 	256
#define	Length_USART6_TX_Buff 128
#define	Length_UART7_TX_Buff 	256
#define	Length_UART8_TX_Buff 	256

#include "BSP_GPIO.h"
#include "BSP_Timer.h"
#include "BSP_PWM.h"
#include "BSP_EXIT.h"
#include "BSP_DMA.h"

#include "BSP_USART.h"
#include "BSP_CAN.h"
//#include "BSP_Flash.h"



#endif






