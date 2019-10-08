#include "app.h"

#define INPUT_TASK_PERIOD	5
appStruct_t appInput;
void app_inputUpdata()
{
	driverPhotoelectricSwitchNowStateUpdate();
	driverKeyNowStateUpdate();
	appInput.loops += INPUT_TASK_PERIOD;
}

void app_inputTask(void *Parameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, INPUT_TASK_PERIOD);
		app_inputUpdata();
	}
}

void app_inputTaskInit(void)
{
	xTaskCreate(app_inputTask,"INPUT",INPUT_STACK_SIZE,NULL,INPUT_PRIORITY,&appInput.xHandleTask);
}
