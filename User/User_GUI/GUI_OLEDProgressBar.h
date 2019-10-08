#ifndef __GUI_OLEDPROGRESSBAR_H
#define __GUI_OLEDPROGRESSBAR_H

#include "stm32f4xx.h"
#include "stdio.h"
/*********************************************************************
*							�궨��
**********************************************************************/
 
/**
* @brief �ı�����.��λ:�ֽ�
*/
 
#define LEN_WIDGET_TEXT				32
 
/*********************************************************************
*							���ݽṹ
**********************************************************************/
 
/**
* @brief ���������ݽṹ
*/
 
typedef struct _Widget_Progbar
{
	//x��λ��
	uint16_t x;
	//y��λ��
	uint16_t y;
	//ˮƽ�ߴ�
	uint16_t xsize;
	//��ֱ�ߴ�
	uint16_t ysize;
}*Widget_Progbar_Handle;
 
/*********************************************************************
*							����
**********************************************************************/
 
/**
* @brief �����ؼ�
* @param x:���Ͻ�x����
* @param y:���Ͻ�y����
* @param xsize:ˮƽ�ߴ�
* @param ysize:��ֱ�ߴ�
* @retval �ؼ����
*/
 
Widget_Progbar_Handle gui_widget_progbar_create(uint16_t x,uint16_t y,uint16_t xsize,uint16_t ysize);
 
/**
* @brief ���ý���
* @param value:�ٷֱ�,0-100
*/
 
void gui_widget_progbar_set_value(Widget_Progbar_Handle handle,uint8_t value);

#endif
