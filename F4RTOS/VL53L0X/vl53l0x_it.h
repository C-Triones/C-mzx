#ifndef __VL53L0X_IT_H
#define __VL53L0X_IT_H

#include "vl53l0x.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ̽����STM32F407������
//VL53L0X-�жϲ���ģʽ ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/7/1
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

void vl53l0x_interrupt_test(VL53L0X_Dev_t *dev);
void vl53l0x_interrupt_start(VL53L0X_Dev_t *dev,uint8_t mode);


#endif
