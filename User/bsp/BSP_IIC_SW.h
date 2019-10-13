#ifndef __BSP_IIC_SW_H
#define __BSP_IIC_SW_H

#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"

//include "BSP_GPIO.h"
#define RCC_IIC_SW RCC_APB2Periph_GPIOB 
#define IIC_WR	0		/* 写控制bit */
#define IIC_RD	1		/* 读控制bit */

//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	
#define READ_SCL   PBin(8)  //输入SCL
#define READ_SDA   PBin(9)  //输入SDA 

#define IIC_Delay()	IIC_SW_Delay(1)

//IIC所有操作函数
void BSP_IIC_SW_Init(void);	
unsigned char BSP_IIC_WriteData(u8 dev_addr,u8 regAddr,u8 data);
unsigned char BSP_IIC_ReadData(u8 dev_addr,u8 regAddr,u8 *buf,u8 length);
void BSP_IIC_Start(void);		//发送IIC开始信号
void BSP_IIC_Stop(void);		//发送IIC停止信号
void BSP_IIC_Send_Byte(u8 txd);		//IIC发送一个字节
u8 BSP_IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 BSP_IIC_Wait_Ack(void);	//IIC等待ACK信号
void BSP_IIC_Ack(void);			//IIC发送ACK信号
void BSP_IIC_NAck(void);		//IIC不发送ACK信号 
uint8_t BSP_IIC_CheckDevice(uint8_t Device_Address);//检查设备
void IIC_SW_Delay(unsigned int t);

#endif
