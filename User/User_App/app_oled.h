#ifndef _APP_OLED_H
#define _APP_OLED_H

#define WAITTING_NEXT_TIME  12
#define NEXT_TIME_PERIOD     2

enum{
	NO_FLAG = 0,														//无操作标志位
	UPDATEMENU_FLAG,												//功能键按下显示标志位
	FUNCTION_MANUAL_FLAG,										//函数手动刷新
	FUNCTION_AUTO_FLAG,
	ERRORSAVE_FLAG,                         //保存出错标志位
	FLASH_SAVE_FLAG,                         //FLASH保存标志位
	CAIL_WAIT_FLAG
};

typedef struct {
	TaskHandle_t xHandleTask;
	uint8_t dataInitFlag;
	uint32_t loops;
}oledStruct_t;

typedef struct 
{
	u8 showFrom;														//显示选项起始编号
	u8 showTo;															//显示选项末尾编号
	u8 subMenuNumber;												//子菜单总数
	u8 currentOption;												//当前选项
	u8 *menuOption[20];											//选项内容
	struct menu **subMenu;									//子菜单
	struct menu *preMenu;										//上级菜单
	u8 displayFlag;													//刷新标志位
	void (**func)(void);										//执行函数	
}oledMenuStruct_t;

#endif

