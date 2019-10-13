#include "app.h"
/*********************************************************
             8->7->5->4->6
**********************************************************/
void app_outfireTwoWorkReady(void)
{
	/*待补充*/ //用按键控制小车启动//
	//finishFlag = SET_ZERO;
	if(outfireRobotState.workMode == OUT_FIRE){
			app_judgeFunc();	
		if(outfireRobotState.returnFlag[RETURN] == 0){
			outfireRobotState.robotTaskstep = EIGHTH_FIRE;
			outfireRobotState.step = DOING;
			outfireRobotState.workStep = NULL;
			outfireRobotState.moveWays = STOP;
			outfireRobotState.beginFlag = FREE;
		}else if(outfireRobotState.returnFlag[RETURN] == 1){
			outfireRobotState.robotTaskstep = RETURN;
			outfireRobotState.step = DOING;
			outfireRobotState.workStep = NULL;
			outfireRobotState.moveWays = STOP;
				outfireRobotState.beginFlag = FREE;
		}
	}
}

void app_findEighthFire(void){
	if(outfireRobotState.fireArray[EIGHTH_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 1:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <= 17 && SRF_04_Data2.getDistance <= 17){
					outfireRobotState.workStep++;
				}break;
			}
			case 2:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 3:{
				outfireRobotState.moveWays = STOP;
				vTaskDelay(200);
				outfireRobotState.workStep++;
				break;
			}
			case 4:{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.moveWays = OTHER;
					outfireRobotState.workStep++;
				}break;
			}
			case 5:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance <=53 && SRF_04_Data2.getDistance <=53){
					outfireRobotState.workStep++;
				}break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 7:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 8:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 9:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data4.getDistance <50){
					outfireRobotState.workStep++;
				}break;
			}
			case 10:{
				app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
				app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
				vTaskDelay(1200);
				app_LeftWheel(FRONT,parameter[NAME_SET_ZERO__LEFT_RATE]);
				app_RightWheel(FRONT,parameter[NAME_SET_ZERO__RIGHT_RATE]);
				outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
				outfireRobotState.workStep++;
				break;
			}
			case 11:{
				outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
				outfireRobotState.workStep++;
				break;
			}
			case 12:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 13:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 14:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_45;
				outfireRobotState.workStep++;
				break;
			}
			case 15:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <20 && SRF_04_Data2.getDistance <20){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 16:{
				app_fan();
				calibrationFinish = checkFire();
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 17:{
				app_goBack(600,NO_TURN);
				outfireRobotState.workStep++;
				break;
			}
			case 18:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_135;
				outfireRobotState.workStep++;
				break;
			}
			case 19:{
				outfireRobotState.moveWays = STOP;
				vTaskDelay(200);
				outfireRobotState.workStep++;
				break;
			}
			case 20:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 21:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 22:{
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep++;
				break;
			}
			case 23:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
				break;
			}
			case 99:{
				if(outfireRobotState.returnFlag[EIGHTH_FIRE] == 1){
					outfireRobotState.robotTaskstep = RETURN;
				}else{
					outfireRobotState.robotTaskstep = SENVENTH_FIRE;
				}
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 0;
				break;
			}
		}
	}
	else{
		if(outfireRobotState.fireArray[SENVENTH_FIRE] == 1){//测试完成
			switch(outfireRobotState.workStep){
				case 0:{
					calibrationFinish = app_calibration(LEFT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 1:{
					calibrationGostraight(LEFT);
					if(SRF_04_Data1.getDistance <= 17 && SRF_04_Data2.getDistance <= 17){
						outfireRobotState.workStep++;
					}break;
				}
				case 2:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 3:{
					outfireRobotState.moveWays = STOP;
					vTaskDelay(200);
					outfireRobotState.workStep++;
					break;
				}
				case 4:{
					calibrationFinish = app_calibration(RIGHT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.moveWays = OTHER;
						outfireRobotState.workStep++;
					}break;
				}
				case 5:{
					calibrationGostraight(RIGHT);
					if(SRF_04_Data1.getDistance <=53 && SRF_04_Data2.getDistance <=53){
						outfireRobotState.workStep++;
					}break;
				}
				case 6:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 7:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 8:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 9:{
					calibrationGostraight(LEFT);
					if(SRF_04_Data4.getDistance <50){
						outfireRobotState.workStep++;
					}break;
				}
				case 10:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 11:{
					calibrationFinish = app_calibration(LEFT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 12:{
					outfireRobotState.moveWays = GO_STRAIGHT;
					calibrationGostraight(LEFT);
					if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}break;
				}
				case 13:{
					outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 14:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 99:{
					outfireRobotState.moveWays = OTHER;
					outfireRobotState.robotTaskstep = SENVENTH_FIRE;
					outfireRobotState.workStep = 0;
					break;
				}
			}
		}
		else{
			//分岔口
			switch(outfireRobotState.workStep){
				case 0:{
					calibrationFinish = app_calibration(LEFT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 1:{
					calibrationGostraight(LEFT);
					if(SRF_04_Data1.getDistance <= 17 && SRF_04_Data2.getDistance <= 17){
						outfireRobotState.workStep++;
					}break;
				}
				case 2:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 3:{
					outfireRobotState.moveWays = STOP;
					vTaskDelay(200);
					outfireRobotState.workStep++;
					break;
				}
				case 4:{
					calibrationFinish = app_calibration(RIGHT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.moveWays = OTHER;
						outfireRobotState.workStep++;
					}break;
				}
				case 5:{
					calibrationGostraight(RIGHT);
					if(SRF_04_Data1.getDistance <=53 && SRF_04_Data2.getDistance <=53){
						outfireRobotState.workStep++;
					}break;
				}
				case 6:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 7:{
					outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 8:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 99;
					break;
				}
				case 99:{
					outfireRobotState.moveWays = OTHER;
					outfireRobotState.robotTaskstep = FOURTH_FIRE;
					outfireRobotState.workStep = 0;
					break;
				}
			}
		}
	}
}


void app_findSixFire(void){
	if(outfireRobotState.fireArray[SIXTH_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance <23 && SRF_04_Data2.getDistance <23){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 1:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <28 && SRF_04_Data2.getDistance <28 ){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 2:{
				outfireRobotState.moveWays = OTHER;
				app_fan();
				calibrationFinish = checkFire();
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 3:{
				app_goBack(100,NO_TURN);
				outfireRobotState.workStep++;
				break;
			}
			case 4:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
				outfireRobotState.workStep++;
				break;
			}
			case 5:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 6:{
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99;
				}break;
			}
			case 99:{
				if(outfireRobotState.returnFlag[SIXTH_FIRE] == 1){
					outfireRobotState.robotTaskstep = RETURN;
				}
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 0;
				break;
			}
		}
	}	
}

void app_findFourthFire(void){
	if(outfireRobotState.fireArray[FOURTH_FIRE] == 1 && outfireRobotState.fireArray[FIFTH_FIRE] == 1 ){
		switch(outfireRobotState.workStep){
			case 0:{
				if(SRF_04_Data1.getDistance >11&& SRF_04_Data2.getDistance >11){
					outfireRobotState.moveWays = GO_STRAIGHT;
				}else if(SRF_04_Data1.getDistance <11&& SRF_04_Data2.getDistance <11){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}	
			case 1:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 2:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 3:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 4:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <18 && SRF_04_Data2.getDistance <18){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}
				break;
			}
			case 5:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 7:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 8:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <45 && SRF_04_Data2.getDistance <45){
					outfireRobotState.workStep++;
				}
				break;
			}
			case 9:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 10:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 11:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 12:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 13:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 14:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_45;
				outfireRobotState.workStep++;
				break;
			}
			case 15:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 16:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <26&& SRF_04_Data2.getDistance <26){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 17:{
				outfireRobotState.moveWays = OTHER;
				app_fan();
				calibrationFinish = checkFire();
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 18:{
				app_goBack(600,NO_TURN);
				outfireRobotState.workStep++;
				break;
			}
			case 19:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_135;
				outfireRobotState.workStep++;
				break;
			}
			case 20:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 21:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 22:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <35 && SRF_04_Data2.getDistance <35){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}
				break;
			}
			case 23:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_45;
				outfireRobotState.workStep++;
				break;
			}
			case 24:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 25:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <24 && SRF_04_Data2.getDistance <24){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 26:{
				outfireRobotState.moveWays = OTHER;
				app_fan();
				calibrationFinish = checkFire();
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 27:{
				app_goBack(500,NO_TURN);
				outfireRobotState.workStep++;
				break;
			}
			case 28:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
				outfireRobotState.workStep++;
				break;
			}
			case 29:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 30:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99;
				}break;
			}
			case 99:{
				if(outfireRobotState.returnFlag[FOURTH_FIRE] == 1 || outfireRobotState.returnFlag[FIFTH_FIRE] == 1){
					outfireRobotState.robotTaskstep = RETURN;
				}
				else{
					outfireRobotState.robotTaskstep = SIXTH_FIRE;
					
				}
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 0;
				break;
			}
		}
	}
	else if(outfireRobotState.fireArray[FOURTH_FIRE] == 1 && outfireRobotState.fireArray[FIFTH_FIRE] == 0){
		switch(outfireRobotState.workStep){
			case 0:{
				if(SRF_04_Data1.getDistance >11&& SRF_04_Data2.getDistance >11){
					outfireRobotState.moveWays = GO_STRAIGHT;
				}else if(SRF_04_Data1.getDistance <11&& SRF_04_Data2.getDistance <11){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}	
			case 1:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 2:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 3:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 4:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <18 && SRF_04_Data2.getDistance <18){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}
				break;
			}
			case 5:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 7:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 8:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <45 && SRF_04_Data2.getDistance <45){
					outfireRobotState.workStep++;
				}
				break;
			}
			case 9:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 10:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 11:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 12:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 13:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 14:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_45;
				outfireRobotState.workStep++;
				break;
			}
			case 15:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 16:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <26&& SRF_04_Data2.getDistance <26){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 17:{
				outfireRobotState.moveWays = OTHER;
				app_fan();
				calibrationFinish = checkFire();
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 18:{
				app_goBack(600,NO_TURN);
				outfireRobotState.workStep++;
				break;
			}
			case 19:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_135;
				outfireRobotState.workStep++;
				break;
			}
			case 20:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 21:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 22:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <20 && SRF_04_Data2.getDistance <20){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}
				break;
			}
			case 23:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 24:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 25:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99;
				}break;
			}
			case 99:{
				if(outfireRobotState.returnFlag[FOURTH_FIRE] == 1){
					outfireRobotState.robotTaskstep = RETURN;
				}
				else{
					outfireRobotState.robotTaskstep = SIXTH_FIRE;
					
				}
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 0;
				break;
			}
		}
	}		
	else if(outfireRobotState.fireArray[FOURTH_FIRE] == 0){
		if(outfireRobotState.fireArray[FIFTH_FIRE] == 1){
			switch(outfireRobotState.workStep){
				case 0:{
					if(SRF_04_Data1.getDistance >11&& SRF_04_Data2.getDistance >11){
						outfireRobotState.moveWays = GO_STRAIGHT;
					}else if(SRF_04_Data1.getDistance <11&& SRF_04_Data2.getDistance <11){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}break;
				}	
				case 1:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 2:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 3:{
					outfireRobotState.moveWays = OTHER;
					calibrationFinish = app_calibration(RIGHT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 4:{
					outfireRobotState.moveWays = GO_STRAIGHT;
					calibrationGostraight(LEFT);
					if(SRF_04_Data1.getDistance <18 && SRF_04_Data2.getDistance <18){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}
					break;
				}
				case 5:{
					outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 6:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 7:{
					outfireRobotState.moveWays = OTHER;
					calibrationFinish = app_calibration(LEFT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 8:{
					outfireRobotState.moveWays = GO_STRAIGHT;
					calibrationGostraight(LEFT);
					if(SRF_04_Data1.getDistance <35 && SRF_04_Data2.getDistance <35){
						outfireRobotState.workStep++;
					}
					break;
				}
				case 9:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 10:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_45;
					outfireRobotState.workStep++;
					break;
				}
				case 11:{
					calibrationFinish = app_findFire();
					outfireRobotState.moveWays = OTHER;
					if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <30&& SRF_04_Data2.getDistance <30){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}break;
				}
				case 12:{
					outfireRobotState.moveWays = OTHER;
					app_fan();
					calibrationFinish = checkFire();
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 13:{
					app_goBack(150,NO_TURN);
					outfireRobotState.workStep++;
					break;
				}
				case 14:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
					outfireRobotState.workStep++;
					break;
				}
				case 15:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 16:{
					outfireRobotState.moveWays = OTHER;
					calibrationFinish = app_calibration(RIGHT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep = 99;
					}break;
				}
				case 99:{
					if(outfireRobotState.returnFlag[FIFTH_FIRE] == 1){
						outfireRobotState.robotTaskstep = RETURN;
					}
					else{
						outfireRobotState.robotTaskstep = SIXTH_FIRE;
						
					}
					outfireRobotState.moveWays = OTHER;
					outfireRobotState.workStep = 0;
					break;
				}
			}
		}
		else{	
			switch(outfireRobotState.workStep){
				case 0:{
					if(SRF_04_Data1.getDistance >11&& SRF_04_Data2.getDistance >11){
						outfireRobotState.moveWays = GO_STRAIGHT;
					}else if(SRF_04_Data1.getDistance <11&& SRF_04_Data2.getDistance <11){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}break;
				}	
				case 1:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
					outfireRobotState.workStep++;
					break;
				}
				case 2:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 3:{
					outfireRobotState.moveWays = OTHER;
					calibrationFinish = app_calibration(RIGHT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 4:{
					outfireRobotState.moveWays = GO_STRAIGHT;
					calibrationGostraight(LEFT);
					if(SRF_04_Data1.getDistance <20 && SRF_04_Data2.getDistance <20){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}
					break;
				}
				case 5:{
					calibrationFinish = app_findFire();
					outfireRobotState.moveWays = OTHER;
					if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <28 && SRF_04_Data2.getDistance <28){
						outfireRobotState.moveWays = STOP;
						outfireRobotState.workStep++;
					}break;
				}
				case 6:{
					app_fan();
					outfireRobotState.moveWays = OTHER;
					calibrationFinish = checkFire();
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep++;
					}break;
				}
				case 7:{
					app_goBack(180,NO_TURN);
					outfireRobotState.workStep++;
					break;
				}
				case 8:{
					outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
					outfireRobotState.workStep++;
					break;
				}
				case 9:{
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
					break;
				}
				case 10:{
					outfireRobotState.moveWays = OTHER;
					calibrationFinish = app_calibration(RIGHT);
					if(calibrationFinish == CALIBRATION_FINISHED){
						outfireRobotState.workStep = 99;
					}break;
				}
				case 99:{
					if(outfireRobotState.returnFlag[SIXTH_FIRE] == 1){
						outfireRobotState.robotTaskstep = RETURN;
					}
					outfireRobotState.moveWays = OTHER;
					outfireRobotState.workStep = 0;
					break;
				}
			}
		}
	}				
}
		
				
void app_findSeventhFire(void){
	if(outfireRobotState.fireArray[SENVENTH_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <26 && SRF_04_Data2.getDistance <26){
					outfireRobotState.workStep++;
				}
				break;
			}
			case 1:{
				outfireRobotState.moveWays =REVERSE_LEFT_TURN_45;
				 outfireRobotState.workStep++;
				break;
			}
			case 2:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED && SRF_04_Data1.getDistance <27 && SRF_04_Data2.getDistance <27){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 3:{
				app_fan();
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = checkFire();
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 4:{
				app_goBack(800,NO_TURN);
				outfireRobotState.workStep++;
				break;
			}
			case 5:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
				outfireRobotState.workStep++;
				break;
			}
			case 6:{
				outfireRobotState.moveWays = STOP;
				vTaskDelay(200);
				outfireRobotState.workStep++;
				break;
			}
			case 7:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance <15 && SRF_04_Data2.getDistance <15 ){
					outfireRobotState.workStep++;
				}
				break;
			}
			case 8:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 9:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 10:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 11:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(RIGHT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 12:{
				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance <10 && SRF_04_Data2.getDistance <10){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 13:{
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 99;
				break;
			}
			case 99:{
				if(outfireRobotState.returnFlag[SENVENTH_FIRE] == 1){
					outfireRobotState.robotTaskstep = RETURN;
				}else{
					outfireRobotState.robotTaskstep = FOURTH_FIRE;
				}
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 0;
				vTaskDelay(200);
				break;
			}
		}
	}else{
		switch(outfireRobotState.workStep){
			case 0:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance <26 && SRF_04_Data2.getDistance <26){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep++;
				}break;
			}
			case 1:{
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep++;
				break;
			}
			case 2:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 3:{
				outfireRobotState.moveWays = OTHER;
				calibrationFinish = app_calibration(LEFT);
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep++;
				}break;
			}
			case 4:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 5:{
				outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
				outfireRobotState.workStep++;
				break;
			}
			case 6:{
				outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
				outfireRobotState.workStep++;
				break;
			}
			case 7:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
				break;
			}
			case 8:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data1.getDistance <= 11 && SRF_04_Data2.getDistance <= 11){
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 99;
				}
				break;
			}
			case 99:{
				outfireRobotState.robotTaskstep = FOURTH_FIRE;
				outfireRobotState.moveWays = OTHER;
				outfireRobotState.workStep = 0;
				break;
			}
		}
	}
}
		
				
void app_returnFromEighthFire(void){
	switch(outfireRobotState.workStep){
		case 0:{
			calibrationGostraight(LEFT);
			if(SRF_04_Data1.getDistance <26 && SRF_04_Data2.getDistance <26){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
			}break;
		}
		case 1:{
			outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			outfireRobotState.workStep++;
			break;
		}
		case 2:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 3:{
			outfireRobotState.moveWays = OTHER;
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 4:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 5:{
			outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
			outfireRobotState.workStep++;
			break;
		}
		case 6:{
			outfireRobotState.moveWays = FRONT_TURN_LEFT_90;
			outfireRobotState.workStep++;
			break;
		}
		case 7:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 8:{
			calibrationGostraight(RIGHT);
			if(SRF_04_Data5.getDistance > 50){
				outfireRobotState.workStep++;
			}break;
		}
		case 9:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 10:{
			outfireRobotState.moveWays = FRONT_TURN_RIGHT_180;
			outfireRobotState.workStep++;
			break;
		}
		case 11:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 12:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			vTaskDelay(500);
			outfireRobotState.workStep++;
			break;
		}
		case 13:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 14:{
			outfireRobotState.moveWays = OTHER;
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 15:{
			calibrationGostraight(LEFT);
			if(SRF_04_Data1.getDistance <32 && SRF_04_Data2.getDistance <32){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			}break;
		}
		case 99:{
			outfireRobotState.moveWays = OTHER;
			outfireRobotState.step = FINISH;
			outfireRobotState.workStep = 0;
			break;
		}
	}
			
}

void app_returnFromSixthFire(void){
	switch(outfireRobotState.workStep){
		case 0:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data6.getDistance> 40){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
			}break;
		}
		case 1:{
			outfireRobotState.moveWays = OTHER;
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 2:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(LEFT);
			vTaskDelay(1500);
			outfireRobotState.workStep++;
			break;
		}
		case 3:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 4:{
			outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
			outfireRobotState.workStep++;
			break;
		}
		case 5:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 6:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			vTaskDelay(450);
			outfireRobotState.workStep++;
			break;
		}
		case 7:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 8:{
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 9:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <40 && SRF_04_Data2.getDistance <40){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			}
			break;
		}
		case 99:{
			outfireRobotState.moveWays = OTHER;
			outfireRobotState.step = FINISH;
			outfireRobotState.workStep = 0;
			break;
		}
	}
}
void app_returnFromFourthFire(void){
	switch(outfireRobotState.workStep){
		case 0:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <18 && SRF_04_Data2.getDistance <18){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
			}break;
		}
		case 1:{
			outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;
			outfireRobotState.workStep++;
			break;
		}
		case 2:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 3:{
			outfireRobotState.moveWays = OTHER;
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 4:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data6.getDistance> 40){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep++;
			}break;
		}
		case 5:{
			outfireRobotState.moveWays = OTHER;
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 6:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(LEFT);
			vTaskDelay(1200);
			outfireRobotState.workStep++;
			break;
		}
		case 7:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 8:{
			outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
			outfireRobotState.workStep++;
			break;
		}
		case 9:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 10:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			vTaskDelay(800);
			outfireRobotState.workStep++;
			break;
		}
		case 11:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 12:{
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 13:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <40 && SRF_04_Data2.getDistance <40){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			}
			break;
		}
		case 99:{
			outfireRobotState.moveWays = OTHER;
			outfireRobotState.step = FINISH;
			outfireRobotState.workStep = 0;
			break;
		}
	}
			
}

void app_returnFromSenventhFire(void){//测试完成
	switch(outfireRobotState.workStep){
		case 0:{
			outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			outfireRobotState.workStep++;
			break;
		}
		case 1:{
			outfireRobotState.moveWays = STOP;
			vTaskDelay(200);
			outfireRobotState.workStep++;
			break;
		}
		case 2:{
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 3:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			vTaskDelay(800);
			outfireRobotState.workStep++;
			break;
		}
		case 4:{
			outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
			outfireRobotState.workStep++;
			break;
		}
		case 5:{
			outfireRobotState.moveWays = STOP;
			outfireRobotState.workStep++;
			break;
		}
		case 6:{
			outfireRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(LEFT);
			vTaskDelay(600);
			outfireRobotState.workStep++;
			break;
		}
		case 7:{
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				outfireRobotState.workStep++;
			}break;
		}
		case 8:{
			outfireRobotState.moveWays = OTHER;
			calibrationGostraight(LEFT);
			if(SRF_04_Data1.getDistance <35 && SRF_04_Data2.getDistance <35){
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			}break;
		}
		case 99:{
			outfireRobotState.moveWays = OTHER;
			outfireRobotState.step = FINISH;
			outfireRobotState.workStep = 0;
			break;
		}
	}		
}


void returnHome(outfireRobotState_t *lastfire){
	if(lastfire->returnFlag[SIXTH_FIRE] == 1){
		app_returnFromSixthFire();
	}else if(lastfire->returnFlag[FOURTH_FIRE] == 1){
		app_returnFromFourthFire();
	}else if(lastfire->returnFlag[EIGHTH_FIRE] == 1){
		app_returnFromEighthFire();
	}else if(lastfire->returnFlag[FIFTH_FIRE] == 1){
		app_returnFromFourthFire();
	}else if(lastfire->returnFlag[SENVENTH_FIRE] == 1){
		app_returnFromSenventhFire();
	}
}

/***寻火任务**/
void app_outfireTwoWorkDoing(void){
	if(outfireRobotState.beginFlag == FREE && outfireRobotState.workMode != TEST){
		switch(outfireRobotState.robotTaskstep){
			case SIXTH_FIRE:app_findSixFire(); break;
			case FOURTH_FIRE:app_findFourthFire(); break;
			case EIGHTH_FIRE:app_findEighthFire(); break;
			case SENVENTH_FIRE:app_findSeventhFire();break;
			case RETURN:returnHome(&outfireRobotState);break;
		}
	}

}
