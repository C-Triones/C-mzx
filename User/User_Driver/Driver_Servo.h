#ifndef __DRIVER_SERVO_H
#define __DRIVER_SERVO_H

#include "BSP_GPIO.h"

#define SERVO1_PORT BSP_GPIOA1
#define SERVO2_PORT BSP_GPIOA2
#define SERVO_USE_TIMER TIM2  //84M
#define SERVO_USE_USE_TIMER_PERIOD (20000-1)
#define SERVO_USE_TIMER_PESCALER (84-1)
#define SERVO_INIT 400
typedef enum{
	FORWARD = 0,
	BACK,
	STOP
}divisonEnum;

typedef struct{
	divisonEnum division;
	int output;
}servoStruct_t;

extern servoStruct_t servo1Data;
extern servoStruct_t servo2Data;
void servo_Init(void);
void servoTest(void);
void servoStart(void);

#endif
