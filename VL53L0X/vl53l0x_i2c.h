#ifndef __VL53L0X_I2C_H
#define __VL53L0X_I2C_H
#include "BSP_GPIO.h"
//IO方向设置
#define VL_SDA_IN()  {GPIOB->MODER&=~(3<<(14*2));GPIOB->MODER|=0<<14*2;}	//PB10输入模式
#define VL_SDA_OUT() {GPIOB->MODER&=~(3<<(14*2));GPIOB->MODER|=1<<14*2;}    //PB10输出模式


//IO操作函数	 
#define VL_IIC_SCL    PBout(15) 		//SCL
#define VL_IIC_SDA    PBout(14) 		//SDA	 
#define VL_READ_SDA   PBin(14) 		    //输入SDA 

//状态
#define STATUS_OK       0x00
#define STATUS_FAIL     0x01

//IIC操作函数

void VL53L0X_i2c_init(void);
u8 VL53L0X_write_byte(u8 address,u8 index,u8 data);              //IIC写一个8位数据
u8 VL53L0X_write_word(u8 address,u8 index,u16 data);             //IIC写一个16位数据
u8 VL53L0X_write_dword(u8 address,u8 index,u32 data);            //IIC写一个32位数据
u8 VL53L0X_write_multi(u8 address, u8 index,u8 *pdata,u16 count);//IIC连续写

u8 VL53L0X_read_byte(u8 address,u8 index,u8 *pdata);             //IIC读一个8位数据
u8 VL53L0X_read_word(u8 address,u8 index,u16 *pdata);            //IIC读一个16位数据
u8 VL53L0X_read_dword(u8 address,u8 index,u32 *pdata);           //IIC读一个32位数据
u8 VL53L0X_read_multi(u8 address,u8 index,u8 *pdata,u16 count);  //IIC连续读

#endif
