#include "BSP_Flash.h"
#include "string.h"
/******************************�ⲿ���ú���************************************/
void BSP_FLASH_Write(u32 WriteAddr, u32 *pBuffer, u32 ByteToWrite);			//��ָ����ַ��ʼд��ָ�����ȵ�����
void BSP_FLASH_Read(u32 ReadAddr,  u32 *pBuffer, u32 NumToRead);		//��ָ����ַ��ʼ����ָ�����ȵ�����
/*****************************************************************************/

/*
***************************************************
��������BSP_FLASH_ReadByte
���ܣ���flash�ж�ȡһ���ֽ�
��ڲ�����	faddr��flash��ַ
����ֵ����ȡ�����ֽ�
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
static u32 BSP_FLASH_ReadByte(u32 faddr){
	return *(vu32*)faddr; 
}

/*
***************************************************
��������BSP_FLASH_GetFlashSector
���ܣ���ȡָ����ַ����flash�Ŀ��׵�ַ
��ڲ�����	addr��Flash��ַ
����ֵ������ҳ�׵�ַ
Ӧ�÷�Χ���ⲿ����
��ע����߿�֧��1Mflash��STM32оƬ
***************************************************
*/
uint16_t BSP_FLASH_GetFlashSector(u32 addr){
	if(addr < ADDR_FLASH_SECTOR_1)				
		return FLASH_Sector_0;
	else if(addr < ADDR_FLASH_SECTOR_2)		
		return FLASH_Sector_1;
	else if(addr < ADDR_FLASH_SECTOR_3)		
		return FLASH_Sector_2;
	else if(addr < ADDR_FLASH_SECTOR_4)		
		return FLASH_Sector_3;
	else if(addr < ADDR_FLASH_SECTOR_5)		
		return FLASH_Sector_4;
	else if(addr < ADDR_FLASH_SECTOR_6)		
		return FLASH_Sector_5;
	else if(addr < ADDR_FLASH_SECTOR_7)		
		return FLASH_Sector_6;
	else if(addr < ADDR_FLASH_SECTOR_8)		
		return FLASH_Sector_7;
	else if(addr < ADDR_FLASH_SECTOR_9)		
		return FLASH_Sector_8;
	else if(addr < ADDR_FLASH_SECTOR_10)	
		return FLASH_Sector_9;
	else if(addr < ADDR_FLASH_SECTOR_11)	
		return FLASH_Sector_10; 
	return FLASH_Sector_11;	
}

/*
***************************************************
��������BSP_FLASH_Write
���ܣ���ָ����ַ��ʼд��ָ�����ȵ�����
��ڲ�����	WriteAddr����ʼ��ַ
					pBuffer��Ҫд�����ݴ洢���׵�ַ
					ByteToWrite��Ҫд����ֽ�����ע�����ֽ��������д���֣���Ҫ����������4
����ֵ��	0��д��ʧ��     
				1��д��ɹ�
Ӧ�÷�Χ���ⲿ����
��ע����ΪSTM32F4������ʵ��̫��û�취���ر�����������,���Ա�����
			д��ַ�����0XFF����ô���Ȳ������������Ҳ������������ݡ�����
			д��0XFF�ĵ�ַ�������������������ݶ�ʧ������д֮ǰȷ��������
			û����Ҫ���ݣ���������������Ȳ����ˣ�Ȼ����������д��

			��������OTP����Ҳ��Ч����������дOTP����
			OTP�����ַ��Χ��0X1FFF7800~0X1FFF7A0F
***************************************************
*/
/*u32 BSP_FLASH_Write(u32 WriteAddr, u32 *pBuffer, u32 ByteToWrite)	
{ 
    FLASH_Status status = FLASH_COMPLETE;
    u8 res=1;
    u32 addrx=0;
    u32 endaddr=0;	
		int i = 0;
    
    u32 start_sector = 0;
    u32 end_sector = 0;
    
    if(WriteAddr<STM32_FLASH_BASE) return 0;	//�Ƿ���ַ
		FLASH_Unlock();								//���� 
    FLASH_DataCacheCmd(DISABLE);	//FLASH�����ڼ�,�����ֹ���ݻ���
 		
		addrx=WriteAddr;				//д�����ʼ��ַ
		endaddr=WriteAddr+ByteToWrite;	//д��Ľ�����ַ
    
    start_sector = BSP_FLASH_GetFlashSector(addrx);
    end_sector = BSP_FLASH_GetFlashSector(endaddr);
    
		if(addrx<0X1FFF0000)			//ֻ�����洢��,����Ҫִ�в�������!!
		{             
				 for(i = start_sector; i <= end_sector; i += 8)
				 {
						 status = FLASH_EraseSector(i, VoltageRange_3);
						 if(status!=FLASH_COMPLETE)
						 {
								 res = 0;	//����������
								 break;
						 }           
				 }           
		}
			
		if(status == FLASH_COMPLETE)
		{
			while(WriteAddr < endaddr)//д����
			{
				if(FLASH_ProgramByte(WriteAddr,*pBuffer) != FLASH_COMPLETE)//д������
				{ 
					res = 0;	//д���쳣
					break;
				}
				WriteAddr+=1;
				pBuffer = (u32*)pBuffer+1;
			} 
		}
   
    FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���
    FLASH_Lock();//����
    return res;
}*/
void BSP_FLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//�Ƿ���ַ
	FLASH_Unlock();									//���� 
  FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���
 		
	addrx=WriteAddr;					//д�����ʼ��ַ
	endaddr=WriteAddr+NumToWrite*4;	//д��Ľ�����ַ
	if(addrx<0X1FFF0000){			//ֻ�����洢��,����Ҫִ�в�������!!
		while(addrx<endaddr){		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
			if(BSP_FLASH_ReadByte(addrx) != 0XFFFFFFFF){   //�з�0XFFFFFFFF�ĵط�,Ҫ�����������
				status=FLASH_EraseSector(BSP_FLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V֮��!!
				if(status!=FLASH_COMPLETE)
					break;	//����������
			}
			else 
				addrx+=4;
		} 
	}
	if(status==FLASH_COMPLETE){
		while(WriteAddr<endaddr){
			//д������
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE){ 
				break;	//д���쳣
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���
	FLASH_Lock();//����
} 
/*
***************************************************
��������BSP_FLASH_Read
���ܣ���ָ����ַ��ʼ����ָ�����ȵ�����
��ڲ�����	WriteAddr����ʼ��ַ
					pBuffer��Ҫд�����ݴ洢���׵�ַ
					ByteToWrite��Ҫд����ֽ�����ע�����ֽ��������д���֣���Ҫ����������4
����ֵ��	0��д��ʧ��     
				1��д��ɹ�
Ӧ�÷�Χ���ⲿ����
��ע����ΪSTM32F4������ʵ��̫��û�취���ر�����������,���Ա�����
			д��ַ�����0XFF����ô���Ȳ������������Ҳ������������ݡ�����
			д��0XFF�ĵ�ַ�������������������ݶ�ʧ������д֮ǰȷ��������
			û����Ҫ���ݣ���������������Ȳ����ˣ�Ȼ����������д��

			��������OTP����Ҳ��Ч����������дOTP����
			OTP�����ַ��Χ��0X1FFF7800~0X1FFF7A0F
***************************************************
*/
void BSP_FLASH_Read(u32 ReadAddr, u32 *pBuffer, u32 ByteToRead){
	u32 i;
//    u32 NumToRead = ((ByteToRead+3u)&(~3u))/4u;
	for(i=0;i<ByteToRead;i++){
		pBuffer[i]=BSP_FLASH_ReadByte(ReadAddr);//��ȡ1���ֽ�.
		ReadAddr+=1;//ƫ��1���ֽ�.	
	}
}
