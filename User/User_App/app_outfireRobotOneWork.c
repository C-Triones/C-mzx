#include "app.h"

#define	DISTANCE_TO_FIRE  30





//  ��������ǽ�ľ��� ������  Flash
calibrationFinish_e calibrationFinish;
void app_outfireOneWorkReady(void)
{
		int i;
	/*������*/ //�ð�������С������//
	//finishFlag = SET_ZERO;
	if(outfireRobotState.workMode == OUT_FIRE){
		outfireRobotState.robotTaskstep = FIRST_FIRE;
		outfireRobotState.step = DOING;
		outfireRobotState.workStep = NULL;
		for(i = 0;i < 9;i++){outfireRobotState.returnFlag[i] = 0;} //��ʼ�����Ѱ�Һͷ��غ���
		for(i = 0;i < 9;i++){outfireRobotState.fireArray[i] = 0;}
		/***********��ʼ�����λ��*********/
		outfireRobotState.fireArray[FIRST_FIRE] = 1;
		outfireRobotState.fireArray[NINTH_FIRE] = 1;
		outfireRobotState.fireArray[THIRD_FIRE] = 1;
		outfireRobotState.fireArray[SECOND_FIRE] = 1;
		app_judgeFunc();
		if(outfireRobotState.returnFlag[RETURN] == 1){   //ȫ�޻�   ֱ�ӵ����һ��
			outfireRobotState.robotTaskstep = RETURN;
		}
	}
	
	
}

/***************һ�������걸***************/
void app_findFirstFire(void){
	if(outfireRobotState.fireArray[FIRST_FIRE] == 1){   //�л�
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
				if(SRF_04_Data1.getDistance < 25 && SRF_04_Data2.getDistance <25){

					outfireRobotState.workStep = 3;
				}
			break;
			}
			case 3:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance < DISTANCE_TO_FIRE && calibrationFinish == CALIBRATION_FINISHED){
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
				app_fan();																										//������
				outfireRobotState.workStep = 6;
			break;
			}
			case 6:{
				outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;
				outfireRobotState.workStep = 7;
			break;
			}
			case 7:{
				outfireRobotState.moveWays = STOP;
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
	else {																						//һ����޻�
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

/***************�Ż���������***************/
void app_findNinthFire(void){  																			 //��һ���ж����޻���֮�����������̬����������û�У�����һ�Ż��λ����Ϊ�����������
	if(outfireRobotState.fireArray[NINTH_FIRE] == 1){										//�л�
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
//				outfireRobotState.moveWays = GO_STRAIGHT;
				calibrationGostraight(RIGHT);
				if(SRF_04_Data3.getDistance < 17 && SRF_04_Data4.getDistance < 17){
					outfireRobotState.workStep = 3;
				}
			break;
			}
			case 3:{
				calibrationGostraight(RIGHT);
				if(SRF_04_Data3.getDistance > 30 && SRF_04_Data4.getDistance < 30){
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
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance  < DISTANCE_TO_FIRE && calibrationFinish == CALIBRATION_FINISHED){   /**�����ľ���**/
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
				app_fan();				//���������
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_135;
				outfireRobotState.workStep = 9;
			break;
			}
			case 9:{//�����Ӻ���
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
				if(SRF_04_Data1.getDistance > 20 && SRF_04_Data2.getDistance > 20 && SRF_04_Data1.getDistance < 30 && SRF_04_Data2.getDistance <30){
					outfireRobotState.workStep = 12;
				}
			break;
			}
			case 12:{
				outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;
				outfireRobotState.workStep = 13;
			break;
			}
			case 13:{//�����Ӻ���
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
//				calibrationGostraight(LEFT);
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
				calibrationFinish = app_calibration(RIGHT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					
				}
				outfireRobotState.workStep = 19;
			break;
			}
			case 19:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			break;
			}
			//�ص���һ�׶�λ��
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
//				outfireRobotState.moveWays = GO_STRAIGHT;
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
/***************�������������***************/
void app_findThirdFire(void){
	if(outfireRobotState.fireArray[THIRD_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = GO_STRAIGHT;
//				if(SRF_04_Data1.getDistance < 40 && SRF_04_Data2.getDistance < 40){   //����1�ͷ���2֮��Ĺ��� 
//					outfireRobotState.moveWays = STOP;
//					outfireRobotState.workStep = 'a';
//				}
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
				vTaskDelay(1000);
				outfireRobotState.workStep = 8;
			break;
			}
			case 8:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance < 22 && SRF_04_Data2.getDistance < 22 ){
					outfireRobotState.workStep = 9;
				}
			break;
			}
			case 9:{
				calibrationFinish = app_findFire();
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance + SRF_04_Data2.getDistance  < DISTANCE_TO_FIRE && calibrationFinish == CALIBRATION_FINISHED){   /**�����ľ���**/
					outfireRobotState.moveWays = STOP;
					outfireRobotState.workStep = 10;
				}
			break;
			}
			case 10:{
				app_fan();				//���������
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep = 11;
			break;
			}
			case 11:{
				calibrationFinish = app_calibration(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(calibrationFinish == CALIBRATION_FINISHED){
					outfireRobotState.workStep = 99;
				}
			break;
			}
			case 99:
				if(outfireRobotState.returnFlag[NINTH_FIRE] == 1)
					outfireRobotState.robotTaskstep = RETURN;
				else{
					outfireRobotState.robotTaskstep = SECOND_FIRE;
				}			
				outfireRobotState.workStep = 0;
				outfireRobotState.moveWays = OTHER;			
			break;
			}
		
	}
	else{																											//û��
		switch(outfireRobotState.workStep){
			case 0:{
				outfireRobotState.moveWays = GO_STRAIGHT;
//				if(SRF_04_Data1.getDistance < 40 && SRF_04_Data2.getDistance < 40){   //����1�ͷ���2֮��Ĺ��� 
//					outfireRobotState.moveWays = STOP;
//					outfireRobotState.workStep = 'a';
//				}
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
				if(SRF_04_Data5.getDistance > 30 && SRF_04_Data6.getDistance < 30){
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
//				if(SRF_04_Data1.getDistance < 20 && SRF_04_Data2.getDistance < 20){
//					
//					outfireRobotState.moveWays = STOP;
//				}
				vTaskDelay(1000);
				outfireRobotState.workStep = 8;
			break;
			}
			case 8:{
				calibrationGostraight(LEFT);
				outfireRobotState.moveWays = OTHER;
				if(SRF_04_Data1.getDistance < 22 && SRF_04_Data2.getDistance < 22 ){
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
				outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;
				outfireRobotState.workStep = 11;
			break;
			}
			case 11:{
//				calibrationFinish = app_calibration(LEFT);
//				outfireRobotState.moveWays = OTHER;
//				if(calibrationFinish == CALIBRATION_FINISHED){
//					outfireRobotState.workStep = 99;
//				}
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;
			break;
			}
			case 99:
				outfireRobotState.workStep = 0;
				outfireRobotState.robotTaskstep = SECOND_FIRE;
			break;
			}	
	}
}

void app_findSecondFire(void){  
	if(outfireRobotState.fireArray[SECOND_FIRE] == 1){
		switch(outfireRobotState.workStep){
			case 0:{
				calibrationGostraight(LEFT);
				if(SRF_04_Data1.getDistance < 50 && SRF_04_Data2.getDistance < 40){
					outfireRobotState.moveWays = FRONT_TURN_RIGHT_135;
					outfireRobotState.workStep = 1;	
				}
			break;
			}
			case 1:{
				outfireRobotState.moveWays = STOP;
				outfireRobotState.workStep = 99;	
			break;
			}
			case 99:
				outfireRobotState.workStep = 0;
				outfireRobotState.robotTaskstep = RETURN;
			break;
			}
	}
}

//�ڵ㷵�̺���
void app_returnFunc(void){
	if(outfireRobotState.returnFlag[FIRST_FIRE] == 1){
		
	}else if(outfireRobotState.returnFlag[SECOND_FIRE] == 1){
		
	}else if(outfireRobotState.returnFlag[THIRD_FIRE] == 1){
		
	}else if(outfireRobotState.returnFlag[NINTH_FIRE] == 1){
	
	}else if(outfireRobotState.returnFlag[RETURN] == 1){
		outfireRobotState.moveWays = STOP;
	}
	
		//·��1

}



void app_judgeFunc(void){
	uint8_t roadCase = 1;
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
}

/***Ѱ������**/
void app_outfireOneWorkDoing(void){
	//��һ�����ؽڵ��жϺ�����һ���ж���������
	if(outfireRobotState.beginFlag == FREE && outfireRobotState.workMode != TEST){
		switch(outfireRobotState.robotTaskstep){
			case FIRST_FIRE:app_findFirstFire(); break;
			case NINTH_FIRE:app_findNinthFire(); break;
			case THIRD_FIRE:app_findThirdFire(); break;
			case SECOND_FIRE:app_findSecondFire(); break;
			case RETURN:break;
		}
	}
}

