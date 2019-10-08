#include "driver.h"

uint8_t aversion = 1;
uint8_t a = 0;
uint8_t b = 0;
void driver_FlashWrite(uint8_t name,uint8_t value)
{
	aversion = 8;
	bsp_WriteCpuFlash(FLASH_SAVE_START_ADDR,(uint8_t *)&aversion, 2);
	bsp_WriteCpuFlash(FLASH_SAVE_START_ADDR+(name*2),(uint8_t *)&value, 2);
	bsp_ReadCpuFlash(FLASH_SAVE_START_ADDR,(uint8_t *)&a, 2);
	bsp_ReadCpuFlash(FLASH_SAVE_START_ADDR+(name*2),(uint8_t *)&b, 2);
}

void driver_FlashRead(uint8_t name,uint8_t value)
{	
	bsp_ReadCpuFlash(FLASH_SAVE_START_ADDR+(name*2),(uint8_t *)&value, 2);
}


