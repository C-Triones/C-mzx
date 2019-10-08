#ifndef __DRIVER_ECHO_H
#define __DRIVER_ECHO_H
#include "bsp.h"

#define ECHO_TIMER TIM4
#define ECHO_TIMER_PERIOD 65535
#define ECHO_TIMER_PESCALER 71
#define ECHO_TIMER_PREEMPTIONPRIORITY 0x04
#define ECHO_TIMER_TIMER_SUBPRIORITY 0x00
//1
#define SRF04_TRIG1 BSP_GPIOE10
#define SRF04_ECHO1 BSP_GPIOE4
#define TRIG1 PEout(10)
#define ECHO1 PEin(4)
//2
#define SRF04_TRIG2 BSP_GPIOE11
#define SRF04_ECHO2 BSP_GPIOE5
#define TRIG2 PEout(11)
#define ECHO2 PEin(5) 
//3
#define SRF04_TRIG3 BSP_GPIOE12
#define SRF04_ECHO3 BSP_GPIOE6
#define TRIG3 PEout(12)
#define ECHO3 PEin(6) 
//4
#define SRF04_TRIG4 BSP_GPIOE13
#define SRF04_ECHO4 BSP_GPIOE7
#define TRIG4 PEout(13)
#define ECHO4 PEin(7) 
//5
#define SRF04_TRIG5 BSP_GPIOE14
#define SRF04_ECHO5 BSP_GPIOE8
#define TRIG5 PEout(14)
#define ECHO5 PEin(8) 
//6
#define SRF04_TRIG6 BSP_GPIOE15
#define SRF04_ECHO6 BSP_GPIOE9
#define TRIG6 PEout(15)
#define ECHO6 PEin(9) 

typedef struct{
	int device;
	int msCount;
	float getDistance;
	uint32_t axis;
	float gyoSum[6];
}ultrasonicStruct_t;

extern ultrasonicStruct_t SRF_04_Data1;
extern ultrasonicStruct_t SRF_04_Data2;
extern ultrasonicStruct_t SRF_04_Data3;
extern ultrasonicStruct_t SRF_04_Data4;
extern ultrasonicStruct_t SRF_04_Data5;
extern ultrasonicStruct_t SRF_04_Data6;


void driver_echo(void);


#endif
