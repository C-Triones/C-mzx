#include "driver.h"
#include "oled_font.h"
#include "oled_bmp.h"

#define IIC_OLED 1
#define SPI_OLED 0

#define OLED_MODE SPI_OLED

#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  

void OLED_Delay(unsigned int t){
	unsigned int i;
	unsigned char a;
	for( i=0;i<t;i++){
		for (a = 0; a < 6; a++);
	}
}
//-----------------OLED IIC�˿ڶ���----------------  					   
#if OLED_MODE

#define RCC_OLED             RCC_APB2Periph_GPIOD

#define GPIO_PORT_OLED_IIC_SDA   GPIOD
#define GPIO_PIN_OLED_IIC_SDA	   GPIO_Pin_6
#define GPIO_PORT_OLED_IIC_SCL   GPIOD
#define GPIO_PIN_OLED_IIC_SCL	   GPIO_Pin_7

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIO_PORT_OLED_IIC_SDA,GPIO_PIN_OLED_IIC_SDA)//SDA IIC�ӿڵ�ʱ���ź�
#define OLED_SCLK_Set() GPIO_SetBits(GPIO_PORT_OLED_IIC_SDA,GPIO_PIN_OLED_IIC_SDA)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIO_PORT_OLED_IIC_SCL,GPIO_PIN_OLED_IIC_SCL)//SCL IIC�ӿڵ������ź�
#define OLED_SDIN_Set() GPIO_SetBits(GPIO_PORT_OLED_IIC_SCL,GPIO_PIN_OLED_IIC_SCL)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	OLED_SCLK_Set();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

void IIC_Wait_Ack()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80){
			OLED_SDIN_Set();
		}
		else OLED_SDIN_Clr();
		da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
	IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	IIC_Stop();
}
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd){
		Write_IIC_Data(dat);
	}
	else {
		Write_IIC_Command(dat);
	}
}
#else
//-----------------OLED SPI�˿ڶ���----------------  					   
#define RCC_OLED             RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC 
 
#define GPIO_PORT_OLED_SPI_CLK   GPIOD
#define GPIO_PIN_OLED_SPI_CLK 	 GPIO_Pin_11

#define GPIO_PORT_OLED_SPI_DIN   GPIOD
#define GPIO_PIN_OLED_SPI_DIN	   GPIO_Pin_10

#define GPIO_PORT_OLED_SPI_RES   GPIOC
#define GPIO_PIN_OLED_SPI_RES	   GPIO_Pin_11

#define GPIO_PORT_OLED_SPI_DC    GPIOC
#define GPIO_PIN_OLED_SPI_DC	   GPIO_Pin_10




#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define OLED_RST_Clr() GPIO_ResetBits(GPIO_PORT_OLED_SPI_RES,GPIO_PIN_OLED_SPI_RES)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIO_PORT_OLED_SPI_RES,GPIO_PIN_OLED_SPI_RES)

#define OLED_DC_Clr() GPIO_ResetBits(GPIO_PORT_OLED_SPI_DC,GPIO_PIN_OLED_SPI_DC)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIO_PORT_OLED_SPI_DC,GPIO_PIN_OLED_SPI_DC)

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIO_PORT_OLED_SPI_CLK,GPIO_PIN_OLED_SPI_CLK)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIO_PORT_OLED_SPI_CLK,GPIO_PIN_OLED_SPI_CLK)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIO_PORT_OLED_SPI_DIN,GPIO_PIN_OLED_SPI_DIN)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIO_PORT_OLED_SPI_DIN,GPIO_PIN_OLED_SPI_DIN)
 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();
		
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_DC_Set();   	  
}
#endif

/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}

//��������
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}
void OLED_On(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n����
u32 oled_pow(uint8_t m,uint8_t n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//��ʾ����
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//��ʼ��SSD1306					    
void driver_InitOLED(void)
{ 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
	
	
 #if OLED_MODE 
	 RCC_APB2PeriphClockCmd(RCC_OLED, ENABLE);	 //ʹ��PC,D,G�˿�ʱ��
 #else
	 RCC_APB2PeriphClockCmd(RCC_OLED, ENABLE);	 //ʹ��PC,D,G�˿�ʱ��
 #endif
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	
 #if OLED_MODE
 
 	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_IIC_SDA;
	GPIO_Init(GPIO_PORT_OLED_IIC_SDA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_IIC_SCL;
	GPIO_Init(GPIO_PORT_OLED_IIC_SCL, &GPIO_InitStructure);
	
 	GPIO_SetBits(GPIO_PORT_OLED_IIC_SDA,GPIO_PIN_OLED_IIC_SDA);						 //PG13,14,15 OUT  �����
  GPIO_SetBits(GPIO_PORT_OLED_IIC_SCL,GPIO_PIN_OLED_IIC_SCL);						 //PG13,14,15 OUT  �����
	
	#else
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_SPI_RES;
	GPIO_Init(GPIO_PORT_OLED_SPI_RES, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_SPI_DC;
	GPIO_Init(GPIO_PORT_OLED_SPI_DC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_SPI_CLK;
	GPIO_Init(GPIO_PORT_OLED_SPI_CLK, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_SPI_DIN;
	GPIO_Init(GPIO_PORT_OLED_SPI_DIN, &GPIO_InitStructure);
	
 	GPIO_SetBits(GPIO_PORT_OLED_SPI_RES,GPIO_PIN_OLED_SPI_RES);						 //PG13,14,15 OUT  �����
	GPIO_SetBits(GPIO_PORT_OLED_SPI_DC,GPIO_PIN_OLED_SPI_DC);						 //PG13,14,15 OUT  �����
	GPIO_SetBits(GPIO_PORT_OLED_SPI_CLK,GPIO_PIN_OLED_SPI_CLK);						 //PG13,14,15 OUT  �����
	GPIO_SetBits(GPIO_PORT_OLED_SPI_DIN,GPIO_PIN_OLED_SPI_DIN);						 //PG13,14,15 OUT  �����

	#endif
  OLED_RST_Set();
	OLED_Delay(10000);
	OLED_RST_Clr();
	OLED_Delay(10000);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
		OLED_WR_Byte(0x81,OLED_CMD); //�Աȶ�����
	OLED_WR_Byte(0xfF,OLED_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0);
}

