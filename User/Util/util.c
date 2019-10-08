#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_CCM
uint32_t heapUsed, heapHighWater, dataSramUsed;
uint32_t *ccmHeap[UTIL_CCM_HEAP_SIZE] __attribute__((section(".ccm")));
#ifdef UTIL_STACK_CHECK
int32_t numStacks;
void *stackPointers[UTIL_STACK_CHECK] __attribute__((section(".ccm")));
uint16_t stackSizes[UTIL_STACK_CHECK] __attribute__((section(".ccm")));
uint16_t stackFrees[UTIL_STACK_CHECK] __attribute__((section(".ccm")));
char *stackNames[UTIL_STACK_CHECK] __attribute__((section(".ccm")));
#endif


void *aqCalloc(size_t count, size_t size) {
    char *addr = 0;

    if (count * size) {
				addr = malloc(count*size);
        heapUsed += count * size;
        if (heapUsed > heapHighWater)
            heapHighWater = heapUsed;
 //       if (addr == 0)
 //           AQ_NOTICE("Out of heap memory!\n");
    }

    return addr;
}

void aqFree(void *ptr, size_t count, size_t size) {
    if (ptr) {
        free(ptr);
        heapUsed -= count * size;
    }
}

// allocates memory from 64KB CCM
void *aqDataCalloc(uint16_t count, uint16_t size) {
    uint32_t words;

    // round up to word size
    words = (count*size + sizeof(int)-1) / sizeof(int);

    if ((dataSramUsed + words) > UTIL_CCM_HEAP_SIZE) {
//        AQ_NOTICE("Out of data SRAM!\n");
    }
    else {
        dataSramUsed += words;
    }

    return (void *)(ccmHeap + dataSramUsed - words);
}

// size in words
uint16_t *aqStackInit(uint16_t size, char *name) {
    uint16_t *sp;

    // use memory in the CCM
    sp = (uint16_t *)aqDataCalloc(1, size*4);

    // fill memory with pattern to ease overflow detection
    memset(sp, 0xFF, size*4);

#ifdef UTIL_STACK_CHECK
    stackPointers[numStacks] = sp;
    stackSizes[numStacks] = size*4;
    stackFrees[numStacks] = stackSizes[numStacks];
    stackNames[numStacks] = name;
    numStacks++;
#endif

    return sp;
}
#endif

float removeDeadBand(float value,float deadBand){
	float factvalue;
	if(value > deadBand)
		factvalue = value - deadBand;
	else
		factvalue = value + deadBand;
	return factvalue;
}

void utilFilterReset(utilFilter_t *f, float setpoint) {
    f->z1 = setpoint;
}

void utilFilterReset2(utilFilter_t *f, float setpoint){
    utilFilterReset(&f[0], setpoint);
    utilFilterReset(&f[1], setpoint);		
}

void utilFilterReset3(utilFilter_t *f, float setpoint) {
    utilFilterReset(&f[0], setpoint);
    utilFilterReset(&f[1], setpoint);
    utilFilterReset(&f[2], setpoint);
}

void utilFilterInit(utilFilter_t *f, float dt, float tau, float setpoint) {
    f->tc = dt / tau;			//tau=0.1 ==> f->tc= 0.05		tau=0.125 ==> f->tc= 0.04	
    utilFilterReset(f, setpoint);
}

void utilFilterInit2(utilFilter_t *f, float dt, float tau, float setpoint) {
    utilFilterInit(&f[0], dt, tau, setpoint);
    utilFilterInit(&f[1], dt, tau, setpoint);
}

void utilFilterInit3(utilFilter_t *f, float dt, float tau, float setpoint) {
    utilFilterInit(&f[0], dt, tau, setpoint);
    utilFilterInit(&f[1], dt, tau, setpoint);
    utilFilterInit(&f[2], dt, tau, setpoint);
}
/*--------- 作用：一节平滑滤波，跟低通类似 ---------*/
float utilFilter(utilFilter_t *f, float signal) {
    register float z1;
		//表达式可翻译为 out = out_last + (in - out_last)* (0.05 || 0.04)
    z1 = f->z1 + (signal - f->z1) * f->tc;			

    f->z1 = z1;
    return z1;
}

/*--------- 作用：进行二阶平滑滤波 ---------*/
float utilFilter2(utilFilter_t *f, float signal) {
    return utilFilter(&f[0], utilFilter(&f[1],signal));
}


/*--------- 作用：进行三阶平滑滤波 ---------*/
float utilFilter3(utilFilter_t *f, float signal) {
    return utilFilter(&f[0], utilFilter(&f[1], utilFilter(&f[2], signal)));
}

float utilFirFilter(utilFirFilter_t *f, float newValue) {
    float result = 0.0f;
    int i;

    f->data[f->i] = newValue;
    f->i = (f->i + 1) % f->n;

    for (i = 0; i < f->n; i++)
        result += f->window[i] * f->data[(f->i + i) % f->n];

    return result;
}

void utilFirFilterInit(utilFirFilter_t *f, const float *window, float *buffer, uint8_t n) {
    int i;

    f->window = window;
    f->data = buffer;
    f->n = n;
    f->i = 0;

    for (i = 0; i < n; i++)
        f->data[i] = 0.0f;
}

void delay_ms(u16 nms)
{
	int i;
	for( i=0;i<nms;i++)
	{
		int a=72000; //at 72MHz 72000 is ok
		while(a--);
	}
}

void delay_us(u32 nus)
{
	int i;
	for( i=0;i<nus;i++)
	{
		int a=72;  //at 72MHz 72 is ok,the higher the number the more timing precise
		while(a--);
	}
}
