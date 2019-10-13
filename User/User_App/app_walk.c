#include "app.h"
#include "GUI.h"

#define WALK_TASK_PERIOD  1
#define CALIBRATION_DISTANCE  0.3f
#define GO_STRAIGHT_MIDDLE 20
#define GO_STRAIGHT_RATIO  4.0f 						//轮子差速大小
#define CALIBRATION_TIME_RATIO 30.0f
#define GO_STRAIGHT_ADD    20
#define WHELL_RATE_ADD 		10
#define MAX_DIFFERENCE_VALUE 8 							//最大差值
#define MIN_DISTANCE_VALUE 6						//距墙最小距离之和

appStruct_t appWalk;
moveWays_e finishFlag;
calibrationFinish_e calibrationFinish;
void app_LeftWheel(uint8_t mode,uint32_t rate){    //向前后左转
	if(mode == 1){		
		TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]+rate);
	}else if(mode == 2){
		TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]-rate);
	}
}

void app_RightWheel(uint8_t mode,uint32_t rate){ // 右前 右后
	if(mode == 1){		
		TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]-rate);
	}else if(mode == 2){
		TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]+rate);
	}
}


void app_CLAW_UPorDOWN(uint8_t mode,uint32_t rata){//爪子1上2下
	if(mode==claw_UP){
	TIM_SetCompare3(TIM3,rata);
	}
	else if (mode==claw_DOWN){
	TIM_SetCompare3(TIM3,rata);
	}
		else if(mode==0){
	TIM_SetCompare3(TIM3,0);
	}
}
void app_CLAW_HOLDorUNON(uint8_t mode,uint32_t rata){	//爪子3紧4松
		if(mode==claw_HOLD){
	TIM_SetCompare4(TIM3,rata);   
	}
	else if (mode==claw_UNON){
	TIM_SetCompare4(TIM3,rata);
	}
	else if(mode==0){
	TIM_SetCompare4(TIM3,0);
	}
}
void app_CAMERA_UPorDOWN(uint8_t mode,uint32_t rata){//相机1上2下
		if(mode==1){
	TIM_SetCompare1(TIM2,rata);
	}
	else if (mode==2){
	TIM_SetCompare1(TIM2,rata);
	}
		else if(mode==0){
	TIM_SetCompare1(TIM2,0);
	}
}

void app_goOtherAction(uint16_t goTime,turnDirection_e direction,handDirection_e hand){
	switch(hand){
		case FRONT:{
			switch(direction){
				case NO_TURN:{
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
					vTaskDelay(goTime);
					app_LeftWheel(FRONT,parameter[NAME_SET_ZERO__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_SET_ZERO__RIGHT_RATE]);
					break;
				}
				case LEFT:{
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE] - WHELL_RATE_ADD);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
					vTaskDelay(goTime);
					app_LeftWheel(FRONT,parameter[NAME_SET_ZERO__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_SET_ZERO__RIGHT_RATE]);
					break;
				}
				case RIGHT:{
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE] - WHELL_RATE_ADD);
					vTaskDelay(goTime);
					app_LeftWheel(FRONT,parameter[NAME_SET_ZERO__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_SET_ZERO__RIGHT_RATE]);
					break;
				
				}
			}
			break;
		}
		case BEHIND:{
			switch(direction){
				case NO_TURN:{
					app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
					app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
					vTaskDelay(goTime);
					app_LeftWheel(BEHIND,parameter[NAME_SET_ZERO__LEFT_RATE]);
					app_RightWheel(BEHIND,parameter[NAME_SET_ZERO__RIGHT_RATE]);
					break;
				}
				case LEFT:{
					app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE] - WHELL_RATE_ADD);
					app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
					vTaskDelay(goTime);
					app_LeftWheel(BEHIND,parameter[NAME_SET_ZERO__LEFT_RATE]);
					app_RightWheel(BEHIND,parameter[NAME_SET_ZERO__RIGHT_RATE]);
					break;
				}
				case RIGHT:{
					app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
					app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE] - WHELL_RATE_ADD);
					vTaskDelay(goTime);
					app_LeftWheel(BEHIND,parameter[NAME_SET_ZERO__LEFT_RATE]);
					app_RightWheel(BEHIND,parameter[NAME_SET_ZERO__RIGHT_RATE]);
					break;
				}
			}
			break;	
		}
	}
}

void app_turnAngleDirection(uint8_t leftWheelDirection,uint32_t leftWheelRate,
                            uint8_t rightWheelDirection,uint32_t rightWheelRate,
														uint32_t WaitingTime){
	TickType_t xLastWakeTime = xTaskGetTickCount();	
	const portTickType xFrequency = pdMS_TO_TICKS(WaitingTime); 
	if(outfireRobotState.beginFlag == FREE || rescueRobotState.beginFlag == FREE){
		outfireRobotState.beginFlag = BUSY;
		rescueRobotState.beginFlag = BUSY;
		app_LeftWheel(leftWheelDirection,leftWheelRate);
		app_RightWheel(rightWheelDirection,rightWheelRate);
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]);
		TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]);
		outfireRobotState.beginFlag = FREE;
		rescueRobotState.beginFlag = FREE;
	}
}
														

void app_walkStop(void){
	if(outfireRobotState.lastMoveWays != STOP){
		TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]);
		TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]);
	}
}
void app_setZero(void){
	if(outfireRobotState.lastMoveWays != SET_ZERO){
		TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]);
		TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]);
	}
}



void app_goStraight(void){
	if(outfireRobotState.lastMoveWays != GO_STRAIGHT){
		app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
		app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
	}
}

void app_goBack(uint16_t goTime,turnDirection_e direction){
	switch(direction){
		case NO_TURN:{
			app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
			app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
			vTaskDelay(goTime);
			app_LeftWheel(BEHIND,parameter[NAME_SET_ZERO__LEFT_RATE]);
			app_RightWheel(BEHIND,parameter[NAME_SET_ZERO__RIGHT_RATE]);
			break;
		}
		case LEFT:{
			app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE] - WHELL_RATE_ADD);
			app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
			vTaskDelay(goTime);
			app_LeftWheel(BEHIND,parameter[NAME_SET_ZERO__LEFT_RATE]);
			app_RightWheel(BEHIND,parameter[NAME_SET_ZERO__RIGHT_RATE]);
			break;
		}
		case RIGHT:{
			app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
			app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE] - WHELL_RATE_ADD);
			vTaskDelay(goTime);
			app_LeftWheel(BEHIND,parameter[NAME_SET_ZERO__LEFT_RATE]);
			app_RightWheel(BEHIND,parameter[NAME_SET_ZERO__RIGHT_RATE]);
			break;
		
		}
	}
}

void calibrationTostraight(){
	uint32_t timeSumLeft;
	uint32_t timeSumRight;
	float differenceValueLeft;
	float differenceValueRight;
	float differenceValueLeftCali;
	float differenceValueRightCali;
	
	differenceValueLeft = fabs(SRF_04_Data3.getDistance + SRF_04_Data4.getDistance);
	differenceValueRight = fabs(SRF_04_Data3.getDistance + SRF_04_Data4.getDistance);
	differenceValueLeftCali = (26 - differenceValueLeft);
	differenceValueRightCali = (26 - differenceValueRight);
	timeSumLeft = CALIBRATION_TIME_RATIO*differenceValueLeftCali;
	timeSumRight = CALIBRATION_TIME_RATIO*differenceValueRightCali;
	if(differenceValueLeft < MIN_DISTANCE_VALUE){
		app_goOtherAction(timeSumLeft,RIGHT,FRONT);
		app_goOtherAction(timeSumLeft,LEFT,FRONT);
	}
	if(differenceValueRight < MIN_DISTANCE_VALUE){
		app_goOtherAction(timeSumRight,LEFT,FRONT);
		app_goOtherAction(timeSumRight,RIGHT,FRONT);
	}
}

float differenceValue;
void calibrationGostraight(turnDirection_e direction){
	float differenceSum;
	switch(direction){
		case LEFT:{
			if(SRF_04_Data3.getDistance <= 25 && SRF_04_Data4.getDistance <= 25){
				differenceValue = fabs(SRF_04_Data3.getDistance - SRF_04_Data4.getDistance);
				differenceSum = GO_STRAIGHT_RATIO*differenceValue;
				if(SRF_04_Data3.getDistance > SRF_04_Data4.getDistance){
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]-differenceSum);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
				}
				if(SRF_04_Data3.getDistance < SRF_04_Data4.getDistance){
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]-differenceSum);    //需要加补偿值
				}
			}else{
				app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
				app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
			}
		break;
		}
		case RIGHT:{
			if(SRF_04_Data5.getDistance <= 25 && SRF_04_Data6.getDistance <= 25){
				differenceValue = fabs(SRF_04_Data5.getDistance - SRF_04_Data6.getDistance);
				differenceSum = GO_STRAIGHT_RATIO*differenceValue;
				if(SRF_04_Data5.getDistance > SRF_04_Data6.getDistance){
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]-differenceSum);
				}
				else if(SRF_04_Data5.getDistance < SRF_04_Data6.getDistance){
					app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]-differenceSum);
					app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);	
				}
			}
			else{
				app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
				app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
			}
		break;
		}
		case NO_TURN:{
		break;
		} 
	}
}
calibrationFinish_e app_findFire(void){
	float calibrationData;
	calibrationFinish_e finshFlag;
	finshFlag = CALIBRATION_NULL;
	calibrationData = adcTestData.adcData[L_ADC] - adcTestData.adcData[R_ADC];
	if(calibrationData > 10){
		app_LeftWheel(FRONT,12);
		app_RightWheel(FRONT,5);
		finshFlag = CALIBRATION_WAITING;
	}else if(calibrationData < -10){
		app_LeftWheel(FRONT,5);
		app_RightWheel(FRONT,12);
		finshFlag = CALIBRATION_WAITING;
	}else if(calibrationData != 0){
		app_LeftWheel(FRONT,20);
		app_RightWheel(FRONT,20);
		finshFlag = CALIBRATION_FINISHED;
	}
	return finshFlag;
}


calibrationFinish_e app_calibration(turnDirection_e direction){      //对位函数
	float calibrationData;
	calibrationFinish_e finshFlag;
	finshFlag = CALIBRATION_NULL;
	if(direction == LEFT){    //使用左侧测量还是右侧测量
		calibrationData = SRF_04_Data3.getDistance - SRF_04_Data4.getDistance;
		if(calibrationData > CALIBRATION_DISTANCE) 
		{
			app_LeftWheel(BEHIND,2);
			app_RightWheel(FRONT,2);
			finshFlag = CALIBRATION_WAITING;
		}else if(calibrationData < -CALIBRATION_DISTANCE){
			app_LeftWheel(FRONT,2);
			app_RightWheel(BEHIND,2);
			finshFlag = CALIBRATION_WAITING;
		}
		else if(calibrationData != 0){
			TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]);
			TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]);
			finshFlag = CALIBRATION_FINISHED;
		}
	}else if(direction == RIGHT){
		calibrationData = SRF_04_Data5.getDistance - SRF_04_Data6.getDistance;
		if(calibrationData > CALIBRATION_DISTANCE) 
			{
				app_LeftWheel(FRONT,2);
				app_RightWheel(BEHIND,2);
				finshFlag = CALIBRATION_WAITING;
			}else if(calibrationData < -CALIBRATION_DISTANCE){
				app_LeftWheel(BEHIND,2);
				app_RightWheel(FRONT,2);
				finshFlag = CALIBRATION_WAITING;
			}
			else if(calibrationData != 0){
				TIM_SetCompare1(TIM3,parameter[NAME_SET_ZERO__LEFT_RATE]);
				TIM_SetCompare2(TIM3,parameter[NAME_SET_ZERO__RIGHT_RATE]);
				finshFlag = CALIBRATION_FINISHED;
			}
	}else if(direction == NO_TURN){
		calibrationData = SRF_04_Data1.getDistance - SRF_04_Data2.getDistance;
		if(calibrationData >CALIBRATION_DISTANCE) 
			{
				app_LeftWheel(FRONT,4);
				app_RightWheel(FRONT,7);
				finshFlag = CALIBRATION_WAITING;
			}else if(calibrationData < -CALIBRATION_DISTANCE){
				app_LeftWheel(FRONT,4);
				app_RightWheel(FRONT,7);
				finshFlag = CALIBRATION_WAITING;
			}
			else{
				app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
				app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
				finshFlag = CALIBRATION_FINISHED;
			}
	}
	return finshFlag;
}



void app_frontTurn(turnDirection_e direction,uint16_t angle){
//	moveWays_e finishFlag;
	switch(direction){
		case LEFT :{
			switch(angle){ 
				case 90:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_LEFT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_LEFT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_LEFT_TIME_90]);break;}
				case 180:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_LEFT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_LEFT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_LEFT_TIME_180]);break;}
				case 135:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_LEFT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_LEFT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_LEFT_TIME_135]);break;}
				case 45:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_LEFT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_LEFT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_LEFT_TIME_45]);break;}
				}
			break;
			}		
		case RIGHT :{
			switch(angle){
				case 90:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_RIGHT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_RIGHT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_RIGHT_TIME_90]);break;}
				case 180:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_RIGHT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_RIGHT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_RIGHT_TIME_180]);break;}
				case 135:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_RIGHT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_RIGHT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_RIGHT_TIME_135]);break;}
				case 45:{app_turnAngleDirection(FOREWARD,parameter[NAME_TURN_RIGHT__LEFT_RATE],
																				FOREWARD,parameter[NAME_TURN_RIGHT__RIGHT_RATE],
																				parameter[NAME_FRONT_TURN_RIGHT_TIME_45]);break;}
				}
				break;
			}
	}
}

void app_behindTurn(turnDirection_e direction,uint16_t angle){
	switch(direction){
		case LEFT :{
			switch(angle){
				case 45:{app_turnAngleDirection(BEHIND,parameter[NAME_TURN_LEFT__LEFT_RATE],
																				BEHIND,parameter[NAME_TURN_LEFT__RIGHT_RATE],
																				parameter[NAME_BEHIND_TURN_LEFT_TIME_45]);	break;}
				}
				break;
			}		
		case RIGHT :{
			switch(angle){
				case 45:{app_turnAngleDirection(BEHIND,parameter[NAME_TURN_RIGHT__LEFT_RATE],
																				BEHIND,parameter[NAME_TURN_RIGHT__RIGHT_RATE],
																				parameter[NAME_BEHIND_TURN_RIGHT_TIME_45]);	break;}
				}
				break;
			}
	}
}

void app_reverseTurn(turnDirection_e direction,uint16_t angle){

	switch(direction){
		case LEFT :{
			switch(angle){
				case 45:{app_turnAngleDirection(REVERSE,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],
																				FOREWARD,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_45]);break;}
				case 90:{app_turnAngleDirection(REVERSE,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],
																				FOREWARD,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_90]);break;}
				case 135:{app_turnAngleDirection(REVERSE,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],
																				FOREWARD,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_135]);break;}
				case 180:{app_turnAngleDirection(REVERSE,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],
																				FOREWARD,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_180]);break;}
				}
			break;
			}
		case RIGHT :{
			switch(angle){
				case 45:{app_turnAngleDirection(FOREWARD,parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],
																				REVERSE,parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_45]);break;}
				case 90:{app_turnAngleDirection(FOREWARD,parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],
																				REVERSE,parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_90]);break;}
				case 135:{app_turnAngleDirection(FOREWARD,parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],
																				REVERSE,parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_135]);break;}
				case 180:{app_turnAngleDirection(FOREWARD,parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],
																				REVERSE,parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],
																				parameter[NAME_REVERSE_TURN_TIME_180]);break;}
				}
			break;
			}
		}
}

void app_walkWaysChoose()
{
	if(robotSelect.robotSelect == OUT_FIRE1 || robotSelect.robotSelect == OUT_FIRE2){
		switch(outfireRobotState.moveWays){
			case STOP:{app_walkStop();break;}
			case FRONT_TURN_LEFT_90:{app_frontTurn(LEFT,90);break;}
			case FRONT_TURN_LEFT_180:{app_frontTurn(LEFT,180);break;}
			case FRONT_TURN_RIGHT_90:{app_frontTurn(RIGHT,90);break;}
			case FRONT_TURN_RIGHT_180:{app_frontTurn(RIGHT,180);break;}
			case FRONT_TURN_LEFT_135:{app_frontTurn(LEFT,135);break;}
			case FRONT_TURN_LEFT_45:{app_frontTurn(LEFT,45);break;}
			case FRONT_TURN_RIGHT_135:{app_frontTurn(RIGHT,135);break;}
			case FRONT_TURN_RIGHT_45:{app_frontTurn(RIGHT,45);break;}
			case BEHIND_TURN_LEFT_45:{app_behindTurn(LEFT,45);break;}
			case BEHIND_TURN_RIGHT_45:{app_behindTurn(RIGHT,45);break;}
			case REVERSE_LEFT_TURN_45:{app_reverseTurn(LEFT,45);break;}
			case REVERSE_LEFT_TURN_90:{app_reverseTurn(LEFT,90);break;}
			case REVERSE_LEFT_TURN_135:{app_reverseTurn(LEFT,135);break;}
			case REVERSE_LEFT_TURN_180:{app_reverseTurn(LEFT,180);break;}
			case REVERSE_RIGHT_TURN_45:{app_reverseTurn(RIGHT,45);break;}
			case REVERSE_RIGHT_TURN_90:{app_reverseTurn(RIGHT,90);break;}
			case REVERSE_RIGHT_TURN_135:{app_reverseTurn(RIGHT,135);break;}
			case REVERSE_RIGHT_TURN_180:{app_reverseTurn(RIGHT,180);break;}
			case GO_STRAIGHT:{app_goStraight();break;}
			case SET_ZERO:{app_setZero();break;}
			default:break;
		}
	}
	else if(robotSelect.robotSelect == RESCUE){
		switch(rescueRobotState.moveWays){
			case STOP:{app_walkStop();break;}
			case FRONT_TURN_LEFT_90:{app_frontTurn(LEFT,90);break;}
			case FRONT_TURN_LEFT_180:{app_frontTurn(LEFT,180);break;}
			case FRONT_TURN_RIGHT_90:{app_frontTurn(RIGHT,90);break;}
			case FRONT_TURN_RIGHT_180:{app_frontTurn(RIGHT,180);break;}
			case FRONT_TURN_LEFT_135:{app_frontTurn(LEFT,135);break;}
			case FRONT_TURN_LEFT_45:{app_frontTurn(LEFT,45);break;}
			case FRONT_TURN_RIGHT_135:{app_frontTurn(RIGHT,135);break;}
			case FRONT_TURN_RIGHT_45:{app_frontTurn(RIGHT,45);break;}
			case BEHIND_TURN_LEFT_45:{app_behindTurn(LEFT,45);break;}
			case BEHIND_TURN_RIGHT_45:{app_behindTurn(RIGHT,45);break;}
			case REVERSE_LEFT_TURN_45:{app_reverseTurn(LEFT,45);break;}
			case REVERSE_LEFT_TURN_90:{app_reverseTurn(LEFT,90);break;}
			case REVERSE_LEFT_TURN_135:{app_reverseTurn(LEFT,135);break;}
			case REVERSE_LEFT_TURN_180:{app_reverseTurn(LEFT,180);break;}
			case REVERSE_RIGHT_TURN_45:{app_reverseTurn(RIGHT,45);break;}
			case REVERSE_RIGHT_TURN_90:{app_reverseTurn(RIGHT,90);break;}
			case REVERSE_RIGHT_TURN_135:{app_reverseTurn(RIGHT,135);break;}
			case REVERSE_RIGHT_TURN_180:{app_reverseTurn(RIGHT,180);break;}
			case GO_STRAIGHT:{app_goStraight();break;}
			case SET_ZERO:{app_setZero();break;}
			default:break;
		}
	}
	rescueRobotState.lastMoveWays = rescueRobotState.moveWays;
	outfireRobotState.lastMoveWays = outfireRobotState.moveWays;
	if(outfireRobotState.testTarget == TESTING && outfireRobotState.moveWays != GO_STRAIGHT) outfireRobotState.moveWays = STOP;
	if(rescueRobotState.testTarget == TESTING && rescueRobotState.moveWays != GO_STRAIGHT) rescueRobotState.moveWays = STOP;
}
void app_walkTask(void *Parameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, WALK_TASK_PERIOD);
		app_walkWaysChoose();
		vTaskDelay(1);
	}
}

void app_walkTaskInit(void)
{
 xTaskCreate(app_walkTask,"Walk",WALK_STACK_SIZE,NULL,WALK_PRIORITY,&appWalk.xHandleTask);
}

