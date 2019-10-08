#include "bsp.h"

/******************************外部调用函数************************************/
void BSP_IIC_SW_Init(void);	
unsigned char BSP_IIC_WriteData(u8 dev_addr,u8 regAddr,u8 data);
unsigned char BSP_IIC_ReadData(u8 dev_addr,u8 regAddr,u8 *buf,u8 length);
void BSP_IIC_Start(void);		//发送IIC开始信号
void BSP_IIC_Stop(void);		//发送IIC停止信号
void BSP_IIC_Send_Byte(u8 txd);		//IIC发送一个字节
u8 BSP_IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 BSP_IIC_Wait_Ack(void);	//IIC等待ACK信号
void BSP_IIC_Ack(void);			//IIC发送ACK信号
void BSP_IIC_NAck(void);		//IIC不发送ACK信号 
uint8_t BSP_IIC_CheckDevice(uint8_t Device_Address);//检查设备
/*****************************************************************************/

void IIC_SW_Delay(unsigned int t){
	unsigned int i;
	unsigned char a;
	for( i=0;i<t;i++){
		for (a = 0; a < 6; a++);
	}
}

/*
***************************************************
函数名：BSP_IIC_WriteData
功能：软件IIC写数据
入口参数：	dev_addr：器件地址
					regAddr：需写的寄存器地址
					data：需写的数据
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
unsigned char BSP_IIC_WriteData(u8 dev_addr,u8 regAddr,u8 data){
	BSP_IIC_Start();
	/*************发送器件地址***************/
	BSP_IIC_Send_Byte(dev_addr);
	if(BSP_IIC_Wait_Ack()){	//等待应答
		BSP_IIC_Stop();		 
		return 1;
	}
	/*************发送寄存器地址***************/
	BSP_IIC_Send_Byte(regAddr);
	if(BSP_IIC_Wait_Ack()){	//等待应答
		BSP_IIC_Stop();		 
		return 1;
	}
	/*************发送数据***************/
	BSP_IIC_Send_Byte(data);
	if(BSP_IIC_Wait_Ack()){	//等待应答
		BSP_IIC_Stop();		 
		return 1;
	}
	BSP_IIC_Stop();	
	return 0;
}

/*
***************************************************
函数名：BSP_IIC_ReadData
功能：软件IIC读数据
入口参数：	dev_addr：器件地址
					regAddr：需读的寄存器地址
					buf：存放读出数据的指针变量
					length：需读数据的长度
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
unsigned char BSP_IIC_ReadData(u8 dev_addr,u8 regAddr,u8 *buf,u8 length){
	BSP_IIC_Start();
	/*************发送器件地址***************/
	BSP_IIC_Send_Byte(dev_addr);
	if(BSP_IIC_Wait_Ack()){	//等待应答
		BSP_IIC_Stop();
		return 1;
	}
	/*************发送寄存器地址***************/
	BSP_IIC_Send_Byte(regAddr);
	if(BSP_IIC_Wait_Ack()){	//等待应答
		BSP_IIC_Stop();	
		return 1;
	}
	/*************发送读数据命令***************/
	BSP_IIC_Start();
	BSP_IIC_Send_Byte(dev_addr+1);
	if(BSP_IIC_Wait_Ack()){	//等待应答
		BSP_IIC_Stop();	
		printf("hehe3\r\n");
		return 1;
	}
	while(length){
		if(length==1)
			*buf = BSP_IIC_Read_Byte(0);	//读数据,发送nACK 
		else 
			*buf = BSP_IIC_Read_Byte(1);	//读数据,发送ACK  
		length--;
		buf++;
	}
	
	BSP_IIC_Stop();	
	return 0;
}

/*
***************************************************
函数名：IIC_SW_Delay
功能：I2C总线位延迟
入口参数：	BSP_IIC_SCL_GPIO：IIC_SCL引脚号
					BSP_IIC_SDA_GPIO：IIC_SDA引脚号
返回值：无
应用范围：内部调用
备注：
***************************************************
*/
//static void IIC_SW_Delay(void)
//{
//	uint8_t i;

//	/*　
//		CPU主频168MHz时，在内部Flash运行, MDK工程不优化。用台式示波器观测波形。
//		循环次数为5时，SCL频率 = 1.78MHz (读耗时: 92ms, 读写正常，但是用示波器探头碰上就读写失败。时序接近临界)
//		循环次数为10时，SCL频率 = 1.1MHz (读耗时: 138ms, 读速度: 118724B/s)
//		循环次数为30时，SCL频率 = 440KHz， SCL高电平时间1.0us，SCL低电平时间1.2us

//		上拉电阻选择2.2K欧时，SCL上升沿时间约0.5us，如果选4.7K欧，则上升沿约1us

//		实际应用选择400KHz左右的速率即可
//	*/
//	for (i = 0; i < 30; i++);
//}

/*
***************************************************
函数名：BSP_IIC_SW_Init
功能：软件IIC初始化
入口参数：	BSP_IIC_SCL_GPIO：IIC_SCL引脚号
					BSP_IIC_SDA_GPIO：IIC_SDA引脚号
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_IIC_SW_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_IIC_SW,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	IIC_SCL=1;
	IIC_SDA=1;
}

/*
***************************************************
函数名：BSP_IIC_Start
功能：产生IIC起始信号
入口参数：无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_IIC_Start(void){
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	IIC_Delay();
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	IIC_Delay();
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  

/*
***************************************************
函数名：BSP_IIC_Stop
功能：产生IIC停止信号
入口参数：无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_IIC_Stop(void){
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	IIC_Delay();
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	IIC_Delay();							   	
}

/*
***************************************************
函数名：BSP_IIC_Wait_Ack
功能：等待应答信号到来
入口参数：无
返回值：	1，接收应答失败
				0，接收应答成功
应用范围：外部调用
备注：
***************************************************
*/
u8 BSP_IIC_Wait_Ack(void){
	u16 ucErrTime=0;
	IIC_SDA=1;
	SDA_IN();      //SDA设置为输入  
	IIC_Delay();	   
	IIC_SCL=1;IIC_Delay();	 
	while(READ_SDA){
		ucErrTime++;
		if(ucErrTime>1000){
			BSP_IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 

/*
***************************************************
函数名：BSP_IIC_Ack
功能：产生ACK应答
入口参数：无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_IIC_Ack(void){
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	IIC_Delay();
	IIC_SCL=1;
	IIC_Delay();
	IIC_SCL=0;
	IIC_Delay();
}

/*
***************************************************
函数名：BSP_IIC_NAck
功能：不产生ACK应答	
入口参数：无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_IIC_NAck(void){
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	IIC_Delay();
	IIC_SCL=1;
	IIC_Delay();
	IIC_SCL=0;
	IIC_Delay();
}					 				     

/*
***************************************************
函数名：BSP_IIC_Send_Byte
功能：IIC发送一个字节
入口参数：txd：发送的数据
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_IIC_Send_Byte(u8 txd){                        
	u8 t;   
	SDA_OUT(); 	    
	IIC_SCL = 0;//拉低时钟开始数据传输
	for(t=0;t<8;t++){              
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		IIC_Delay();
		IIC_SCL=1;
		IIC_Delay(); 
		IIC_SCL=0;	
		IIC_Delay();
	}	 
} 	 

/*
***************************************************
函数名：BSP_IIC_Read_Byte
功能：读1个字节
入口参数：ack=1时，发送ACK，ack=0，发送nACK   
返回值：无
应用范围：receive：接收的数据
备注：
***************************************************
*/
u8 BSP_IIC_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
	for(i=0;i<8;i++ ){
		IIC_SCL=0; 
		IIC_Delay();
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)	receive++;   
		IIC_Delay(); 
	}					 
	if (ack)
		BSP_IIC_Ack(); //发送ACK 
	else
		BSP_IIC_NAck();//发送nACK 
	return receive;
}


/*
***************************************************
函数名：BSP_IIC_CheckDevice
功能：检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
入口参数：Device_Address：设备的IIC总线地址
返回值：	0：表示正确
				1：表示未探测到
应用范围：receive：接收的数据
备注：
***************************************************
*/
uint8_t BSP_IIC_CheckDevice(uint8_t Device_Address){
	uint8_t ucAck;

	if (READ_SDA && READ_SCL){
		BSP_IIC_Start();		/* 发送启动信号 */

		/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
		BSP_IIC_Send_Byte(Device_Address | IIC_WR);
		ucAck = BSP_IIC_Wait_Ack();		/* 检测设备的ACK应答 */

		BSP_IIC_Stop();		/* 发送停止信号 */

		return ucAck;
	}
	return 1;	/* I2C总线异常 */
}
