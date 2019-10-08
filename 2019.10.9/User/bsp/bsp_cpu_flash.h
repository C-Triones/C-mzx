/*
*********************************************************************************************************
*
*	ģ������ : cpu�ڲ�falsh����ģ��
*	�ļ����� : bsp_cpu_flash.h
*	��    �� : V1.0
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _BSP_CPU_FLASH_H_
#define _BSP_CPU_FLASH_H_

#define FLASH_BASE_ADDR	0x08000000			/* Flash����ַ */
#define	FLASH_SIZE		(256*1024)		/* Flash ���� */

/* ����F103��  512K FLASH , ÿ��PAGE = 2K �ֽڣ��ܹ� 256�� PAGE  */
#define SECTOR_MASK			0xFFFFF800

#define FLASH_IS_EQU		0   /* Flash���ݺʹ�д���������ȣ�����Ҫ������д���� */
#define FLASH_REQ_WRITE		1	/* Flash����Ҫ������ֱ��д */
#define FLASH_REQ_ERASE 		2	/* Flash��Ҫ�Ȳ���,��д */
#define FLASH_PARAM_ERR		3	/* ������������ */

#define FLASH_SAVE_START_ADDR		  0x08033000  //(0x08000000 + 0x20000 - 0x800)

uint8_t bsp_ReadCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize);
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize);
uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize);

#endif


/***************************** ���������� www.armfly.com (END OF FILE) *********************************/

