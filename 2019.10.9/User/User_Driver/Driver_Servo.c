#include "Driver_Servo.h"

servoStruct_t servo1Data;
servoStruct_t servo2Data;
void servo_Init(void){
	BSP_GPIO_Init(SERVO1_PORT,GPIO_Mode_Out_PP);
//	BSP_GPIO_Init(SERVO2_PORT,GPIO_Mode_Out_PP);
//	BSP_TIM_PWM_Init(SERVO_USE_TIMER,SERVO_USE_USE_TIMER_PERIOD,SERVO_USE_TIMER_PESCALER,NULL,SERVO1_PORT,SERVO2_PORT,NULL);
}

static void servoGetValue(servoStruct_t *servoData,int Rate){
	//servoData->division = (divisonEnum)Div;
	if(servoData->division == FORWARD){
		servoData->output = Rate;
	}else if(servoData->division == BACK){
		servoData->output = Rate-400;
	}else{
		servoData->output = 400;
	}
	if(servoData->output <= 0){
		servoData->output = 0;
	}
}

void servoTest(void){
	servoGetValue(&servo1Data,600);
//	servoGetValue(&servo2Data,600);
	TIM_SetCompare2(SERVO_USE_TIMER,servo1Data.output);
//	TIM_SetCompare3(SERVO_USE_TIMER,servo2Data.output);
}

void servoStart(void){
	servo1Data.output = SERVO_INIT;
	servo2Data.output = SERVO_INIT;
	TIM_SetCompare2(SERVO_USE_TIMER,servo1Data.output);
	TIM_SetCompare3(SERVO_USE_TIMER,servo2Data.output);
}
