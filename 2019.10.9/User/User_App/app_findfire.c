#include "app.h"

#define ADC_TASK_PERIOD 1
appStruct_t appfindFire;
adcTestStruct_t adcTestData;
void appfindFireUpdata(void){
	getadc_average(adcTestData.adcData);
}

void app_findFireTask(void *Parameters){
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime,ADC_TASK_PERIOD);
		appfindFireUpdata();
	}
}

void appfindFire_Init(void){
	xTaskCreate(app_findFireTask,"ADC",ADC_STACK_SIZE,NULL,ADC_PRIORITY,&appfindFire.xHandleTask);
}
