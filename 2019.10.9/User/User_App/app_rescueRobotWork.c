#include "app.h"

void app_rescueWorkReady(void)
{
	/*待补充*/ //用按键控制小车启动//
	rescueRobotState.step = DOING;
	command = '0';
}
/***寻火任务**/
void app_rescueWorkDoing(void){
	wifiControl(command);
}
 
///////////救援串口控制限位////////////////
void app_UCLIMI_FORNT(uint8_t distance){//前限位
 
} 
void app_UCLIMI_LEFT(uint8_t distance){//左限位
	
}  
void app_UCLIMI_RIGHT(uint8_t distance){//右限位
	
}
///////////rescue_AUTOTASK/////////////////
void rescue_AUTOTASK_PUTCLAW(void){
		app_CLAW_HOLDorUNON(claw_UNON,185);
    vTaskDelay(20);		
		app_CLAW_UPorDOWN(claw_DOWN,268);
		app_CAMERA_UPorDOWN(camera_DOWN,220);	
}
void rescue_AUTOTASK_HOLDCLAW(void){
		app_CLAW_HOLDorUNON(claw_HOLD,318);
    vTaskDelay(500);	
		app_CLAW_UPorDOWN(claw_UP,240);
		app_CAMERA_UPorDOWN(camera_UP,130);
}
