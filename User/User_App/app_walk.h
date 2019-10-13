#ifndef _APP_WALK_H
#define _APP_WALK_H

typedef enum{
	WALK_PRIORITY = 5 ,
	WALK_STACK_SIZE = 512,
}appWalk_e;

typedef enum{
	LEFT = 1,
	RIGHT,
	NO_TURN,
}turnDirection_e;


typedef enum{
	TESTING = 0,
	WAITING,
}testTarget_e;


typedef enum{
	FRONT = 1,
	BEHIND,
}handDirection_e;

typedef enum{

	FRONT_TURN_LEFT_TIME_90  = 2000,
	FRONT_TURN_LEFT_TIME_180 = 2000,
	
	FRONT_TURN_RIGHT_TIME_90 = 2000,
	FRONT_TURN_RIGHT_TIME_180 = 2000,
	
	FRONT_TURN_LEFT_TIME_135 = 2428,
	FRONT_TURN_LEFT_TIME_45 = 2000,
	
	FRONT_TURN_RIGHT_TIME_135= 2778,
	FRONT_TURN_RIGHT_TIME_45= 2000,
	
	BEHIND_TURN_LEFT_TIME_45= 1179,
	BEHIND_TURN_RIGHT_TIME_45= 1179,
	
	REVERSE_TURN_LEFT_TIME_45 = 269,
	REVERSE_TURN_LEFT_TIME_90 = 420,
	REVERSE_TURN_LEFT_TIME_135 = 632,
	REVERSE_TURN_LEFT_TIME_180 = 889,
	
	REVERSE_TURN_RIGHT_TIME_45 = 269,
	REVERSE_TURN_RIGHT_TIME_90 = 420,
	REVERSE_TURN_RIGHT_TIME_135 = 632,
	REVERSE_TURN_RIGHT_TIME_180 = 889,
	
	GO_STRAIGHT_TIME = 2000,
	
 	SET_ZERO_TIME = 2000,
}turnTimeParameter_e;

typedef enum{
	TURN_LEFT__LEFT_RATE = 6,  
	TURN_LEFT__RIGHT_RATE = 17,
	TURN_RIGHT__LEFT_RATE = 17,
	TURN_RIGHT__RIGHT_RATE = 6,
}valueTurnParameter_e;

typedef enum{
	
	REVERSE_LEFT_TURN__RIGHT_RATE = 20,
	REVERSE_LEFT_TURN__LEFT_RATE = 20,
	
	REVERSE_RIGHT_TURN__RIGHT_RATE = 20,
	REVERSE_RIGHT_TURN__LEFT_RATE = 20,

	GO_STRAIGHT__LEFT_RATE = 20,
	GO_STRAIGHT__RIGHT_RATE = 20,
	
}valueOfStraighParameter_e;


typedef enum{
	SET_ZERO__LEFT_RATE = 200,
	SET_ZERO__RIGHT_RATE = 200,
}valueOfSetZero_e;


typedef enum{
	CALIBRATION_FINISHED = 0,
	CALIBRATION_WAITING,
	CALIBRATION_NULL,
}calibrationFinish_e;

typedef enum{
	TEST = 0,
	OUT_FIRE ,
	RESCUEING,
}workMode_e;

typedef enum{
	STOP = 1,
	
	FRONT_TURN_LEFT_90,
	FRONT_TURN_LEFT_180,
	FRONT_TURN_RIGHT_90,
	FRONT_TURN_RIGHT_180,
	
	FRONT_TURN_LEFT_135,
	FRONT_TURN_LEFT_45,
	FRONT_TURN_RIGHT_135,
	FRONT_TURN_RIGHT_45,
	
	BEHIND_TURN_LEFT_45,
	BEHIND_TURN_RIGHT_45,

	REVERSE_LEFT_TURN_45,
	REVERSE_RIGHT_TURN_45,
	
	REVERSE_LEFT_TURN_90,
	REVERSE_RIGHT_TURN_90,
	
	REVERSE_LEFT_TURN_135,
	REVERSE_RIGHT_TURN_135,
	
	REVERSE_LEFT_TURN_180,
	REVERSE_RIGHT_TURN_180,
	
	OTHER,
	
	GO_STRAIGHT,

	SET_ZERO,
	
}moveWays_e;

typedef enum{
	BUSY = 0,
	FREE,
}beginFlag_e;

typedef struct{ //方向控制限位标志
  u8 forward;
  u8 left;
  u8 right;	
}LimiFlag_t;
typedef enum{
	stop = 0,
  go,
}work_e;

extern LimiFlag_t LimiFlag;
extern moveWays_e finishFlag;
extern calibrationFinish_e calibrationFinish;
extern uint8_t speed_cut;
/////////////抓取机构控制/////////
void app_CLAW_UPorDOWN(uint8_t mode,uint32_t rata);
void app_CLAW_HOLDorUNON(uint8_t mode,uint32_t rata);
void app_CAMERA_UPorDOWN(uint8_t mode,uint32_t rate);
void rescue_AUTOTASK_PUTCLAW(void);
void rescue_AUTOTASK_HOLDCLAW(void);
///////////////////////////////
////////////自动回城///////////
//////////////////////////////
void app_back_One(void);
void app_back_Two(void);
void app_back_Three(void);
void app_back_Four(void);
/////////////////////////////////
/////////////串口控制限位/////////
void app_UCLIMI_FORNT(float distance1,float distance2); //前限位
void app_UCLIMI_LEFT(float distance1,float distance2);  //左限位
void app_UCLIMI_RIGHT(float distance,float distance2); //右限位
void app_UCLIMI_SPEED(float distance,float distance2);//速度控制
//////////////////////////////////

void app_LeftWheel(uint8_t mode,uint32_t rate);
void app_RightWheel(uint8_t mode,uint32_t rate);
void app_turnAngleDirection(uint8_t leftWheelDirection,uint32_t leftWheelRate,
                            uint8_t rightWheelDirection,uint32_t rightWheelRate,
														uint32_t WaitingTime);
void app_goOtherAction(uint16_t goTime,turnDirection_e direction,handDirection_e hand);
void app_setZero(void);
void app_walkStop(void);
void app_goStraight(void);
void app_goBack(uint16_t goTime,turnDirection_e direction);
void app_frontTurn(turnDirection_e direction,uint16_t angle);
void app_behindTurn(turnDirection_e direction,uint16_t angle);
void app_reverseTurn(turnDirection_e direction,uint16_t angle);
void calibrationGostraight(turnDirection_e direction);
calibrationFinish_e app_findFire(void);
calibrationFinish_e app_calibration(turnDirection_e direction);
void app_walkWaysChoose(void);
void app_walkTaskInit(void);
#endif
