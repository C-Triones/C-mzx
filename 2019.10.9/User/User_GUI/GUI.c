#include "GUI.h"

#define GUI_TASK_PERIOD  100

GUIStruct_t GUI;
appStruct_t appGui;

/*GUI校准保存*/
void saveGUIFinish()
{
	GUI.alterType = GUI_ALTER_FINISH;
	GUI.workState = GUI_SAVE_FINISH;
	currentMenu -> displayFlag = FLASH_SAVE_FLAG;
}
/*GUI回复非校准状态*/
void resetGUIState()
{
	GUI.alterType = GUI_NO_NEED_ALTER;
	GUI.workState = GUI_NO_NEED_SAVE;
	currentMenu -> displayFlag = UPDATEMENU_FLAG;				//刷新一次菜单~
}

/*GUIoled初始化*/
void GUI_OLEDInit()
{
  menuInit();
}
/*GUI界面更新*/
double gui = 0;
void GUIUpdate(void *Parameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, GUI_TASK_PERIOD);
		//OLED_ShowString(20,2,"Save",16);
		PDout(7) = ~PDout(7);
		gui = gui + 0.1;
		menuUpdate(); 
	}
}
/*GUI类型初始化*/
void GUI_Init(void)
{                      
	GUI_OLEDInit();
	xTaskCreate(GUIUpdate,"WORK",GUI_STACK_SIZE,NULL,GUI_PRIORITY,&appGui.xHandleTask);
}
