#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f4xx.h"

typedef const struct
{
	GPIO_TypeDef *GPIOx;	//GPIO号
	uint32_t Pin;					//对应针脚
}BSP_GPIOSource_TypeDef;

typedef enum
{ 
	GPIO_Mode_IN_FLOATING = 0x000000,	//浮空输入
	GPIO_Mode_IPU 				=	0x000001,	//上拉输入
	GPIO_Mode_IPD 				= 0x000002,	//下拉输入
	GPIO_Mode_Out_PP 			= 0x010001,	//推挽输出
	GPIO_Mode_Out_OD 			= 0x010101,	//开漏输出		
	GPIO_Mode_AF_PP 			= 0x020001,	//复用推挽
	GPIO_Mode_AF_OD 			= 0x020101,	//复用开漏
	GPIO_Mode_Ain 				= 0x030000	//模拟输入
}BSP_GPIOMode_TypeDef;

uint8_t GPIO_Pin_TO_GPIO_PinSource(BSP_GPIOSource_TypeDef* BSP_GPIO);

void GPIO_Pin_TO_PinAFConfig(BSP_GPIOSource_TypeDef* BSP_GPIO,uint8_t GPIO_AF);

void BSP_GPIO_Init(BSP_GPIOSource_TypeDef* BSP_GPIO,BSP_GPIOMode_TypeDef GPIO_Mode);

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

/*******************************GPIO指针定义*********************************/

/************GPIOA引脚定义************/
#define BSP_GPIOA0  (&BSP_GPIOA0_Base)
#define BSP_GPIOA1  (&BSP_GPIOA1_Base)
#define BSP_GPIOA2  (&BSP_GPIOA2_Base)
#define BSP_GPIOA3  (&BSP_GPIOA3_Base)
#define BSP_GPIOA4  (&BSP_GPIOA4_Base)
#define BSP_GPIOA5  (&BSP_GPIOA5_Base)
#define BSP_GPIOA6  (&BSP_GPIOA6_Base)
#define BSP_GPIOA7  (&BSP_GPIOA7_Base)
#define BSP_GPIOA8  (&BSP_GPIOA8_Base)
#define BSP_GPIOA9  (&BSP_GPIOA9_Base)
#define BSP_GPIOA10 (&BSP_GPIOA10_Base)
#define BSP_GPIOA11 (&BSP_GPIOA11_Base)
#define BSP_GPIOA12 (&BSP_GPIOA12_Base)
#define BSP_GPIOA13 (&BSP_GPIOA13_Base)
#define BSP_GPIOA14 (&BSP_GPIOA14_Base)
#define BSP_GPIOA15 (&BSP_GPIOA15_Base)

/************GPIOB引脚定义************/
#define BSP_GPIOB0  (&BSP_GPIOB0_Base)
#define BSP_GPIOB1  (&BSP_GPIOB1_Base)
#define BSP_GPIOB2  (&BSP_GPIOB2_Base)
#define BSP_GPIOB3  (&BSP_GPIOB3_Base)
#define BSP_GPIOB4  (&BSP_GPIOB4_Base)
#define BSP_GPIOB5  (&BSP_GPIOB5_Base)
#define BSP_GPIOB6  (&BSP_GPIOB6_Base)
#define BSP_GPIOB7  (&BSP_GPIOB7_Base)
#define BSP_GPIOB8  (&BSP_GPIOB8_Base)
#define BSP_GPIOB9  (&BSP_GPIOB9_Base)
#define BSP_GPIOB10 (&BSP_GPIOB10_Base)
#define BSP_GPIOB11 (&BSP_GPIOB11_Base)
#define BSP_GPIOB12 (&BSP_GPIOB12_Base)
#define BSP_GPIOB13 (&BSP_GPIOB13_Base)
#define BSP_GPIOB14 (&BSP_GPIOB14_Base)
#define BSP_GPIOB15 (&BSP_GPIOB15_Base)

/************GPIOC引脚定义************/
#define BSP_GPIOC0  (&BSP_GPIOC0_Base)
#define BSP_GPIOC1  (&BSP_GPIOC1_Base)
#define BSP_GPIOC2  (&BSP_GPIOC2_Base)
#define BSP_GPIOC3  (&BSP_GPIOC3_Base)
#define BSP_GPIOC4  (&BSP_GPIOC4_Base)
#define BSP_GPIOC5  (&BSP_GPIOC5_Base)
#define BSP_GPIOC6  (&BSP_GPIOC6_Base)
#define BSP_GPIOC7  (&BSP_GPIOC7_Base)
#define BSP_GPIOC8  (&BSP_GPIOC8_Base)
#define BSP_GPIOC9  (&BSP_GPIOC9_Base)
#define BSP_GPIOC10 (&BSP_GPIOC10_Base)
#define BSP_GPIOC11 (&BSP_GPIOC11_Base)
#define BSP_GPIOC12 (&BSP_GPIOC12_Base)
#define BSP_GPIOC13 (&BSP_GPIOC13_Base)
#define BSP_GPIOC14 (&BSP_GPIOC14_Base)
#define BSP_GPIOC15 (&BSP_GPIOC15_Base)

/************GPIOD引脚定义************/
#define BSP_GPIOD0  (&BSP_GPIOD0_Base)
#define BSP_GPIOD1  (&BSP_GPIOD1_Base)
#define BSP_GPIOD2  (&BSP_GPIOD2_Base)
#define BSP_GPIOD3  (&BSP_GPIOD3_Base)
#define BSP_GPIOD4  (&BSP_GPIOD4_Base)
#define BSP_GPIOD5  (&BSP_GPIOD5_Base)
#define BSP_GPIOD6  (&BSP_GPIOD6_Base)
#define BSP_GPIOD7  (&BSP_GPIOD7_Base)
#define BSP_GPIOD8  (&BSP_GPIOD8_Base)
#define BSP_GPIOD9  (&BSP_GPIOD9_Base)
#define BSP_GPIOD10 (&BSP_GPIOD10_Base)
#define BSP_GPIOD11 (&BSP_GPIOD11_Base)
#define BSP_GPIOD12 (&BSP_GPIOD12_Base)
#define BSP_GPIOD13 (&BSP_GPIOD13_Base)
#define BSP_GPIOD14 (&BSP_GPIOD14_Base)
#define BSP_GPIOD15 (&BSP_GPIOD15_Base)

/************GPIOE引脚定义************/
#define BSP_GPIOE0  (&BSP_GPIOE0_Base)
#define BSP_GPIOE1  (&BSP_GPIOE1_Base)
#define BSP_GPIOE2  (&BSP_GPIOE2_Base)
#define BSP_GPIOE3  (&BSP_GPIOE3_Base)
#define BSP_GPIOE4  (&BSP_GPIOE4_Base)
#define BSP_GPIOE5  (&BSP_GPIOE5_Base)
#define BSP_GPIOE6  (&BSP_GPIOE6_Base)
#define BSP_GPIOE7  (&BSP_GPIOE7_Base)
#define BSP_GPIOE8  (&BSP_GPIOE8_Base)
#define BSP_GPIOE9  (&BSP_GPIOE9_Base)
#define BSP_GPIOE10 (&BSP_GPIOE10_Base)
#define BSP_GPIOE11 (&BSP_GPIOE11_Base)
#define BSP_GPIOE12 (&BSP_GPIOE12_Base)
#define BSP_GPIOE13 (&BSP_GPIOE13_Base)
#define BSP_GPIOE14 (&BSP_GPIOE14_Base)
#define BSP_GPIOE15 (&BSP_GPIOE15_Base)

/************GPIOF引脚定义************/
#define BSP_GPIOF0  (&BSP_GPIOF0_Base)
#define BSP_GPIOF1  (&BSP_GPIOF1_Base)
#define BSP_GPIOF2  (&BSP_GPIOF2_Base)
#define BSP_GPIOF3  (&BSP_GPIOF3_Base)
#define BSP_GPIOF4  (&BSP_GPIOF4_Base)
#define BSP_GPIOF5  (&BSP_GPIOF5_Base)
#define BSP_GPIOF6  (&BSP_GPIOF6_Base)
#define BSP_GPIOF7  (&BSP_GPIOF7_Base)
#define BSP_GPIOF8  (&BSP_GPIOF8_Base)
#define BSP_GPIOF9  (&BSP_GPIOF9_Base)
#define BSP_GPIOF10 (&BSP_GPIOF10_Base)
#define BSP_GPIOF11 (&BSP_GPIOF11_Base)
#define BSP_GPIOF12 (&BSP_GPIOF12_Base)
#define BSP_GPIOF13 (&BSP_GPIOF13_Base)
#define BSP_GPIOF14 (&BSP_GPIOF14_Base)
#define BSP_GPIOF15 (&BSP_GPIOF15_Base)

/************GPIOG引脚定义************/
#define BSP_GPIOG0  (&BSP_GPIOG0_Base)
#define BSP_GPIOG1  (&BSP_GPIOG1_Base)
#define BSP_GPIOG2  (&BSP_GPIOG2_Base)
#define BSP_GPIOG3  (&BSP_GPIOG3_Base)
#define BSP_GPIOG4  (&BSP_GPIOG4_Base)
#define BSP_GPIOG5  (&BSP_GPIOG5_Base)
#define BSP_GPIOG6  (&BSP_GPIOG6_Base)
#define BSP_GPIOG7  (&BSP_GPIOG7_Base)
#define BSP_GPIOG8  (&BSP_GPIOG8_Base)
#define BSP_GPIOG9  (&BSP_GPIOG9_Base)
#define BSP_GPIOG10 (&BSP_GPIOG10_Base)
#define BSP_GPIOG11 (&BSP_GPIOG11_Base)
#define BSP_GPIOG12 (&BSP_GPIOG12_Base)
#define BSP_GPIOG13 (&BSP_GPIOG13_Base)
#define BSP_GPIOG14 (&BSP_GPIOG14_Base)
#define BSP_GPIOG15 (&BSP_GPIOG15_Base)

/************GPIOH引脚定义************/
#define BSP_GPIOH0  (&BSP_GPIOH0_Base)
#define BSP_GPIOH1  (&BSP_GPIOH1_Base)
#define BSP_GPIOH2  (&BSP_GPIOH2_Base)
#define BSP_GPIOH3  (&BSP_GPIOH3_Base)
#define BSP_GPIOH4  (&BSP_GPIOH4_Base)
#define BSP_GPIOH5  (&BSP_GPIOH5_Base)
#define BSP_GPIOH6  (&BSP_GPIOH6_Base)
#define BSP_GPIOH7  (&BSP_GPIOH7_Base)
#define BSP_GPIOH8  (&BSP_GPIOH8_Base)
#define BSP_GPIOH9  (&BSP_GPIOH9_Base)
#define BSP_GPIOH10 (&BSP_GPIOH10_Base)
#define BSP_GPIOH11 (&BSP_GPIOH11_Base)
#define BSP_GPIOH12 (&BSP_GPIOH12_Base)
#define BSP_GPIOH13 (&BSP_GPIOH13_Base)
#define BSP_GPIOH14 (&BSP_GPIOH14_Base)
#define BSP_GPIOH15 (&BSP_GPIOH15_Base)

/************GPIOI引脚定义************/
#define BSP_GPIOI0  (&BSP_GPIOI0_Base)
#define BSP_GPIOI1  (&BSP_GPIOI1_Base)
#define BSP_GPIOI2  (&BSP_GPIOI2_Base)
#define BSP_GPIOI3  (&BSP_GPIOI3_Base)
#define BSP_GPIOI4  (&BSP_GPIOI4_Base)
#define BSP_GPIOI5  (&BSP_GPIOI5_Base)
#define BSP_GPIOI6  (&BSP_GPIOI6_Base)
#define BSP_GPIOI7  (&BSP_GPIOI7_Base)
#define BSP_GPIOI8  (&BSP_GPIOI8_Base)
#define BSP_GPIOI9  (&BSP_GPIOI9_Base)
#define BSP_GPIOI10 (&BSP_GPIOI10_Base)
#define BSP_GPIOI11 (&BSP_GPIOI11_Base)
#define BSP_GPIOI12 (&BSP_GPIOI12_Base)
#define BSP_GPIOI13 (&BSP_GPIOI13_Base)
#define BSP_GPIOI14 (&BSP_GPIOI14_Base)
#define BSP_GPIOI15 (&BSP_GPIOI15_Base)

/************GPIOJ引脚定义************/
#define BSP_GPIOJ0  (&BSP_GPIOJ0_Base)
#define BSP_GPIOJ1  (&BSP_GPIOJ1_Base)
#define BSP_GPIOJ2  (&BSP_GPIOJ2_Base)
#define BSP_GPIOJ3  (&BSP_GPIOJ3_Base)
#define BSP_GPIOJ4  (&BSP_GPIOJ4_Base)
#define BSP_GPIOJ5  (&BSP_GPIOJ5_Base)
#define BSP_GPIOJ6  (&BSP_GPIOJ6_Base)
#define BSP_GPIOJ7  (&BSP_GPIOJ7_Base)
#define BSP_GPIOJ8  (&BSP_GPIOJ8_Base)
#define BSP_GPIOJ9  (&BSP_GPIOJ9_Base)
#define BSP_GPIOJ10 (&BSP_GPIOJ10_Base)
#define BSP_GPIOJ11 (&BSP_GPIOJ11_Base)
#define BSP_GPIOJ12 (&BSP_GPIOJ12_Base)
#define BSP_GPIOJ13 (&BSP_GPIOJ13_Base)
#define BSP_GPIOJ14 (&BSP_GPIOJ14_Base)
#define BSP_GPIOJ15 (&BSP_GPIOJ15_Base)

/************GPIOK引脚定义************/
#define BSP_GPIOK0  (&BSP_GPIOK0_Base)
#define BSP_GPIOK1  (&BSP_GPIOK1_Base)
#define BSP_GPIOK2  (&BSP_GPIOK2_Base)
#define BSP_GPIOK3  (&BSP_GPIOK3_Base)
#define BSP_GPIOK4  (&BSP_GPIOK4_Base)
#define BSP_GPIOK5  (&BSP_GPIOK5_Base)
#define BSP_GPIOK6  (&BSP_GPIOK6_Base)
#define BSP_GPIOK7  (&BSP_GPIOK7_Base)
#define BSP_GPIOK8  (&BSP_GPIOK8_Base)
#define BSP_GPIOK9  (&BSP_GPIOK9_Base)
#define BSP_GPIOK10 (&BSP_GPIOK10_Base)
#define BSP_GPIOK11 (&BSP_GPIOK11_Base)
#define BSP_GPIOK12 (&BSP_GPIOK12_Base)
#define BSP_GPIOK13 (&BSP_GPIOK13_Base)
#define BSP_GPIOK14 (&BSP_GPIOK14_Base)
#define BSP_GPIOK15 (&BSP_GPIOK15_Base)

/*************GPIOA引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOA0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOA15_Base;

/*************GPIOB引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOB0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOB15_Base;

/*************GPIOC引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOC0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOC15_Base;

/*************GPIOD引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOD0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOD15_Base;

/*************GPIOE引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOE0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOE15_Base;

/*************GPIOF引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOF0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOF15_Base;

/*************GPIOG引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOG0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOG15_Base;

/*************GPIOH引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOH0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOH15_Base;

/*************GPIOI引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOI0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOI15_Base;

/*************GPIOJ引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOJ0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOJ15_Base;

/*************GPIOK引脚定义*************/
extern BSP_GPIOSource_TypeDef BSP_GPIOK0_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK1_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK2_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK3_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK4_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK5_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK6_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK7_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK8_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK9_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK10_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK11_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK12_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK13_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK14_Base;
extern BSP_GPIOSource_TypeDef BSP_GPIOK15_Base;

#endif
