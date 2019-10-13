#ifndef _APP_WORK_H
#define _APP_WORK_H


typedef enum{
	INIT = 0,
  READY,
	DOING,
	FINISH,
}step_e;

typedef enum{
	FIRST_FIRE = 0,		
	SECOND_FIRE,//寻找着火点工作过程枚举类型
	THIRD_FIRE,
	FOURTH_FIRE,
	FIFTH_FIRE,
	SIXTH_FIRE,
	SENVENTH_FIRE,
	EIGHTH_FIRE,
	NINTH_FIRE,					
	RETURN,
}robotTaskstep_e;

typedef enum{
	ROOM_ONE = 0,
	ROOM_TWO,
	ROOM_THREE,
	ROOM_FOUR,
}rescueSelect_e;

typedef enum{
	WALKING_MODE = 0,
	DRIVING_MODE,
	DRIVER_INDEEP,
}rescueTaskstep_e;

typedef enum{	
	ALL_OFF= 0,
	BEHIND_ON,
	FRONT_ON ,	
}fanMode_e;

typedef enum{
	OUT_FIRE1 = 0,
	OUT_FIRE2,
	RESCUE,
}robotType_e;

typedef enum{
	WORK_PRIORITY = 3,
	WORK_STACK_SIZE = 512,
}appWork_e;



void app_fan(void);
void app_judgeFunc(void);
void app_returnFunc(void);
calibrationFinish_e checkFire(void);

void app_outfireOneWorkReady(void);
void app_outfireOneWorkDoing(void);

void app_outfireTwoWorkReady(void);
void app_outfireTwoWorkDoing(void);

void app_rescueWorkReady(void);
void app_rescueWorkDoing(void);



void app_WorkCommandFinish(void);
void app_WorkCommandReset(void);


void app_WorkTaskInit(void);
#endif
