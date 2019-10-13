#include "app.h"

#define	DISTANCE_TO_FIRE  25

//  超声波与墙的距离 可以做  Flash
void app_outfireOneWorkReady(void)
{ 
	/*待补充*/ //用按键控制小车启动//
	//finishFlag = SET_ZERO;
	/***********初始化火点位置*********/
	if(outfireRobotState.workMode == OUT_FIRE){
			app_judgeFunc();	
		if(outfireRobotState.returnFlag[RETURN] == 0){
			outfireRobotState.robotTaskstep = FIRST_FIRE;
			outfireRobotState.step = DOING;
			outfireRobotState.workStep = NULL;
			outfireRobotState.moveWays = STOP;
			outfireRobotState.beginFlag = FREE;
		}else if(outfireRobotState.returnFlag[RETURN] ==	1){
			outfireRobotState.robotTaskstep = RETURN;
			outfireRobotState.step = DOING;
			outfireRobotState.workStep = NULL;
			outfireRobotState.moveWays = STOP;
				outfireRobotState.beginFlag = FREE;
		}
	}
}
/***************一火点基本完备***************/
void app_findFirstFire(void){
	if(outfireRobotState.fireArray[FIRST_FIRE] == 1){   //有火
		switch(outfireRobotState.workStep){								
			case 0:{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 1;
				}
			break;
			}
			case 1:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance <50)
				{
					
 					outfireRobotState.workStep = 2;
				}
			break;
			}
			case 2:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 26 && SRF_04_Data2.getDistance <26){

					outfireRobotState.workStep = 3;
				}
			break;
			}
			case 3:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance < DISTANCE_TO_FIRE + 4 && calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 4; 
				}
			break;
			}
			case 4:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 5;
			break;
			} 
			case 5:{
				app_fan();						
				calibrationFinish = checkFire();			//开风扇
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 6;
				}
			break;
			}
			case 6:{
				app_goOtherAction(150,NO_TURN,BEHIND);
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
				outfireRobotState.workStep = 7;
			break;
			}
			case 7:{
				outfireRobotState.moveWays = STOP;
				vTaskDelay(400);
				outfireRobotState.workStep = 8;
			break;
			}
			case 8:{
				calibrationFinish = app_calibration(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99; 
				}
			break;
			}
			case 99:{
				if(outfireRobotState.returnFlag[FIRST_FIRE] == 1){
					outfireRobotState.robotTaskstep = RETURN;
				}else{
					outfireRobotState.robotTaskstep = NINTH_FIRE;
				}
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;
				break;
			}
		}
	}
	else {																						//一火点无火
		switch(outfireRobotState.workStep){
			case 0:{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 1;
				}
			break;
			}
			case 1:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance <50)
				{
					
					outfireRobotState.workStep = 2;
				}
			break;
			}
			case 2:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 17 && SRF_04_Data2.getDistance <17){
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
					outfireRobotState.workStep = 3;
				}
			break;
			}
			case 3:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 4;
			break;
			}
			case 4:{
				outfireRobotState.workStep = 5;
			break;
			}
			case 5:{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99; 
				}
			break;
			}
			case 99:
				outfireRobotState.workStep = 0;
			outfireRobotState.moveWays = OTHER;
				outfireRobotState.robotTaskstep = NINTH_FIRE;
			break;
		}
	}	
}

/***************九火点基本完善***************/
void app_findNinthFire(void){  																			 //从一号判断有无火焰之后纠正车体姿态，（不管有没有）都从一号火点位置作为本函数的起点
	if(outfireRobotState.fireArray[NINTH_FIRE] == 1){										//有火
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 1;
				break;
			}
			case 1:{
				outfireRobotState.workStep = 2;
			break;
			}
			case 2:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data3.getDistance < 25 && SRF_04_Data4.getDistance < 25){
					outfireRobotState.workStep = 3;
				}
			break;
			}
			case 3:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data3.getDistance > 50 && SRF_04_Data4.getDistance <30){
					outfireRobotState.workStep = 4;	
				}
			break;
			}
			case 4:{
				outfireRobotState.moveWays = FRONT_TURN_LEFT_135;
				outfireRobotState.workStep = 5;	
			break;
			}
			case 5:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 6;
			break;
			}
			case 6:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance  < DISTANCE_TO_FIRE && calibrationFinish == CALIBRATION_FINISHED){   /**与火焰的距离**/
					outfireRobotState.workStep = 7;
				}
			break;
			}
			case 7:{			
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 8;   
				break;
			}
			case 8:{
				app_fan();				//开风扇灭火
				calibrationFinish = checkFire();
				app_goOtherAction(400,NO_TURN,BEHIND);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.moveWays = REVERSE_RIGHT_TURN_135;
					outfireRobotState.workStep = 9;
				}
			break;
			}
			case 9:{//出屋子函数
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 10;
				break;
			}
			case 10:{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 11;
				}
			break;
			}
			case 11:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance > 25 && SRF_04_Data2.getDistance > 25 && SRF_04_Data1.getDistance < 35 && SRF_04_Data2.getDistance <35){
					outfireRobotState.workStep = 12;
				}
			break;
			}
			case 12:{
				outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
				outfireRobotState.workStep = 13;
			break;
			}
			case 13:{//出屋子函数
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 14;
				break;
			}
			case 14:{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 15;
				}
			break;
			}
			case 15:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 17 && SRF_04_Data2.getDistance < 17 ){
					outfireRobotState.workStep = 16;
				}
			break;
			}
			case 16:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep = 17;
			break;
			}
			case 17:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 18;
				break;
			}
			case 18:{
				outfireRobotState.workStep = 19;
			break;
			}
			case 19:{
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 99;
			break;
			}
			//回到第一阶段位置
			case 99:{
				if(outfireRobotState.returnFlag[NINTH_FIRE] == 1)
					outfireRobotState.robotTaskstep = RETURN;
				else{
					outfireRobotState.robotTaskstep = THIRD_FIRE;
				}			
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;
			break;
			}
		}
	}
	else {
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.workStep = 1;	
			break;
			}
			case 1:{
				outfireRobotState.workStep = 2;
			break;
			}
			case 2:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data3.getDistance > 40 && SRF_04_Data4.getDistance < 40){	
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 3;
				}
			break;
			}
			case 3:{
				outfireRobotState.workStep = 99;	
			break;
			}
			case 99:
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.robotTaskstep = THIRD_FIRE;
			break;
		}
	}
}
/***************三火点正在完善***************/
void app_findThirdFire(void){
	if(outfireRobotState.fireArray[THIRD_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(200);
				outfireRobotState.workStep = 'a';
			break;
			}
			case 'a':{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance < 32){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 1;
				}	
			break;
			}
			case 1:{
				outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
				outfireRobotState.workStep = 2;
			break;
			}
			case 2:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 3;
			break;
			}
			case 3:{
				calibrationFinish = app_calibration(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 4;
				}
			break;
			}
			case 4:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(1000);
				outfireRobotState.workStep = 5;
			break;
			}
			case 5:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data5.getDistance > 40 && SRF_04_Data6.getDistance < 40){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
					outfireRobotState.workStep = 6;
				}
			break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 7;
			break;
			}
			case 7:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(900);
				outfireRobotState.workStep = 8;
			break;
			}
			case 8:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance < 35 && SRF_04_Data2.getDistance < 35 ){
					outfireRobotState.workStep = 9;
				}
			break;
			}
			case 9:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance  < DISTANCE_TO_FIRE && calibrationFinish == CALIBRATION_FINISHED){   /**与火焰的距离**/
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 10;
				}
			break;
			}
			case 10:{
				app_fan();						
				calibrationFinish = checkFire();			//开风扇
				if(calibrationFinish == CALIBRATION_FINISHED){
					app_goOtherAction(600,LEFT,BEHIND);
					outfireRobotState.workStep = 11;
				}
				
			break;
			}
			case 11:{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 12;
				}
			break;
			}
			case 12:{
				app_goOtherAction(500,NO_TURN,BEHIND);
				outfireRobotState.workStep = 13;
			break;
			}
			case 13:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			}
			case 99:
				if(outfireRobotState.returnFlag[THIRD_FIRE] == 1)
					outfireRobotState.robotTaskstep = RETURN;
				else{
					outfireRobotState.robotTaskstep = SECOND_FIRE;
				}			
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;			
			break;
			}
		
	}
	else{																											//没火
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(200);
				outfireRobotState.workStep = 'a';
			break;
			}
			case 'a':{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance < 32){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 1;
				}	
			break;
			}
			case 1:{
				outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
				outfireRobotState.workStep = 2;
			break;
			}
			case 2:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 3;
			break;
			}
			case 3:{
				calibrationFinish = app_calibration(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 4;
				}
			break;
			}
			case 4:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(800);
				outfireRobotState.workStep = 5;
			break;
			}
			case 5:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data5.getDistance > 40 && SRF_04_Data6.getDistance < 40){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
					outfireRobotState.workStep = 6;
				}
			break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 7;
			break;
			}
			case 7:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(900);
				outfireRobotState.workStep = 8;
			break;
			}
			case 8:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance < 18 && SRF_04_Data2.getDistance < 18 ){
					outfireRobotState.workStep = 9;
				}
			break;
			}	
			case 9:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 10;
			break;
			}
			case 10:{
//				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep = 11;
			break;
			}
			case 11:{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99;
					outfireRobotState.moveWays = STOP;
				}
			break;
			}
			case 99:
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.robotTaskstep = SECOND_FIRE;
			break;
			}	
	}
}
/***************二火点正在完善***************/
void app_findSecondFire(void){  
	if(outfireRobotState.fireArray[SECOND_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 20 && SRF_04_Data2.getDistance < 20){
					outfireRobotState.workStep = 'z';
					outfireRobotState.moveWays = STOP;
				}
				break;
			}
			case 'z':{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep = 'v';
				break;
			}
			case 'v':{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = STOP;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 'M';
				}
				break;
			}
			case 'M':{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance < 50){
					outfireRobotState.moveWays = REVERSE_RIGHT_TURN_45;
					outfireRobotState.workStep = 'b';	
				}
			break;
			}
			case 'b':{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 1;
			break;
			}
			case 1:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance  < DISTANCE_TO_FIRE && calibrationFinish == CALIBRATION_FINISHED){   /**与火焰的距离**/
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 2;
				}
			break;
			}
			case 2:{
				app_fan();						
				calibrationFinish = checkFire();			//开风扇
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 'a';
				}
				
				break;
			}
			case 'a':{
				app_goOtherAction(800,NO_TURN,BEHIND);
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
				outfireRobotState.workStep = 3;
				break;
			}
			case 3:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			break;
			}
			case 99:
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.robotTaskstep = RETURN;
			break;
			}
	}
}

//节点返程函数
void app_returnFunc(void){
	if(outfireRobotState.returnFlag[FIRST_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep = 1;
				break;
			}
			case 1:{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 2;
				}
				break;
			}
			case 2:{
				app_goOtherAction(800,NO_TURN,FRONT);
				outfireRobotState.workStep = 3;
				break;
			}
			case 3:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance < 50)
				{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 99;
				}
				break;
			}
			/********最好加入原地校准******/
			
			case 99:{
				outfireRobotState.workStep = 0;
				outfireRobotState.step = FINISH;
				break;
			}
		}
	}else if(outfireRobotState.returnFlag[SECOND_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance < 32 &&SRF_04_Data2.getDistance <32){
					outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
					outfireRobotState.workStep = 'e';
				}
				break;
			}
			/********最好加入原地校准******/
			case 'e':{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 1;
				break;
			}
			case 1:{
				calibrationGostraight(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance <32){
					outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
					outfireRobotState.workStep = 'b';
				}
				break;
			}
			case 'b':{
				outfireRobotState.moveWays = STOP;
				vTaskDelay(200);
				outfireRobotState.workStep = 'a';
				break;
			}
			case 'a':{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 3;
				}
				break;
			}
			case 3:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 35 && SRF_04_Data2.getDistance<35){
					outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
					outfireRobotState.workStep = 'f';
				}
				break;
			}
			case 'f':{
				calibrationFinish = app_calibration(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 4;
				}
				break;
			}
			case 4:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(800);
				outfireRobotState.workStep = 5;
				break;
			}
			case 5:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance < 32){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;		
					outfireRobotState.workStep = 6;
				}
				break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 'd';
				break;
			}
			case 'd':{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(800);
				outfireRobotState.workStep = 7;
			break;
			}
			case 7:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 45 && SRF_04_Data2.getDistance < 45)
				{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 8;
				}
				break;
			}
			case 8:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 35 && SRF_04_Data2.getDistance < 35){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
					vTaskDelay(200);
					outfireRobotState.workStep = 'g';
				}
				break;
			}
			case 'g':{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 9;
					vTaskDelay(400);
				}
			break;
			}
			case 9:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance < 50)
				{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 99;
				}
				break;
			}
			case 99:{
				outfireRobotState.workStep = 0;
				outfireRobotState.step = FINISH;
				break;
			}
		}
	}else if(outfireRobotState.returnFlag[THIRD_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_180;
				outfireRobotState.workStep = 1;
				break;
			}
			case 1:{
				outfireRobotState.moveWays = STOP;
				vTaskDelay(200);
				outfireRobotState.workStep = 'a';
				break;
			}
			case 'a':{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 3;
				}
				break;
			}
			case 3:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 35 && SRF_04_Data2.getDistance<35){
					outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
					outfireRobotState.workStep = 'f';
				}
				break;
			}
			case 'f':{
				calibrationFinish = app_calibration(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 4;
				}
				break;
			}
			case 4:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(400);
				outfireRobotState.workStep = 5;
				break;
			}
			case 5:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance < 32){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;		
					outfireRobotState.workStep = 6;
				}
				break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 'd';
				break;
			}
			case 'd':{
				outfireRobotState.moveWays = GO_STRAIGHT;
				vTaskDelay(400);
				outfireRobotState.workStep = 7;
			break;
			}
			case 7:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 45 && SRF_04_Data2.getDistance < 45)
				{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 8;
				}
				break;
			}
			case 8:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance < 32){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
					vTaskDelay(200);
					outfireRobotState.workStep = 'g';
				}
				break;
			}
			case 'g':{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 9;
					vTaskDelay(400);
				}
			break;
			}
			case 9:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance < 50)
				{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 99;
				}
				break;
			}
			/********最好加入原地校准******/
			
			case 99:{
				outfireRobotState.workStep = 0;
				outfireRobotState.step = FINISH;
				break;
			}
		}
	}else if(outfireRobotState.returnFlag[NINTH_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_180;
				vTaskDelay(200);
				outfireRobotState.workStep = 2;
				break;
			}
//			case 1:{
//				calibrationFinish = app_calibration(LEFT);
//				outfireRobotState.moveWays = OTHER;
//				if(calibrationFinish == CALIBRATION_FINISHED){
//					outfireRobotState.workStep = 2;
//				}
//				break;
//			}
			case 2:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 32 && SRF_04_Data2.getDistance < 32)
				{
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;;
					outfireRobotState.workStep = 'g';
				}
				break;
			}
//			case 3:{
//				outfireRobotState.moveWays = GO_STRAIGHT;
//				if(SRF_04_Data1.getDistance < 22 && SRF_04_Data2.getDistance < 32){
//					outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
//					vTaskDelay(200);
//					outfireRobotState.workStep = 'g';
//				}
//				break;
//			}
			case 'g':{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 4;
					vTaskDelay(400);
				}
			break;
			}
			case 4:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance < 50)
				{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 99;
				}
				break;
			}
			/********最好加入原地校准******/
			
			case 99:{
				outfireRobotState.workStep = 0;
				outfireRobotState.step = FINISH;
				break;
			}
		}
	}else if(outfireRobotState.returnFlag[RETURN] == 1){
		outfireRobotState.workStep = 0;
		outfireRobotState.step = FINISH;
	}		//路线1
}

/***寻火任务**/
void app_outfireOneWorkDoing(void){
	//加一个返回节点判断函数，一次判断终身享用
	if(outfireRobotState.beginFlag == FREE && outfireRobotState.workMode != TEST){
		switch(outfireRobotState.robotTaskstep){
			case FIRST_FIRE:app_findFirstFire(); break;
			case NINTH_FIRE:app_findNinthFire(); break;
			case THIRD_FIRE:app_findThirdFire(); break;
			case SECOND_FIRE:app_findSecondFire(); break;
			case RETURN:app_returnFunc();break;
		}
	}
}

