#include "bsp.h"

/******************************�ⲿ���ú���************************************/
void BSP_IIC_SW_Init(void);	
unsigned char BSP_IIC_WriteData(u8 dev_addr,u8 regAddr,u8 data);
unsigned char BSP_IIC_ReadData(u8 dev_addr,u8 regAddr,u8 *buf,u8 length);
void BSP_IIC_Start(void);		//����IIC��ʼ�ź�
void BSP_IIC_Stop(void);		//����IICֹͣ�ź�
void BSP_IIC_Send_Byte(u8 txd);		//IIC����һ���ֽ�
u8 BSP_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 BSP_IIC_Wait_Ack(void);	//IIC�ȴ�ACK�ź�
void BSP_IIC_Ack(void);			//IIC����ACK�ź�
void BSP_IIC_NAck(void);		//IIC������ACK�ź� 
uint8_t BSP_IIC_CheckDevice(uint8_t Device_Address);//����豸
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
��������BSP_IIC_WriteData
���ܣ����IICд����
��ڲ�����	dev_addr��������ַ
					regAddr����д�ļĴ�����ַ
					data����д������
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
unsigned char BSP_IIC_WriteData(u8 dev_addr,u8 regAddr,u8 data){
	BSP_IIC_Start();
	/*************����������ַ***************/
	BSP_IIC_Send_Byte(dev_addr);
	if(BSP_IIC_Wait_Ack()){	//�ȴ�Ӧ��
		BSP_IIC_Stop();		 
		return 1;
	}
	/*************���ͼĴ�����ַ***************/
	BSP_IIC_Send_Byte(regAddr);
	if(BSP_IIC_Wait_Ack()){	//�ȴ�Ӧ��
		BSP_IIC_Stop();		 
		return 1;
	}
	/*************��������***************/
	BSP_IIC_Send_Byte(data);
	if(BSP_IIC_Wait_Ack()){	//�ȴ�Ӧ��
		BSP_IIC_Stop();		 
		return 1;
	}
	BSP_IIC_Stop();	
	return 0;
}

/*
***************************************************
��������BSP_IIC_ReadData
���ܣ����IIC������
��ڲ�����	dev_addr��������ַ
					regAddr������ļĴ�����ַ
					buf����Ŷ������ݵ�ָ�����
					length��������ݵĳ���
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
unsigned char BSP_IIC_ReadData(u8 dev_addr,u8 regAddr,u8 *buf,u8 length){
	BSP_IIC_Start();
	/*************����������ַ***************/
	BSP_IIC_Send_Byte(dev_addr);
	if(BSP_IIC_Wait_Ack()){	//�ȴ�Ӧ��
		BSP_IIC_Stop();
		return 1;
	}
	/*************���ͼĴ�����ַ***************/
	BSP_IIC_Send_Byte(regAddr);
	if(BSP_IIC_Wait_Ack()){	//�ȴ�Ӧ��
		BSP_IIC_Stop();	
		return 1;
	}
	/*************���Ͷ���������***************/
	BSP_IIC_Start();
	BSP_IIC_Send_Byte(dev_addr+1);
	if(BSP_IIC_Wait_Ack()){	//�ȴ�Ӧ��
		BSP_IIC_Stop();	
		printf("hehe3\r\n");
		return 1;
	}
	while(length){
		if(length==1)
			*buf = BSP_IIC_Read_Byte(0);	//������,����nACK 
		else 
			*buf = BSP_IIC_Read_Byte(1);	//������,����ACK  
		length--;
		buf++;
	}
	
	BSP_IIC_Stop();	
	return 0;
}

/*
***************************************************
��������IIC_SW_Delay
���ܣ�I2C����λ�ӳ�
��ڲ�����	BSP_IIC_SCL_GPIO��IIC_SCL���ź�
					BSP_IIC_SDA_GPIO��IIC_SDA���ź�
����ֵ����
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
//static void IIC_SW_Delay(void)
//{
//	uint8_t i;

//	/*��
//		CPU��Ƶ168MHzʱ�����ڲ�Flash����, MDK���̲��Ż�����̨ʽʾ�����۲Ⲩ�Ρ�
//		ѭ������Ϊ5ʱ��SCLƵ�� = 1.78MHz (����ʱ: 92ms, ��д������������ʾ����̽ͷ���ϾͶ�дʧ�ܡ�ʱ��ӽ��ٽ�)
//		ѭ������Ϊ10ʱ��SCLƵ�� = 1.1MHz (����ʱ: 138ms, ���ٶ�: 118724B/s)
//		ѭ������Ϊ30ʱ��SCLƵ�� = 440KHz�� SCL�ߵ�ƽʱ��1.0us��SCL�͵�ƽʱ��1.2us

//		��������ѡ��2.2Kŷʱ��SCL������ʱ��Լ0.5us�����ѡ4.7Kŷ����������Լ1us

//		ʵ��Ӧ��ѡ��400KHz���ҵ����ʼ���
//	*/
//	for (i = 0; i < 30; i++);
//}

/*
***************************************************
��������BSP_IIC_SW_Init
���ܣ����IIC��ʼ��
��ڲ�����	BSP_IIC_SCL_GPIO��IIC_SCL���ź�
					BSP_IIC_SDA_GPIO��IIC_SDA���ź�
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
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
��������BSP_IIC_Start
���ܣ�����IIC��ʼ�ź�
��ڲ�������
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_IIC_Start(void){
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	IIC_Delay();
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	IIC_Delay();
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

/*
***************************************************
��������BSP_IIC_Stop
���ܣ�����IICֹͣ�ź�
��ڲ�������
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_IIC_Stop(void){
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	IIC_Delay();
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	IIC_Delay();							   	
}

/*
***************************************************
��������BSP_IIC_Wait_Ack
���ܣ��ȴ�Ӧ���źŵ���
��ڲ�������
����ֵ��	1������Ӧ��ʧ��
				0������Ӧ��ɹ�
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
u8 BSP_IIC_Wait_Ack(void){
	u16 ucErrTime=0;
	IIC_SDA=1;
	SDA_IN();      //SDA����Ϊ����  
	IIC_Delay();	   
	IIC_SCL=1;IIC_Delay();	 
	while(READ_SDA){
		ucErrTime++;
		if(ucErrTime>1000){
			BSP_IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 

/*
***************************************************
��������BSP_IIC_Ack
���ܣ�����ACKӦ��
��ڲ�������
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
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
��������BSP_IIC_NAck
���ܣ�������ACKӦ��	
��ڲ�������
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
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
��������BSP_IIC_Send_Byte
���ܣ�IIC����һ���ֽ�
��ڲ�����txd�����͵�����
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_IIC_Send_Byte(u8 txd){                        
	u8 t;   
	SDA_OUT(); 	    
	IIC_SCL = 0;//����ʱ�ӿ�ʼ���ݴ���
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
��������BSP_IIC_Read_Byte
���ܣ���1���ֽ�
��ڲ�����ack=1ʱ������ACK��ack=0������nACK   
����ֵ����
Ӧ�÷�Χ��receive�����յ�����
��ע��
***************************************************
*/
u8 BSP_IIC_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ ){
		IIC_SCL=0; 
		IIC_Delay();
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)	receive++;   
		IIC_Delay(); 
	}					 
	if (ack)
		BSP_IIC_Ack(); //����ACK 
	else
		BSP_IIC_NAck();//����nACK 
	return receive;
}


/*
***************************************************
��������BSP_IIC_CheckDevice
���ܣ����I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
��ڲ�����Device_Address���豸��IIC���ߵ�ַ
����ֵ��	0����ʾ��ȷ
				1����ʾδ̽�⵽
Ӧ�÷�Χ��receive�����յ�����
��ע��
***************************************************
*/
uint8_t BSP_IIC_CheckDevice(uint8_t Device_Address){
	uint8_t ucAck;

	if (READ_SDA && READ_SCL){
		BSP_IIC_Start();		/* ���������ź� */

		/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
		BSP_IIC_Send_Byte(Device_Address | IIC_WR);
		ucAck = BSP_IIC_Wait_Ack();		/* ����豸��ACKӦ�� */

		BSP_IIC_Stop();		/* ����ֹͣ�ź� */

		return ucAck;
	}
	return 1;	/* I2C�����쳣 */
}
