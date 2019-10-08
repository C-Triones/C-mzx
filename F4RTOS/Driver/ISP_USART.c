#include "HJ_USART.h"

unsigned char command = 0;
void USART1_IRQHandler(void){
	if(USART_GetITStatus(WIFI_USART,USART_IT_RXNE)!=RESET){
		command = USART_ReceiveData(WIFI_USART);
		while(USART_GetFlagStatus(WIFI_USART,USART_FLAG_RXNE));
//		USART_ClearFlag(USART1,RESET);
//		wifiControl(command);

//		command = 0x00;
	}
}


