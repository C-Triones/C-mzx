
/**
* Copyright (c), 2015-2025
* @file gui_widget_progbar.c
* @brief 进度条控件主文件
* @author jdh
* @date 2015/11/22
*/
 
/*********************************************************************
*							头文件
**********************************************************************/
 
#include "GUI_OLEDProgressBar.h"
#include "Driver_RMOLED.h"
#include "stdlib.h"
 
/*********************************************************************
*							静态变量
**********************************************************************/
 
/**
* @brief 百分比
*/
 
static uint8_t Percent = 0;

/*********************************************************************
*							静态函数
**********************************************************************/
 
/**
* @brief 控件显示
* @param handle:控件句柄
*/
 
static void show(Widget_Progbar_Handle handle);
 
/*********************************************************************
*							函数
**********************************************************************/
 
/**
* @brief 创建控件
* @param x:左上角x坐标
* @param y:左上角y坐标
* @param xsize:水平尺寸
* @param ysize:垂直尺寸
* @retval 控件句柄
*/
 
Widget_Progbar_Handle gui_widget_progbar_create(uint16_t x,uint16_t y,uint16_t xsize,uint16_t ysize)
{
	Widget_Progbar_Handle handle;
	
	//控件初始化
	handle = malloc(sizeof(*handle));
	handle->x = x;
	handle->y = y;
	handle->xsize = xsize;
	handle->ysize = ysize;
	
	//显示
	show(handle);
	
	return handle;
}
 
/**
* @brief 设置进度
* @param value:百分比,0-100
*/
 
void gui_widget_progbar_set_value(Widget_Progbar_Handle handle,uint8_t value)
{
	if (Percent == value)
	{
		return;
	}
	
	if (value < Percent)
	{
		//清除区域
		OLED_Clear();
	}
	
	//显示
	gui_fill_rect(handle->x + handle->xsize * Percent / 100,handle->y,
				  handle->x + handle->xsize * value / 100,handle->y + handle->ysize,1);
	Percent = value;
}
 
/**
* @brief 控件显示
* @param handle:控件句柄
*/
 
static void show(Widget_Progbar_Handle handle)
{
	//清除区域
	gui_fill_rect(handle->x,handle->y,handle->x + handle->xsize,handle->y + handle->ysize,0);
	//显示
	gui_draw_rect(handle->x,handle->y,handle->x + handle->xsize,handle->y + handle->ysize);
	Percent = 0;
}
