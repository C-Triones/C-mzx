#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "stm32f4xx.h"
#include "stdlib.h"
#include "stdio.h"

#include "BSP_GPIO.h"

typedef struct
{
	CAN_TypeDef* CANx;			//CANͨ��
	BSP_GPIOSource_TypeDef *CANx_RX;	//CANx_RX ����
	BSP_GPIOSource_TypeDef *CANx_TX;	//CANx_TX ����
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;	//CANͨ�����ã����������ʵȵ�
}BSP_CAN_TypeDef;

typedef struct
{
	CAN_TypeDef* 	CANx;
	CanTxMsg* 		TxMessage;
}BSP_CANSend_TypeDef;

void BSP_CAN_Mode_Init(BSP_CAN_TypeDef *BSP_CANx,u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u8 PreemptionPriority,u8 SubPriority);
 u8	 BSP_CAN_Send_Msg(BSP_CAN_TypeDef *BSP_CANx,CanTxMsg *TxMessage);
 u8	 BSP_CAN_Receive_Msg(BSP_CAN_TypeDef *BSP_CANx,CanRxMsg *RxMessage);

extern const CAN_FilterInitTypeDef  CAN1_FilterInitStructure;
extern const CAN_FilterInitTypeDef  CAN2_FilterInitStructure;

#endif
