#ifndef __GUI_OLEDPROGRESSBAR_H
#define __GUI_OLEDPROGRESSBAR_H

#include "stm32f4xx.h"
#include "stdio.h"
/*********************************************************************
*							宏定义
**********************************************************************/
 
/**
* @brief 文本长度.单位:字节
*/
 
#define LEN_WIDGET_TEXT				32
 
/*********************************************************************
*							数据结构
**********************************************************************/
 
/**
* @brief 进度条数据结构
*/
 
typedef struct _Widget_Progbar
{
	//x轴位置
	uint16_t x;
	//y轴位置
	uint16_t y;
	//水平尺寸
	uint16_t xsize;
	//垂直尺寸
	uint16_t ysize;
}*Widget_Progbar_Handle;
 
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
 
Widget_Progbar_Handle gui_widget_progbar_create(uint16_t x,uint16_t y,uint16_t xsize,uint16_t ysize);
 
/**
* @brief 设置进度
* @param value:百分比,0-100
*/
 
void gui_widget_progbar_set_value(Widget_Progbar_Handle handle,uint8_t value);

#endif
