
/**
* Copyright (c), 2015-2025
* @file gui_widget_progbar.c
* @brief �������ؼ����ļ�
* @author jdh
* @date 2015/11/22
*/
 
/*********************************************************************
*							ͷ�ļ�
**********************************************************************/
 
#include "GUI_OLEDProgressBar.h"
#include "Driver_RMOLED.h"
#include "stdlib.h"
 
/*********************************************************************
*							��̬����
**********************************************************************/
 
/**
* @brief �ٷֱ�
*/
 
static uint8_t Percent = 0;

/*********************************************************************
*							��̬����
**********************************************************************/
 
/**
* @brief �ؼ���ʾ
* @param handle:�ؼ����
*/
 
static void show(Widget_Progbar_Handle handle);
 
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
 
Widget_Progbar_Handle gui_widget_progbar_create(uint16_t x,uint16_t y,uint16_t xsize,uint16_t ysize)
{
	Widget_Progbar_Handle handle;
	
	//�ؼ���ʼ��
	handle = malloc(sizeof(*handle));
	handle->x = x;
	handle->y = y;
	handle->xsize = xsize;
	handle->ysize = ysize;
	
	//��ʾ
	show(handle);
	
	return handle;
}
 
/**
* @brief ���ý���
* @param value:�ٷֱ�,0-100
*/
 
void gui_widget_progbar_set_value(Widget_Progbar_Handle handle,uint8_t value)
{
	if (Percent == value)
	{
		return;
	}
	
	if (value < Percent)
	{
		//�������
		OLED_Clear();
	}
	
	//��ʾ
	gui_fill_rect(handle->x + handle->xsize * Percent / 100,handle->y,
				  handle->x + handle->xsize * value / 100,handle->y + handle->ysize,1);
	Percent = value;
}
 
/**
* @brief �ؼ���ʾ
* @param handle:�ؼ����
*/
 
static void show(Widget_Progbar_Handle handle)
{
	//�������
	gui_fill_rect(handle->x,handle->y,handle->x + handle->xsize,handle->y + handle->ysize,0);
	//��ʾ
	gui_draw_rect(handle->x,handle->y,handle->x + handle->xsize,handle->y + handle->ysize);
	Percent = 0;
}
