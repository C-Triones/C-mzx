#include "app.h"

#define ECHO_TASK_PERIOD  35 //30
#define ECHO_UPDATA_TIME  20 //1000
appStruct_t appTimer;
ultrasonicTaskStruct_t ultrasonicTask;
echoStruct_t echoDirection;
uint32_t loop;
void echo_Delay(uint32_t t){
	unsigned int i;
	unsigned char a;
	for( i=0;i<t;i++){
		for (a = 0; a < 6; a++);
	}
}
void app_echoUpdata(){
	switch(loop){
		case 1:
			ultrasonicTask.step = 1;
			TRIG1 = 1; 
			echo_Delay(ECHO_UPDATA_TIME);
			TRIG1 = 0;
			break;
		case 2:
			ultrasonicTask.step = 2;
			TRIG2 = 1;
			echo_Delay(ECHO_UPDATA_TIME);
			TRIG2 = 0;
			break;
		case 3:
			ultrasonicTask.step = 3;
			TRIG3 = 1;
			echo_Delay(ECHO_UPDATA_TIME);
			TRIG3 = 0;
			break;
		case 4:
			ultrasonicTask.step = 4;
			TRIG4 = 1;
			echo_Delay(ECHO_UPDATA_TIME);
			TRIG4 = 0;
			break;
		case 5:
			ultrasonicTask.step = 5;
			TRIG5 = 1;
			echo_Delay(ECHO_UPDATA_TIME);
			TRIG5 = 0;
			break;
		case 6:
			ultrasonicTask.step = 6;
			TRIG6 = 1;
			echo_Delay(ECHO_UPDATA_TIME);
			TRIG6 = 0;
			loop=0;
			break;
		default:break;
	}
	loop++;
}

void app_echoTask(void *Parameters){
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime,ECHO_TASK_PERIOD);
		app_echoUpdata();
		vTaskDelay(1);
		
	}
}
void app_echoInit(){
	xTaskCreate(app_echoTask,"TIMER",ECHO_STACK_SIZE,NULL,ECHO_PRIORITY,&appTimer.xHandleTask);
	ultrasonicTask.step = 1;
}
