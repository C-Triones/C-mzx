#include "app.h"

#define WORK_TASK_PERIOD  1
uint32_t pwm =0;

appStruct_t appWork;


void app_fanMode(fanMode_e fanDirection)
{
	
}

void app_fan()
{
	PDout(15) = 1;
	vTaskDelay(800);
	PDout(15) = 0;
}

void app_WorkCommandReset(void)    //恢复初始状态标志位
{
	outfireRobotState.testTarget = WAITING;
	outfireRobotState.lastMoveWays = OTHER;
	outfireRobotState.moveWays = STOP;
	outfireRobotState.step = READY;
	outfireRobotState.beginFlag = FREE;
	outfireRobotState.workMode = TEST;
	driver_FanMotorOff();	
}

void app_rescueWorkCommandReset(void){
	rescueRobotState.step = READY;
}

/***灭火1机器人主任务**/
void app_outfireOneRobotTask(void){
		switch(outfireRobotState.step){
			case INIT: app_WorkCommandReset(); break;
			case READY: app_outfireOneWorkReady(); break;
			case DOING: app_outfireOneWorkDoing(); break;
			case FINISH: break;
			default:break;
		}
}
	/***灭火机器人2主任务**/
void app_outfireTwoRobotTask(void){

}
	/***救援机器人主任务**/
void app_rescueRobotTask(void){
	switch(rescueRobotState.step){
			case INIT: app_rescueWorkCommandReset(); break;
			case READY: app_rescueWorkReady(); break;
			case DOING: app_rescueWorkDoing(); break;
			case FINISH: break;
			default:break;
		}
	
}

void app_WorkUpdata(robotType_e robotType) 	//机器人任务分类
{
	
	switch(robotType){
		case OUT_FIRE1:
			app_outfireOneRobotTask();
			break;
		case OUT_FIRE2:
			app_outfireTwoRobotTask();
			break;
		case RESCUE:
			app_rescueRobotTask();
			break;
	}
}
void app_WorkTask(void *Parameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, WORK_TASK_PERIOD);
		app_WorkUpdata( RESCUE);	
		vTaskDelay(1);
		app_CAMERA_UPorDOWN(claw_UNON,pwm);
	}
}

void app_WorkTaskInit(void)
{
  xTaskCreate(app_WorkTask,"WORK",WORK_STACK_SIZE,NULL,WORK_PRIORITY,&appWork.xHandleTask);
	rescueRobotState.step = INIT;
	command = '0';
}

