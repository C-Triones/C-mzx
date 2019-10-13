#ifndef __HJ_USART_H
#define __HJ_USART_H
#include "BSP_GPIO.h"
#include "app.h"
#define WIFI_RCC RCC_APB2Periph_USART1
#define WIFI_USART USART1
#define WIFI_BAUD 9600
#define WIFI_TX_GPIO BSP_GPIOA9
#define WIFI_RX_GPIO BSP_GPIOA10

typedef enum{
	RESCUE_STOP = 0x30,
	RESCUE_FORWARD,
	RESCUE_BACK,
	RESCUE_LEFT,
	RESCUE_RIGHT,
	CLAW_UP,
	CLAW_DOWN,
	CLAW_HOLD,
	CLAW_UNDO,
	CAMERA_UP,
	CAMERA_DOWN,	
}USARTCONTROL_e;

typedef enum{
 claw_STOP =0,
 claw_UP,
 claw_DOWN,
 claw_HOLD,
 claw_UNON,	
}CLAWMODE_e;

typedef enum{
 camera_STOP =0,
 camera_UP,
 camera_DOWN,
}CAMERAMODE_e;

extern uint8_t command;
extern uint8_t initFlg;//校验完成标志位
extern uint8_t fuze;//校验计数

void wifi_Init(void);
void wifiControl(uint8_t command);



#endif
