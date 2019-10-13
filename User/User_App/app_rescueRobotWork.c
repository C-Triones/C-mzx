#include "app.h"
uint8_t temp=0;
LimiFlag_t LimiFlag;
void roomChoose(rescueRobotState_t *rescueRobotState);
void roomChoose_back(rescueRobotState_t *rescueRobotState);
void app_rescueWorkReady(void)
{
	/*待补充*/ //用按键控制小车启动//
	if(rescueRobotState.workMode == RESCUEING){
		rescueRobotState.step = DOING;
		rescueRobotState.workStep = NULL;
		rescueRobotState.rescueTaskstep = WALKING_MODE;
		command = '0';
	}
}
/***寻物块任务**/
void app_rescueWorkDoing(void){
	app_UCLIMI_FORNT(SRF_04_Data1.getDistance,SRF_04_Data2.getDistance); //前限位
	app_UCLIMI_LEFT (SRF_04_Data3.getDistance,SRF_04_Data4.getDistance);  //左限位
	app_UCLIMI_RIGHT(SRF_04_Data5.getDistance,SRF_04_Data6.getDistance); //右限位
	app_UCLIMI_SPEED(SRF_04_Data1.getDistance,SRF_04_Data2.getDistance);  //速度限制
	if(rescueRobotState.beginFlag == FREE && rescueRobotState.workMode != TEST){
		switch(rescueRobotState.rescueTaskstep){
			case WALKING_MODE:roomChoose(&rescueRobotState);break;
			case DRIVING_MODE:wifiControl(command);break;
			case DRIVER_INDEEP:roomChoose_back(&rescueRobotState);break;
		}
	
	}
}
 
///////////救援串口控制限位////////////////
void app_UCLIMI_SPEED(float distance1,float distance2){
	if((distance1<25.0)&&(distance2<25.0)){
	  speed_cut = go;
	}
	else{
		speed_cut = stop;
	}
}

void app_UCLIMI_FORNT(float distance1,float distance2){//前限位
 if((distance1<15.0)&&(distance2<15.0))  LimiFlag.forward = stop;
   else  LimiFlag.forward = go;
} 
void app_UCLIMI_LEFT(float distance1,float distance2){ //左限位
 if((distance1<13.0)&&(distance2<13.0)) LimiFlag.left = stop;
   else  LimiFlag.left = go;
}  
void app_UCLIMI_RIGHT(float distance1,float distance2){//右限位
 if((distance1<13.0)&&(distance2<1.0))  LimiFlag.right = stop;
   else LimiFlag.right = go;
}
///////////rescue_AUTOTASK/////////////////
void rescue_AUTOTASK_PUTCLAW(void){
		app_CLAW_HOLDorUNON(claw_UNON,250);
		vTaskDelay(20);		
		app_CLAW_UPorDOWN(claw_DOWN,255);
		app_CAMERA_UPorDOWN(camera_DOWN,220);	
}
void rescue_AUTOTASK_HOLDCLAW(void){
		app_CLAW_HOLDorUNON(claw_HOLD,320);
		vTaskDelay(500);	
		app_CLAW_UPorDOWN(claw_UP,210);
		app_CAMERA_UPorDOWN(camera_UP,120);
}
/***********rescue_AutoBackTask****/
/***********doing know*************/
void app_back_One(void){	
	switch (temp){
		case 0:{
			rescueRobotState.moveWays = OTHER;
			temp++;
			break;	
		}	 	
		case 1:{
			rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			temp++;						
		break;
		}
		case 2:{
		  rescueRobotState.moveWays = STOP;
			temp++;
			break;
		}
		case 3:{
		   calibrationGostraight(LEFT);
			if(SRF_04_Data1.getDistance <24 && SRF_04_Data2.getDistance <24){
				rescueRobotState.moveWays = STOP;
			temp++;
			}
			break;
		}
		case 4:{
		  rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			temp++;
			break;
		}
		case 5:{
		  rescueRobotState.moveWays = STOP;
			temp++;
			break;
		}
		case 6:{
			calibrationGostraight(LEFT);
			if(SRF_04_Data1.getDistance <=30 && SRF_04_Data2.getDistance <=30){
			temp=99;
			}
		 break;
		}
		case 99:{
			rescueRobotState.moveWays = OTHER;
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
			default :rescueRobotState.moveWays = STOP; break;
  }
}

void app_back_Two(void){
	switch (temp){
	case 0:{
		rescueRobotState.moveWays = OTHER;
		app_goOtherAction(1,NO_TURN,BEHIND);
		if(SRF_04_Data1.getDistance <=19 && SRF_04_Data2.getDistance <=19){	
			temp++;
		}
			
			break;
		}		
		case 1:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;			
			temp++;
		break;
		}
		case 2:{		
		  rescueRobotState.moveWays = STOP;
			temp++;		
			break;
		}		
	case 3:{
		   calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
			temp++;
			}			 	
			break;
		}
	case 4:{
			rescueRobotState.moveWays= GO_STRAIGHT;
		  if(SRF_04_Data1.getDistance <=26 && SRF_04_Data2.getDistance <=26){
			temp++;			
		  }
		   break;
			}
			case 5:{
			rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;			
			temp++;
		break;
		}
		case 6:{		
		  rescueRobotState.moveWays = STOP;
			temp++;		
			break;
		}
		case 7:{
				rescueRobotState.moveWays= GO_STRAIGHT;
			  vTaskDelay(1900);
				temp++;
			break;
		}
		case 8:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
			temp++;
		break;
		}
		case 9:{
		  rescueRobotState.moveWays = STOP;
			temp++;
			break;
		}
		case 10:{
		  calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
			temp=99;
		}
			break;
  	}
     case 99:{
			rescueRobotState.moveWays = OTHER;
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
				default : rescueRobotState.moveWays = STOP; break;
    }
}
void app_back_Three(void){
	switch (temp){
		case 0:{
			rescueRobotState.moveWays = OTHER;
			temp++;
			break;
		}		
		case 1:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;			
			temp++;
		break;
		}
		case 2:{		
		  rescueRobotState.moveWays = STOP;
			temp++;		
			break;
		}		
	  case 3:{
		   calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
			temp++;
			}			 	
			break;
		}
	  case 4:{
			calibrationGostraight(LEFT);
		  if(SRF_04_Data5.getDistance >=50 && SRF_04_Data6.getDistance >=50){
			temp++;			
		  }
		   break;
			}
		case 5:{
				rescueRobotState.moveWays= GO_STRAIGHT;
			  vTaskDelay(2200);
				temp++;
			break;
		}
		case 6:{
			rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			temp++;
		break;
		}
	  case 7:{
		  rescueRobotState.moveWays = STOP;
			temp++;
			break;
		}
		case 8:{
		  calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
			temp=99;
		}
			break;
  	}
    case 99:{
			rescueRobotState.moveWays = OTHER;
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
		default : rescueRobotState.moveWays = STOP; break;
   }
}

void app_back_Four(void){
	switch (temp){
		case 0:{
			rescueRobotState.moveWays = OTHER;
			temp++;
			break;
		}		
		case 1:{
			rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			temp++;			
		break;
		}
		case 2:{
		  rescueRobotState.moveWays = STOP;
			temp++;
			break;
		}
    case 3:{
		   calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
			temp++;
			}			 	
			break;
		}
		case 4:{
				 rescueRobotState.moveWays= GO_STRAIGHT;
				 vTaskDelay(1800);
						temp++;
					break;
				}
		case 5:{
			rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			temp++;
		break;
		}
		case 6:{
		  rescueRobotState.moveWays = STOP;
			temp++;
			break;
		}
		case 7:{
		  calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <30 && SRF_04_Data2.getDistance <30){
			temp=99;
		}
			break;
  	}
    case 99:{
			rescueRobotState.moveWays = OTHER;
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
		default : rescueRobotState.moveWays = STOP; break;
   }
}
void app_RoomOne(void){
	switch(rescueRobotState.workStep){
		case 0:{
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.workStep++;
			}break;
		}
		case 1:{
			rescueRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <24 && SRF_04_Data2.getDistance <24){
				rescueRobotState.workStep++;
			}break;
		}
		case 2:{
			rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep++;
			break;
		}
		case 3:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
			rescueRobotState.workStep++;
			break;
		}
		case 4:{
			rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep++;
			break;
		}
		case 5:{
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.workStep++;
			}break;
		}
		case 6:{
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <= 76&& SRF_04_Data2.getDistance <= 76){
				rescueRobotState.moveWays = STOP;
				rescueRobotState.workStep++;
			}break;
		}
		case 7:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
			rescueRobotState.workStep++;
			break;
		}
		case 8:{
			rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep = 99;
			break;
		}
		case 99:{
			rescueRobotState.moveWays = OTHER;
			rescueRobotState.workStep = 99;
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
	}
}
void app_RoomTwo(void){
	switch(rescueRobotState.workStep){
  case 0:{
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.moveWays = OTHER;
				rescueRobotState.workStep++;
			}break;
		}
			case 1:{
			  rescueRobotState.moveWays =GO_STRAIGHT;
				rescueRobotState.workStep++;
				break;		
				}				
			case 2:{
				if(SRF_04_Data1.getDistance <=22 && SRF_04_Data2.getDistance <=22){
			 rescueRobotState.moveWays =REVERSE_RIGHT_TURN_90;
				rescueRobotState.workStep ++;
				}
				break;
			}
			case 3:{
				rescueRobotState.moveWays = STOP;
				rescueRobotState.workStep++;
				break;
				}
			case 4:{
		    calibrationFinish = app_calibration(LEFT);
			 if(calibrationFinish == CALIBRATION_FINISHED){
			     rescueRobotState.workStep++;
			  }			 	
			break;
	   	}
		 case 5:{
				rescueRobotState.moveWays= GO_STRAIGHT;
			  vTaskDelay(1800);
				rescueRobotState.workStep++;
			break;
		 }
		 case 6:{
			 if(SRF_04_Data4.getDistance >=40 && SRF_04_Data6.getDistance <=25){
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
			rescueRobotState.workStep++;
			 }
		break;
		}
		case 7:{
		  rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep++;
			break;
		}
		case 8:{
		  rescueRobotState.moveWays= GO_STRAIGHT;
			if(SRF_04_Data4.getDistance <=25 && SRF_04_Data6.getDistance <=25){
				rescueRobotState.moveWays = STOP;
			 rescueRobotState.workStep++;
			}
			break;
		}
		case 9:{
				 calibrationFinish = app_calibration(LEFT);
			 if(calibrationFinish == CALIBRATION_FINISHED){
			     rescueRobotState.workStep++;
			  }			 	
			break;
		}
		case 10:{
		        rescueRobotState.moveWays= GO_STRAIGHT;
			if(SRF_04_Data1.getDistance <25 && SRF_04_Data2.getDistance <25){
			rescueRobotState.workStep++;
		}
		break;	
		}
		case 11:{
		  rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
			rescueRobotState.workStep++;
			break;
  	}
			case 12:{
		  rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep=99;
			break;
		}
     case 99:{
			rescueRobotState.moveWays = OTHER;
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
			default : rescueRobotState.moveWays = STOP; break;
			}
}
void app_RoomThree(void){
	switch(rescueRobotState.workStep){
		case 0:{
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.workStep++;
			}break;
		}
		case 1:{
		 calibrationGostraight(LEFT);
			if(SRF_04_Data1.getDistance <=17 && SRF_04_Data2.getDistance <=17){
				rescueRobotState.workStep++;
			}
			break;
		}
			case 2:{
					rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
					rescueRobotState.workStep++;
				break;
			}
			case 3:{			 
			 rescueRobotState.moveWays = STOP;
				rescueRobotState.workStep++;
				break;
			}
			case 4:{
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.workStep++;
			}break;
		}			
			case 5:{
       calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <=20 && SRF_04_Data2.getDistance <=20){
				rescueRobotState.workStep++;
				}
			break;
			}
			case 6:{
				rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				rescueRobotState.workStep++;
				break;			
			}
			case 7:{
				rescueRobotState.moveWays = STOP;
				rescueRobotState.workStep = 99;
				break;
			}
			case 99:{
				rescueRobotState.moveWays = OTHER;
				rescueRobotState.workStep = 0;
				rescueRobotState.rescueTaskstep = DRIVING_MODE;
				break;
		}
   }
}
void app_RoomFour(void){
	switch(rescueRobotState.workStep){
		case 0:{
			calibrationFinish = app_calibration(LEFT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.workStep++;
			}break;
		}
		case 1:{
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <24 && SRF_04_Data2.getDistance <24){
				rescueRobotState.workStep++;
			}break;
		}
		case 2:{
			rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep++;
			break;
		}
		case 3:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
			rescueRobotState.workStep++;
			break;
		}
		case 4:{
			rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep++;
			break;
		}
		case 5:{
			calibrationFinish = app_calibration(RIGHT);
			if(calibrationFinish == CALIBRATION_FINISHED){
				rescueRobotState.workStep++;
			}break;
		}
		case 6:{
			rescueRobotState.moveWays = GO_STRAIGHT;
			calibrationGostraight(RIGHT);
			if(SRF_04_Data1.getDistance <= 72&& SRF_04_Data2.getDistance <= 72){
				rescueRobotState.moveWays = STOP;
				rescueRobotState.workStep++;
			}break;
		}
		case 7:{
			rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;
			rescueRobotState.workStep++;
			break;
		}
		case 8:{
			rescueRobotState.moveWays = STOP;
			rescueRobotState.workStep = 99;
			break;
		}
		case 99:{
			rescueRobotState.moveWays = OTHER;
			rescueRobotState.workStep = 99;
			rescueRobotState.rescueTaskstep = DRIVING_MODE;
			break;
		}
	}
}	
void roomChoose(rescueRobotState_t *rescueRobotState){
	switch(rescueRobotState->rescuePosition){
		case ROOM_ONE:app_RoomOne();break;
		case ROOM_TWO:app_RoomTwo();break;
		case ROOM_THREE:app_RoomThree();break;
		case ROOM_FOUR:app_RoomFour();break;
	}
}

void roomChoose_back(rescueRobotState_t *rescueRobotState){
	switch(rescueRobotState->rescuePosition){
		case ROOM_ONE:app_back_One();    break;
		case ROOM_TWO:app_back_Two();    break;
		case ROOM_THREE:app_back_Three();break;
		case ROOM_FOUR:app_back_Four();  break;
	}
}


