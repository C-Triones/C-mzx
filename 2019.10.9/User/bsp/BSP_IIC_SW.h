#ifndef __BSP_IIC_SW_H
#define __BSP_IIC_SW_H

#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"

//include "BSP_GPIO.h"
#define RCC_IIC_SW RCC_APB2Periph_GPIOB 
#define IIC_WR	0		/* д����bit */
#define IIC_RD	1		/* ������bit */

//IO��������
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO��������	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	
#define READ_SCL   PBin(8)  //����SCL
#define READ_SDA   PBin(9)  //����SDA 

#define IIC_Delay()	IIC_SW_Delay(1)

//IIC���в�������
void BSP_IIC_SW_Init(void);	
unsigned char BSP_IIC_WriteData(u8 dev_addr,u8 regAddr,u8 data);
unsigned char BSP_IIC_ReadData(u8 dev_addr,u8 regAddr,u8 *buf,u8 length);
void BSP_IIC_Start(void);		//����IIC��ʼ�ź�
void BSP_IIC_Stop(void);		//����IICֹͣ�ź�
void BSP_IIC_Send_Byte(u8 txd);		//IIC����һ���ֽ�
u8 BSP_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 BSP_IIC_Wait_Ack(void);	//IIC�ȴ�ACK�ź�
void BSP_IIC_Ack(void);			//IIC����ACK�ź�
void BSP_IIC_NAck(void);		//IIC������ACK�ź� 
uint8_t BSP_IIC_CheckDevice(uint8_t Device_Address);//����豸
void IIC_SW_Delay(unsigned int t);

#endif
