#ifndef __DRIVER_SRF_05_H
#define __DRIVER_SRF_05_H

#include "BSP_GPIO.h"
#include "BSP_Timer.h"
#include "BSP_PWM.h"
#include "BSP_EXIT.h"

#define SRF_05_TRIG BSP_GPIOE8
#define SRF_05_ECHO BSP_GPIOE9
#define SRF_05_USE_TIMER TIM3
#define SRF_05_USE_TIMER_PERIOD (5000-1)
#define SRF_05_USE_TIMER_PESCALER (84-1)
#define SRF_05_USE_TIMER_PREEMPTIONPRIORITY 2
#define SRF_05_USE_TIMER_SUBPRIORITY 0
#define TIMER_CONTER_INIT 0
#define TRIG_OUT PEout(8)
#define ECHO_IN PEin(9)
typedef struct{
	int msCount;
	int echoTime;
	float getDistance;
}ultrasonicStruct_t;
	
extern ultrasonicStruct_t SRF_05_Data;
void SRF_05_Init(void);
void SRF_05_Start(void);
void Get_Distance(void);

#endif
