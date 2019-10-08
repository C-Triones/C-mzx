#ifndef __GUI_H
#define __GUI_H

#include "app.h"
#include "GUI_OLED.h"

typedef enum{
	GUI_PRIORITY = 2,
	GUI_STACK_SIZE = 512,
}appGUI_e;



/*按键延时时间枚举*/
enum{
  KEY_EXPEDITE_LEVEL_1 = 20,
	KEY_EXPEDITE_LEVEL_2 = 50,
};
/*GUI调节状态枚举*/
enum{
	GUI_NO_NEED_ALTER = 0,	
  GUI_PID_CALIBRATE	,	
	GUI_ROBOT_DISTINGUISH	,
	GUI_LOCAL_ID_DISTINGUISH,
	GUI_TOF_CALIBRATE,
	GUI_IMU_CALIBRATE,
  GUI_GIMBAL_CALIBRATE,
	GUI_FOLLOW_GIMBAL_SET,
	GUI_CHASSIS_KB_ACC_SET,
	GUI_GIMBAL_CTR_SCALE_SET,
	GUI_GIMBAL_KB_SCALE_SET,
	GUI_CHASSIS_KB_SPEED_SET,
	GUI_CHASSIS_RC_SPEED_SET,
	GUI_SINGLE_RATE_SET,
	GUI_CONTINUOUS_RATE_SET,
	GUI_OUR_CAMP_SET,
  GUI_ALTER_FINISH	
};
/*GUI保存模式状态枚举*/
enum{
	GUI_NO_NEED_SAVE = 0,													
	GUI_CHOOSE,	
	GUI_SAVE_START,
  GUI_SAVE_BEING,	
  GUI_SAVE_FINISH			
};
/*GUI结构体*/
typedef struct 
{
	uint8_t testFlag;
	uint16_t alterType;
	uint16_t workState;
	uint16_t updateTime;
	uint8_t nullKeyFlag;
	uint32_t waitKeyTime[6];
	uint8_t workChoose[4];
	uint8_t workChooseList;
	
}GUIStruct_t;

extern GUIStruct_t GUI;

void GUI_Init(void);
void saveGUIFinish(void);
void resetGUIState(void);
void GUIUpdate(void *Parameters);
void GUI_OLEDInit(void);

#endif
