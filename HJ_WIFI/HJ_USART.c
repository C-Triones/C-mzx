#include "HJ_USART.h"
#include "Driver_LED.h"


void wifi_Init(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(WIFI_RCC,ENABLE);
	
	BSP_GPIO_Init(WIFI_TX_GPIO,GPIO_Mode_AF_PP);
	BSP_GPIO_Init(WIFI_RX_GPIO,GPIO_Mode_AF_PP);
	
	GPIO_Pin_TO_PinAFConfig(WIFI_TX_GPIO,GPIO_AF_USART1);
	GPIO_Pin_TO_PinAFConfig(WIFI_RX_GPIO,GPIO_AF_USART1);
	
	USART_InitStructure.USART_BaudRate=WIFI_BAUD;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Init(USART1,&USART_InitStructure);
	NVIC_Init(&NVIC_InitStructure);

}

void wifiControl(u8 command){
//	if(command == 'a') LED = 1;
//	else if(command == 'b') LED = 0;
	switch(command){
		case 'a':
			servo1Data.division = FORWARD;
		  LED = 1;
			command = 's';
			break;
		case 'b':
			servo1Data.division = BACK;		 
	    LED =0;
			command = 's';
			break;
	}
}

