#include "app.h"

void app_rescueWorkReady(void)
{
	/*������*/ //�ð�������С������//
	rescueRobotState.step = DOING;
	command = '0';
}
/***Ѱ������**/
void app_rescueWorkDoing(void){
	wifiControl(command);
}
 
///////////��Ԯ���ڿ�����λ////////////////
void app_UCLIMI_FORNT(uint8_t distance){//ǰ��λ
 
} 
void app_UCLIMI_LEFT(uint8_t distance){//����λ
	
}  
void app_UCLIMI_RIGHT(uint8_t distance){//����λ
	
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
