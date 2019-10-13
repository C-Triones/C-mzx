#ifndef __APP_FINDFIRE_H
#define __APP_FINDFIRE_H

typedef enum{
	ADC_STACK_SIZE = 512,
	ADC_PRIORITY = 3,
}appADC_e;

typedef enum{
	L_ADC = 0,
	R_ADC,
}adcDevice_e;

typedef struct{
	float adcData[2];
}adcTestStruct_t;

extern adcTestStruct_t adcTestData;

void appfindFire_Init(void);
void appfindFireUpdata(void);


#endif
