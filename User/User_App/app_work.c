#include "app.h"

#define WORK_TASK_PERIOD  1

uint32_t pwm =0;
uint8_t speed_cut = stop;
appStruct_t appWork;
robotSelectStruct_t robotSelect;

void app_fanMode(fanMode_e fanDirection)
{
	
}

void app_fan()
{
	PDout(15) = 1;
	PDout(14) = 1;
	vTaskDelay(800);
	PDout(15) = 0;
	PDout(14) = 0;
	vTaskDelay(500);
	outfireRobotState.fireBassarl = true;
}


calibrationFinish_e checkFire(void){
	calibrationFinish_e finshFlag;
	finshFlag = CALIBRATION_NULL;
	if(outfireRobotState.fireBassarl == true){
		if(adcTestData.adcData[L_ADC] < 300|| adcTestData.adcData[R_ADC] < 300){
			app_fan();
			finshFlag = CALIBRATION_WAITING;
		}
		else if(adcTestData.adcData[L_ADC] > 300 && adcTestData.adcData[R_ADC] > 300){
			outfireRobotState.fireBassarl = false;
			finshFlag = CALIBRATION_FINISHED;
		}
	}
		return finshFlag;
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
	switch(outfireRobotState.step){
			case INIT: app_WorkCommandReset(); break;
			case READY: app_outfireTwoWorkReady(); break;
			case DOING: app_outfireTwoWorkDoing(); break;
			case FINISH: break;
			default:break;
	}
}

void app_rescueWorkCommandReset(void){
	command = RESCUE_STOP;
	rescueRobotState.testTarget = WAITING;
	rescueRobotState.lastMoveWays = OTHER;
	rescueRobotState.moveWays = STOP;
	rescueRobotState.beginFlag = FREE;
	rescueRobotState.workMode = TEST;
	rescueRobotState.step = READY;	
	LimiFlag.forward = go;
	LimiFlag.left    = go;
	LimiFlag.right   = go;
	speed_cut        = stop;

}
void app_judgeFunc(void){
	uint8_t roadCase = 1;
	if(robotSelect.robotSelect == OUT_FIRE1){
		switch(roadCase){
			case 1:{
				if(outfireRobotState.fireArray[NINTH_FIRE] == 0&&outfireRobotState.fireArray[THIRD_FIRE] == 0&&outfireRobotState.fireArray[SECOND_FIRE] == 0 && outfireRobotState.fireArray[FIRST_FIRE] == 0){
						outfireRobotState.returnFlag[RETURN] = 1;
						break;
					}
						roadCase = 2;
				}
			case 2:{
				if(outfireRobotState.fireArray[NINTH_FIRE] == 0&&outfireRobotState.fireArray[THIRD_FIRE] == 0&&outfireRobotState.fireArray[SECOND_FIRE] == 0){
						outfireRobotState.returnFlag[FIRST_FIRE] = 1;
						break;
					}
						roadCase = 3;
				}
			case 3:{
				if(outfireRobotState.fireArray[THIRD_FIRE] == 0&&outfireRobotState.fireArray[SECOND_FIRE] == 0){
						outfireRobotState.returnFlag[NINTH_FIRE] = 1;
						break;
					}
						roadCase = 4;
				}
			case 4:{
				if(outfireRobotState.fireArray[SECOND_FIRE] == 0){
						outfireRobotState.returnFlag[THIRD_FIRE] = 1;
						break;
					}
						roadCase = 5;
				}
			case 5:{
				outfireRobotState.returnFlag[SECOND_FIRE] = 1;
				roadCase = 1;
				break;
				}
		}
	}else if(robotSelect.robotSelect == OUT_FIRE2){
		switch(roadCase){
			case 1:{
				if(outfireRobotState.fireArray[EIGHTH_FIRE] == 0&&outfireRobotState.fireArray[SENVENTH_FIRE] == 0&&outfireRobotState.fireArray[FOURTH_FIRE] == 0 && outfireRobotState.fireArray[FIFTH_FIRE] == 0 && outfireRobotState.fireArray[SIXTH_FIRE] == 0){
						outfireRobotState.returnFlag[RETURN] = 1;
						break;
					}
						roadCase = 2;
				}
			case 2:{
				if(outfireRobotState.fireArray[SENVENTH_FIRE] == 0&&outfireRobotState.fireArray[FOURTH_FIRE] == 0 && outfireRobotState.fireArray[FIFTH_FIRE] == 0 && outfireRobotState.fireArray[SIXTH_FIRE] == 0){
						outfireRobotState.returnFlag[EIGHTH_FIRE] = 1;
						break;
					}
						roadCase = 3;
				}
			case 3:{
				if(outfireRobotState.fireArray[FOURTH_FIRE] == 0 && outfireRobotState.fireArray[FIFTH_FIRE] == 0 && outfireRobotState.fireArray[SIXTH_FIRE] == 0){
						outfireRobotState.returnFlag[SENVENTH_FIRE] = 1;
						break;
					}
						roadCase = 4;
				}
			case 4:{
				if(outfireRobotState.fireArray[FIFTH_FIRE] == 0 && outfireRobotState.fireArray[SIXTH_FIRE] == 0){
						outfireRobotState.returnFlag[FOURTH_FIRE] = 1;
						break;
					}
						roadCase = 5;
				}
			case 5:{
				if(outfireRobotState.fireArray[SIXTH_FIRE] == 0){
						outfireRobotState.returnFlag[FIFTH_FIRE] = 1;
						break;
					}
						roadCase = 6;
				}
			case 6:{
				outfireRobotState.returnFlag[SIXTH_FIRE] = 1;
				roadCase = 1;
				break;
				}
		}
	}
	if(outfireRobotState.returnFlag[RETURN] == 1){   //全无火   直接到最后一步
			outfireRobotState.robotTaskstep = RETURN;
	}
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
void app_WorkUpdata(robotSelectStruct_t *robotSelect) 	//机器人任务分类
{
	
	switch(robotSelect->robotSelect){
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
		app_WorkUpdata(&robotSelect);
		vTaskDelay(1);
	}
}

void app_WorkTaskInit(void){

	xTaskCreate(app_WorkTask,"WORK",WORK_STACK_SIZE,NULL,WORK_PRIORITY,&appWork.xHandleTask);

}

