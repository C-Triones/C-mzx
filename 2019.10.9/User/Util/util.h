#ifndef __UTIL_H
#define __UTIL_H

#include "stm32f10x.h"
//#include "FreeRTOS_board.h"
#include <stdlib.h>

#define digitalHi(p)        *p = 1
#define digitalLo(p)        *p = 0
#define digitalSet(p, n)    *p = n
#define digitalGet(p)       (*p)
#define digitalTogg(p)      *p = !(*p)
#define digitalIncreasing(p) *p += 1
#define digitalDecline(p)   *p -= 1
#define digitalClan(p)			*p = 0
#define HIGH	1
#define LOW   0

#define constrainInt(v, lo, hi)	    (((int)(v) < (int)(lo)) ? (int)(lo) : (((int)(v) > (int)(hi)) ? (int)(hi) : (int)(v)))
#define constrainFloat(v, lo, hi)   (((float)(v) < (float)(lo)) ? (float)(lo) : (((float)(v) > (float)(hi)) ? (float)(hi) : (float)(v)))

#define abs(x) ( (x)>0?(x):-(x) )
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define yield(n)		    vTaskDelay(n)

#define	UTIL_STACK_CHECK	    12

#ifdef USE_CCM
#define UTIL_CCM_HEAP_SIZE	    (0x2800)
#else
#define UTIL_CCM_HEAP_SIZE	    (0)	// 0KB
#endif
#define PERIPH2BB(addr, bit)        ((uint32_t *)(PERIPH_BB_BASE + ((addr) - PERIPH_BASE) * 32 + ((bit) * 4)))

// first order filter		一阶滤波器
typedef struct {
    float tc;
    float z1;
} utilFilter_t;

typedef struct {
    const float *window;
    float *data;
    uint8_t n;
    uint8_t i;
} utilFirFilter_t;

//联合体用于转换数据
typedef union{
	u8 		u8_temp[4];
	float float_temp;
	s32 	s32_temp;
	u32		u32_temp;
} formatTrans32Struct_t;

typedef union{
	u8 		u8_temp[2];
	s16 	s16_temp;
	u16		u16_temp;
} formatTrans16Struct_t;

typedef struct {
	uint32_t errorCount;
	uint32_t lastErrorCount;
	uint32_t intervalNum;
} errorScanStruct_t; 

uint16_t *aqStackInit(uint16_t size, char *name);
void *aqCalloc(size_t count, size_t size);
void aqFree(void *ptr, size_t count, size_t size);
void *aqDataCalloc(uint16_t count, uint16_t size);
float removeDeadBand(float value,float deadBand);
void utilFilterInit(utilFilter_t *f, float dt, float tau, float setpoint);
void utilFilterInit2(utilFilter_t *f, float dt, float tau, float setpoint);
void utilFilterInit3(utilFilter_t *f, float dt, float tau, float setpoint);
float utilFilter(utilFilter_t *f, float signal);
float utilFilter2(utilFilter_t *f, float signal);
float utilFilter3(utilFilter_t *f, float signal);
void utilFilterReset(utilFilter_t *f, float setpoint);
void utilFilterReset3(utilFilter_t *f, float setpoint);
float utilFirFilter(utilFirFilter_t *f, float newValue);
void utilFirFilterInit(utilFirFilter_t *f, const float *window, float *buffer, uint8_t n);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
