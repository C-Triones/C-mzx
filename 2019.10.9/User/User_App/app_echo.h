#ifndef __APP_ECHO_H
#define __APP_ECHO_H
#include "app.h"

typedef enum{
	ECHO_STACK_SIZE = 512,
	ECHO_PRIORITY = 3,
}appTimer_e;
typedef enum{
	OFF = 0,
	ON,
}echoDirection_e;
typedef struct{
	echoDirection_e frontecho;
	echoDirection_e leftecho;
	echoDirection_e rightecho;
}echoStruct_t;

typedef struct{
	uint8_t step;
	uint8_t state;
}ultrasonicTaskStruct_t;


extern echoStruct_t echoDirection;
extern ultrasonicTaskStruct_t ultrasonicTask;
void app_echoFunc(echoDirection_e frontecho,echoDirection_e leftecho,echoDirection_e rightecho);
void app_echoInit(void);
void app_echoUpdata(void);


#endif
