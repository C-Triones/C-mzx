#include "BSP_USART.h"

/******************************外部调用函数************************************/
void BSP_USART_Init(BSP_USART_TypeDef *BSP_USARTx,uint8_t PreemptionPriority,uint8_t SubPriority);
void BSP_USART_TX_DMA_Init(BSP_USART_TypeDef *BSP_USARTx);
void BSP_USART_RX_DMA_Init(BSP_USART_TypeDef *BSP_USARTx);
void BSP_USART_SendData(BSP_USART_TypeDef *BSP_USARTx,uint8_t *Array,uint16_t len);
void BSP_USART_SendStr(BSP_USART_TypeDef *BSP_USARTx,uint8_t *Str);
uint8_t BSP_USART1_DMA_SendData(uint8_t *Array,uint16_t len);
uint8_t BSP_USART2_DMA_SendData(uint8_t *Array,uint16_t len);
uint8_t BSP_USART3_DMA_SendData(uint8_t *Array,uint16_t len);
uint8_t BSP_UART4_DMA_SendData(uint8_t *Array, uint16_t len);
uint8_t BSP_UART5_DMA_SendData(uint8_t *Array, uint16_t len);
uint8_t BSP_USART6_DMA_SendData(uint8_t *Array,uint16_t len);
/*****************************************************************************/

uint8_t Array_USART1_RX[Length_USART1_RX_Buff];
uint8_t Array_USART2_RX[Length_USART2_RX_Buff];
uint8_t Array_USART3_RX[Length_USART3_RX_Buff];
uint8_t Array_UART4_RX [Length_UART4_RX_Buff];
uint8_t Array_UART5_RX [Length_UART5_RX_Buff];
uint8_t Array_USART6_RX[Length_USART6_RX_Buff];

uint8_t Array_USART1_TX[Length_USART1_TX_Buff];
uint8_t Array_USART2_TX[Length_USART2_TX_Buff];
uint8_t Array_USART3_TX[Length_USART3_TX_Buff];
uint8_t Array_UART4_TX [Length_UART4_TX_Buff];
uint8_t Array_UART5_TX [Length_UART5_TX_Buff];
uint8_t Array_USART6_TX[Length_USART6_TX_Buff];

//宏定义使用printf()的串口
#define USARTx_printf USART6

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE { 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) { 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f){ 	
	while((USARTx_printf->SR&0X40)==0);//循环发送,直到发送完毕   
	USARTx_printf->DR = (uint8_t) ch;      
	return ch;
}

void _ttywrch(int ch) { 
	ch = ch; 
} 

/*
***************************************************
函数名：BSP_USART_RCC_Init
功能：配置USART外设时钟
入口参数：	USARTx：USART号
返回值：无
应用范围：内部调用
备注：
***************************************************
*/
void BSP_USART_RCC_Init(USART_TypeDef* USARTx){
	if(USARTx == USART1)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	else if(USARTx == USART2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	else if(USARTx == USART3)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	else if(USARTx == UART4)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	else if(USARTx == UART5)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	else if(USARTx == USART6)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
}

/*
***************************************************
函数名：CANx_TO_GPIO_AF
功能：从CAN号输出GPIO_AF
入口参数：	CANx：CAN号
返回值：GPIO_AF:复用的CAN模式
应用范围：内部调用
备注：
***************************************************
*/
uint8_t USARTx_TO_GPIO_AF(USART_TypeDef* USARTx){
	uint8_t GPIO_AF;
	
	if(USARTx == USART1)
		GPIO_AF = GPIO_AF_USART1;
	else if(USARTx == USART2)
		GPIO_AF = GPIO_AF_USART2;
	else if(USARTx == USART3)
		GPIO_AF = GPIO_AF_USART3;
	else if(USARTx == UART4)
		GPIO_AF = GPIO_AF_UART4;
	else if(USARTx == UART5)
		GPIO_AF = GPIO_AF_UART5;
	else if(USARTx == USART6)
		GPIO_AF = GPIO_AF_USART6;
	
	return GPIO_AF;
}

/*
***************************************************
函数名：GPIO_TO_NVIC_IRQChannel
功能：输出NVIC中断通道
入口参数：	GPIO：引脚号
返回值：NVIC_IRQChannel
应用范围：内部调用
备注：
***************************************************
*/
uint8_t	USART_TO_NVIC_IRQChannel(USART_TypeDef* USARTx){
	uint8_t NVIC_IRQChannel;
	
	if(USARTx == USART1)
		NVIC_IRQChannel = USART1_IRQn;
	else if(USARTx == USART2)
		NVIC_IRQChannel = USART2_IRQn;
	else if(USARTx == USART3)
		NVIC_IRQChannel = USART3_IRQn;
	else if(USARTx == UART4)
		NVIC_IRQChannel = UART4_IRQn;
	else if(USARTx == UART5)
		NVIC_IRQChannel = UART5_IRQn;
	else if(USARTx == USART6)
		NVIC_IRQChannel = USART6_IRQn;
	
	return NVIC_IRQChannel;	
}

/*
***************************************************
函数名：USART_TO_ArrayRX
功能：输出串口接收数组地址
入口参数：	GPIO：引脚号
返回值：ArrayRX
应用范围：内部调用
备注：
***************************************************
*/
uint32_t	USART_TO_ArrayRX(USART_TypeDef* USARTx){
	uint32_t ArrayRX;
	
	if(USARTx == USART1)
		ArrayRX = (uint32_t)Array_USART1_RX;
	else if(USARTx == USART2)
		ArrayRX = (uint32_t)Array_USART2_RX;
	else if(USARTx == USART3)
		ArrayRX = (uint32_t)Array_USART3_RX;
	else if(USARTx == UART4)
		ArrayRX = (uint32_t)Array_UART4_RX;
	else if(USARTx == UART5)
		ArrayRX = (uint32_t)Array_UART5_RX;
	else if(USARTx == USART6)
		ArrayRX = (uint32_t)Array_USART6_RX;

	
	return ArrayRX;	
}

/*
***************************************************
函数名：USART_TO_LengthArrayRX
功能：输出串口接收数组长度
入口参数：	GPIO：引脚号
返回值：ArrayRX
应用范围：内部调用
备注：
***************************************************
*/
uint32_t	USART_TO_LengthArrayRX(USART_TypeDef* USARTx){
	uint32_t Length;
	
	if(USARTx == USART1)
		Length = Length_USART1_RX_Buff;
	else if(USARTx == USART2)
		Length = Length_USART2_RX_Buff;
	else if(USARTx == USART3)
		Length = Length_USART3_RX_Buff;
	else if(USARTx == UART4)
		Length = Length_UART4_RX_Buff;
	else if(USARTx == UART5)
		Length = Length_UART5_RX_Buff;
	else if(USARTx == USART6)
		Length = Length_USART6_RX_Buff;

	
	return Length;	
}

/*
***************************************************
函数名：USART_TO_ArrayRX
功能：输出串口发送数组地址
入口参数：	GPIO：引脚号
返回值：ArrayRX
应用范围：内部调用
备注：
***************************************************
*/
uint32_t	USART_TO_ArrayTX(USART_TypeDef* USARTx){
	uint32_t ArrayTX;
	
	if(USARTx == USART1)
		ArrayTX = (uint32_t)Array_USART1_TX;
	else if(USARTx == USART2)
		ArrayTX = (uint32_t)Array_USART2_TX;
	else if(USARTx == USART3)
		ArrayTX = (uint32_t)Array_USART3_TX;
	else if(USARTx == UART4)
		ArrayTX = (uint32_t)Array_UART4_TX;
	else if(USARTx == UART5)
		ArrayTX = (uint32_t)Array_UART5_TX;
	else if(USARTx == USART6)
		ArrayTX = (uint32_t)Array_USART6_TX;

	
	return ArrayTX;	
}

/*
***************************************************
函数名：USART_TO_LengthArrayTX
功能：输出串口接收数组长度
入口参数：	GPIO：引脚号
返回值：ArrayTX
应用范围：内部调用
备注：
***************************************************
*/
uint32_t	USART_TO_LengthArrayTX(USART_TypeDef* USARTx){
	uint32_t Length;
	
	if(USARTx == USART1)
		Length = Length_USART1_TX_Buff;
	else if(USARTx == USART2)
		Length = Length_USART2_TX_Buff;
	else if(USARTx == USART3)
		Length = Length_USART3_TX_Buff;
	else if(USARTx == UART4)
		Length = Length_UART4_TX_Buff;
	else if(USARTx == UART5)
		Length = Length_UART5_TX_Buff;
	else if(USARTx == USART6)
		Length = Length_USART6_TX_Buff;
	
	return Length;	
}

BSP_DMA_TypeDef* USART_TO_BSP_DMA_Streamx_chx(USART_TypeDef* USARTx,uint16_t USART_DMAReq){
	BSP_DMA_TypeDef *DMA_Streamx_chx;
	if(USART_DMAReq == USART_DMAReq_Tx){
		if(USARTx == USART1)
			DMA_Streamx_chx = &BSP_DMA_USART1_TX;
		else if(USARTx == USART2)
			DMA_Streamx_chx = &BSP_DMA_USART2_TX;
		else if(USARTx == USART3)
			DMA_Streamx_chx = &BSP_DMA_USART3_TX;
		else if(USARTx == UART4)
			DMA_Streamx_chx = &BSP_DMA_UART4_TX;
		else if(USARTx == UART5)
			DMA_Streamx_chx = &BSP_DMA_UART5_TX;
		else if(USARTx == USART6)
			DMA_Streamx_chx = &BSP_DMA_USART6_TX;

	}
	else if(USART_DMAReq == USART_DMAReq_Rx){
		if(USARTx == USART1)
			DMA_Streamx_chx = &BSP_DMA_USART1_RX;
		else if(USARTx == USART2)
			DMA_Streamx_chx = &BSP_DMA_USART2_RX;
		else if(USARTx == USART3)
			DMA_Streamx_chx = &BSP_DMA_USART3_RX;
		else if(USARTx == UART4)
			DMA_Streamx_chx = &BSP_DMA_UART4_RX;
		else if(USARTx == UART5)
			DMA_Streamx_chx = &BSP_DMA_UART5_RX;
		else if(USARTx == USART6)
			DMA_Streamx_chx = &BSP_DMA_USART6_RX;
	}
	return DMA_Streamx_chx;
}

/*
***************************************************
函数名：BSP_USART_Init
功能：USART初始化
入口参数：	BSP_USARTx：串口号
					PreemptionPriority：抢占优先级 0xff时失能串口中断
					SubPriority：子优先级 0xff时失能串口中断
返回值：无
应用范围：外部调用
备注：不用串口中断时请  PreemptionPriority=0xff，SubPriority=0xff
***************************************************
*/
void BSP_USART_Init(BSP_USART_TypeDef *BSP_USARTx,uint8_t PreemptionPriority,uint8_t SubPriority){
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct = BSP_USARTx->USART_InitStructure;
	
	/*************初始化USARTx时钟***************/
	BSP_USART_RCC_Init(BSP_USARTx->USARTx);
	
	/*************初始化USARTx引脚***************/
	if(BSP_USARTx->USART_TX != NULL)
		BSP_GPIO_Init(BSP_USARTx->USART_TX,GPIO_Mode_AF_PP);	//初始化USART_TX引脚为复用推挽
	if(BSP_USARTx->USART_RX != NULL)
		BSP_GPIO_Init(BSP_USARTx->USART_RX,GPIO_Mode_AF_PP);	//初始化USART_RX引脚为复用推挽
	
	/*************引脚复用映射配置***************/
	if(BSP_USARTx->USART_TX != NULL)
		GPIO_Pin_TO_PinAFConfig(BSP_USARTx->USART_TX,USARTx_TO_GPIO_AF(BSP_USARTx->USARTx));	//USART_TX引脚复用为 USARTx
	if(BSP_USARTx->USART_RX != NULL)
		GPIO_Pin_TO_PinAFConfig(BSP_USARTx->USART_RX,USARTx_TO_GPIO_AF(BSP_USARTx->USARTx));	//USART_RX引脚复用为 USARTx
	
	/*************USARTx初始化设置***************/
	USART_Init(BSP_USARTx->USARTx, &USART_InitStruct); //初始化串口x
	
	/*************USARTx NVIC配置***************/
	if( (PreemptionPriority!=0xff) && (SubPriority!=0xff) ){
		NVIC_InitStructure.NVIC_IRQChannel = USART_TO_NVIC_IRQChannel(BSP_USARTx->USARTx);
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		
		USART_ITConfig(BSP_USARTx->USARTx, USART_IT_IDLE, ENABLE);//开启串口空闲中断
	}
	
	if(BSP_USARTx->USART_TX != NULL)
		USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Tx,ENABLE);	//开启串口DMA发送
	if(BSP_USARTx->USART_RX != NULL)
		USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Rx,ENABLE);	//开启串口DMA接收
	
  USART_Cmd(BSP_USARTx->USARTx, ENABLE);                    	//使能串口
}

void BSP_USART_TX_DMA_Init(BSP_USART_TypeDef *BSP_USARTx){
	uint32_t mar = USART_TO_ArrayTX(BSP_USARTx->USARTx);
	BSP_DMA_TypeDef *BSP_DMA_Streamx_chx = USART_TO_BSP_DMA_Streamx_chx(BSP_USARTx->USARTx,USART_DMAReq_Tx);
	BSP_DMA_TX_Init(BSP_DMA_Streamx_chx,(uint32_t)&BSP_USARTx->USARTx->DR,mar,0);
	USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Tx,ENABLE);	//开启串口DMA发送
}

void BSP_USART_RX_DMA_Init(BSP_USART_TypeDef *BSP_USARTx){
	uint32_t mar = USART_TO_ArrayRX(BSP_USARTx->USARTx);
	uint32_t ndtr = USART_TO_LengthArrayRX(BSP_USARTx->USARTx);
	BSP_DMA_TypeDef *BSP_DMA_Streamx_chx = USART_TO_BSP_DMA_Streamx_chx(BSP_USARTx->USARTx,USART_DMAReq_Rx);
	BSP_DMA_RX_Init(BSP_DMA_Streamx_chx,(uint32_t)&BSP_USARTx->USARTx->DR,mar,ndtr);
	USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Rx,ENABLE);	//开启串口DMA接收
}

/*
***************************************************
函数名：BSP_USART_SendData
功能：串口普通发送一组数据
入口参数：	BSP_USARTx：串口号
					Array：发送数组指针
					len：数据长度
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_USART_SendData(BSP_USART_TypeDef *BSP_USARTx,uint8_t *Array,uint16_t len){
	uint8_t i;
	for(i=0;i<len;i++){
		BSP_USARTx->USARTx->DR = Array[i];
		while((BSP_USARTx->USARTx->SR & USART_FLAG_TC)==0);	//等待发送结束
	}
}

/*
***************************************************
函数名：BSP_USART_SendData
功能：串口普通发送一组数据
入口参数：	BSP_USARTx：串口号
					Str：发送字符串指针
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void BSP_USART_SendStr(BSP_USART_TypeDef *BSP_USARTx,uint8_t *Str){
	uint16_t i;
	for(i=0;Str[i]!=0;i++){
		BSP_USARTx->USARTx->DR = Str[i];
		while((BSP_USARTx->USARTx->SR & USART_FLAG_TC)==0);	//等待发送结束
	}
}

/*
***************************************************
函数名：BSP_USART1_DMA_SendData
功能：串口1 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_USART1_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA2_Stream7->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA2_Stream7, DISABLE); 
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA2_Stream7, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7 | DMA_FLAG_HTIF7);	//清空标志位
	DMA2_Stream7->M0AR = (uint32_t)Array;
	DMA2_Stream7->NDTR = len;
	DMA_Cmd(DMA2_Stream7, ENABLE);   
	return 0;
}

/*
***************************************************
函数名：BSP_USART2_DMA_SendData
功能：串口2 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_USART2_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream6->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA1_Stream6, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream6) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream6, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6 | DMA_FLAG_HTIF6);	//清空标志位
	DMA1_Stream6->M0AR = (uint32_t)Array;
	DMA1_Stream6->NDTR = len;
	DMA_Cmd(DMA1_Stream6, ENABLE);   
	return 0;
}

/*
***************************************************
函数名：BSP_USART3_DMA_SendData
功能：串口3 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_USART3_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream3->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA1_Stream3, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream3, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3 | DMA_FLAG_HTIF3);	//清空标志位
	DMA1_Stream3->M0AR = (uint32_t)Array;
	DMA1_Stream3->NDTR = len;
	DMA_Cmd(DMA1_Stream3, ENABLE);   
	return 0;
}

/*
***************************************************
函数名：BSP_UART4_DMA_SendData
功能：串口4 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_UART4_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream4->NDTR){													  //DMA通道中是否还有未传输的数据s
		return 1;
	}
	DMA_Cmd(DMA1_Stream4, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream4) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream4, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4 | DMA_FLAG_HTIF4);	//清空标志位
	DMA1_Stream4->M0AR = (uint32_t)Array;
	DMA1_Stream4->NDTR = len;
	DMA_Cmd(DMA1_Stream4, ENABLE);  
	return 0;	
}

/*
***************************************************
函数名：BSP_UART5_DMA_SendData
功能：串口5 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_UART5_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream7->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA1_Stream7, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream7) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream7, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7 | DMA_FLAG_HTIF7);	//清空标志位
	DMA1_Stream7->M0AR = (uint32_t)Array;
	DMA1_Stream7->NDTR = len;
	DMA_Cmd(DMA1_Stream7, ENABLE);  
	return 0;
}

/*
***************************************************
函数名：BSP_USART6_DMA_SendData
功能：串口6 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_USART6_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA2_Stream6->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA2_Stream6, DISABLE); 
	while (DMA_GetCmdStatus(DMA2_Stream6) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA2_Stream6, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA2_Stream6, DMA_FLAG_TCIF6 | DMA_FLAG_HTIF6);	//清空标志位
	DMA2_Stream6->M0AR = (uint32_t)Array;
	DMA2_Stream6->NDTR = len;
	DMA_Cmd(DMA2_Stream6, ENABLE); 
	return 0;
}

/*
***************************************************
函数名：BSP_UART7_DMA_SendData
功能：串口7 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_UART7_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream1->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA1_Stream1, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream1, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1 | DMA_FLAG_HTIF1);	//清空标志位
	DMA1_Stream1->M0AR = (uint32_t)Array;
	DMA1_Stream1->NDTR = len;
	DMA_Cmd(DMA1_Stream1, ENABLE); 
	return 0;
}

/*
***************************************************
函数名：BSP_UART8_DMA_SendData
功能：串口8 DMA发送一组数据
入口参数：	Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_UART8_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream0->NDTR){														//DMA通道中是否还有未传输的数据
		return 1;
	}
	DMA_Cmd(DMA1_Stream0, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream0) != DISABLE){//确保 DMA 可以被设置
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream0, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0);	//清空标志位
	DMA1_Stream0->M0AR = (uint32_t)Array;
	DMA1_Stream0->NDTR = len;
	DMA_Cmd(DMA1_Stream0, ENABLE); 
	return 0;
}

/*
***************************************************
函数名：BSP_USART_DMA_SendData
功能：串口自适应DMA发送一组数据
入口参数：	USARTx:串口号
					Str：发送字符串指针
					len：数据指针
返回值：	0：发送成功
				1：DMA中有未传输数据
				2：DMA设置超时
应用范围：外部调用
备注：
***************************************************
*/
uint8_t BSP_USART_DMA_SendData(USART_TypeDef *USARTx, uint8_t *Array, uint16_t len){
	uint8_t retry = 0;
	if(USARTx == USART1)
		retry = BSP_USART1_DMA_SendData(Array, len);
	else if(USARTx == USART2)
		retry = BSP_USART2_DMA_SendData(Array, len);
	else if(USARTx == USART3)
		retry = BSP_USART3_DMA_SendData(Array, len);
	else if(USARTx == UART4)
		retry = BSP_UART4_DMA_SendData(Array, len);
	else if(USARTx == UART5)
		retry = BSP_UART5_DMA_SendData(Array, len);
	else if(USARTx == USART6)
		retry = BSP_USART6_DMA_SendData(Array, len);

	return retry;
}
