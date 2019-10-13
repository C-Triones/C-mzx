#include "app.h"

void app_FlashWriteUdata(void)
{
	uint8_t i = 0;
	for(i = 0;i < NAME_OF_LIST;i++){
		bsp_WriteCpuFlash(FLASH_SAVE_START_ADDR + (i*2),(uint8_t *)&parameter[i], 2);
	}
}

void app_FlashReadUdata(void)
{
	uint8_t i = 0;
	for(i = 1;i < NAME_OF_LIST;i++){
		bsp_ReadCpuFlash(FLASH_SAVE_START_ADDR + (i*2),(uint8_t *)&parameter[i], 2);
	}
}
