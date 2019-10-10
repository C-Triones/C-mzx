#include "BSP_Flash.h"
#include "string.h"
/******************************外部调用函数************************************/
void BSP_FLASH_Write(u32 WriteAddr, u32 *pBuffer, u32 ByteToWrite);			//从指定地址开始写入指定长度的数据
void BSP_FLASH_Read(u32 ReadAddr,  u32 *pBuffer, u32 NumToRead);		//从指定地址开始读出指定长度的数据
/*****************************************************************************/

/*
***************************************************
函数名：BSP_FLASH_ReadByte
功能：从flash中读取一个字节
入口参数：	faddr：flash地址
返回值：读取到的字节
应用范围：内部调用
备注：
***************************************************
*/
static u32 BSP_FLASH_ReadByte(u32 faddr){
	return *(vu32*)faddr; 
}

/*
***************************************************
函数名：BSP_FLASH_GetFlashSector
功能：获取指定地址所在flash的块首地址
入口参数：	addr：Flash地址
返回值：所在页首地址
应用范围：外部调用
备注：最高可支持1Mflash的STM32芯片
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
函数名：BSP_FLASH_Write
功能：从指定地址开始写入指定长度的数据
入口参数：	WriteAddr：起始地址
					pBuffer：要写入数据存储的首地址
					ByteToWrite：要写入的字节数，注意是字节数，如果写入字，需要用字数乘以4
返回值：	0：写入失败     
				1：写入成功
应用范围：外部调用
备注：因为STM32F4的扇区实在太大，没办法本地保存扇区数据,所以本函数
			写地址如果非0XFF，那么会先擦除整个扇区且不保存扇区数据。所以
			写非0XFF的地址，将导致整个扇区数据丢失。建议写之前确保扇区里
			没有重要数据，最好是整个扇区先擦除了，然后慢慢往后写。

			本函数对OTP区域也有效！可以用来写OTP区！
			OTP区域地址范围：0X1FFF7800~0X1FFF7A0F
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
    
    if(WriteAddr<STM32_FLASH_BASE) return 0;	//非法地址
		FLASH_Unlock();								//解锁 
    FLASH_DataCacheCmd(DISABLE);	//FLASH擦除期间,必须禁止数据缓存
 		
		addrx=WriteAddr;				//写入的起始地址
		endaddr=WriteAddr+ByteToWrite;	//写入的结束地址
    
    start_sector = BSP_FLASH_GetFlashSector(addrx);
    end_sector = BSP_FLASH_GetFlashSector(endaddr);
    
		if(addrx<0X1FFF0000)			//只有主存储区,才需要执行擦除操作!!
		{             
				 for(i = start_sector; i <= end_sector; i += 8)
				 {
						 status = FLASH_EraseSector(i, VoltageRange_3);
						 if(status!=FLASH_COMPLETE)
						 {
								 res = 0;	//发生错误了
								 break;
						 }           
				 }           
		}
			
		if(status == FLASH_COMPLETE)
		{
			while(WriteAddr < endaddr)//写数据
			{
				if(FLASH_ProgramByte(WriteAddr,*pBuffer) != FLASH_COMPLETE)//写入数据
				{ 
					res = 0;	//写入异常
					break;
				}
				WriteAddr+=1;
				pBuffer = (u32*)pBuffer+1;
			} 
		}
   
    FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
    FLASH_Lock();//上锁
    return res;
}*/
void BSP_FLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//非法地址
	FLASH_Unlock();									//解锁 
  FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间,必须禁止数据缓存
 		
	addrx=WriteAddr;					//写入的起始地址
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
	if(addrx<0X1FFF0000){			//只有主存储区,才需要执行擦除操作!!
		while(addrx<endaddr){		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
			if(BSP_FLASH_ReadByte(addrx) != 0XFFFFFFFF){   //有非0XFFFFFFFF的地方,要擦除这个扇区
				status=FLASH_EraseSector(BSP_FLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V之间!!
				if(status!=FLASH_COMPLETE)
					break;	//发生错误了
			}
			else 
				addrx+=4;
		} 
	}
	if(status==FLASH_COMPLETE){
		while(WriteAddr<endaddr){
			//写入数据
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE){ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
	FLASH_Lock();//上锁
} 
/*
***************************************************
函数名：BSP_FLASH_Read
功能：从指定地址开始读出指定长度的数据
入口参数：	WriteAddr：起始地址
					pBuffer：要写入数据存储的首地址
					ByteToWrite：要写入的字节数，注意是字节数，如果写入字，需要用字数乘以4
返回值：	0：写入失败     
				1：写入成功
应用范围：外部调用
备注：因为STM32F4的扇区实在太大，没办法本地保存扇区数据,所以本函数
			写地址如果非0XFF，那么会先擦除整个扇区且不保存扇区数据。所以
			写非0XFF的地址，将导致整个扇区数据丢失。建议写之前确保扇区里
			没有重要数据，最好是整个扇区先擦除了，然后慢慢往后写。

			本函数对OTP区域也有效！可以用来写OTP区！
			OTP区域地址范围：0X1FFF7800~0X1FFF7A0F
***************************************************
*/
void BSP_FLASH_Read(u32 ReadAddr, u32 *pBuffer, u32 ByteToRead){
	u32 i;
//    u32 NumToRead = ((ByteToRead+3u)&(~3u))/4u;
	for(i=0;i<ByteToRead;i++){
		pBuffer[i]=BSP_FLASH_ReadByte(ReadAddr);//读取1个字节.
		ReadAddr+=1;//偏移1个字节.	
	}
}
