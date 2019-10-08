#ifndef __DRIVER_LINEAR_MOVEMENT_H
#define __DRIVER_LINEAR_MOVEMENT_H

#include "bsp.h"
#include "util.h"

#define SAMP_COUNT	20		/* 样本个数，表示200ms内的采样数据求平均值 */
#define SENSOR_LENGTH 500
#define SENSOR_SCALE 1.0f/4096*SENSOR_LENGTH

#define  ADC1_USEGPIO BSP_GPIOC0
#define  ADC2_USEGPIO BSP_GPIOC1
#define  ADC3_USEGPIO BSP_GPIOC2
#define  ADC4_USEGPIO BSP_GPIOC3


#define ADC_1             0
#define ADC_2             1
#define ADC_3             2
#define ADC_4             3

#define SPEED_1             0
#define SPEED_2             1
#define SPEED_3             2
#define SPEED_4             3

typedef struct adcFilterData
{
    float   gx1;
    float   gx2;
    float   gx3;
    float   previousInput;
    float   previousOutput;
}adcFilterData_t;

extern __IO uint16_t adc_raw_value[10][4]; //采集的ADC值
extern __IO float average_dis[4];  //距离平均值
void ADC_Configuration(void);
void AdcPro(void);
uint16_t GetADC(void);
void getadc_average(__IO float *real);
void adcLowPassFilter(formatTrans32Struct_t *distence, formatTrans32Struct_t *speed);
void adcLowPassFilterInit(void);
float adcFilter(float input, struct adcFilterData *filterParameters);



#endif

