#include "BSP_USART.h"

/******************************�ⲿ���ú���************************************/
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

//�궨��ʹ��printf()�Ĵ���
#define USARTx_printf USART6

#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE { 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) { 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f){ 	
	while((USARTx_printf->SR&0X40)==0);//ѭ������,ֱ���������   
	USARTx_printf->DR = (uint8_t) ch;      
	return ch;
}

void _ttywrch(int ch) { 
	ch = ch; 
} 

/*
***************************************************
��������BSP_USART_RCC_Init
���ܣ�����USART����ʱ��
��ڲ�����	USARTx��USART��
����ֵ����
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������CANx_TO_GPIO_AF
���ܣ���CAN�����GPIO_AF
��ڲ�����	CANx��CAN��
����ֵ��GPIO_AF:���õ�CANģʽ
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������GPIO_TO_NVIC_IRQChannel
���ܣ����NVIC�ж�ͨ��
��ڲ�����	GPIO�����ź�
����ֵ��NVIC_IRQChannel
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������USART_TO_ArrayRX
���ܣ�������ڽ��������ַ
��ڲ�����	GPIO�����ź�
����ֵ��ArrayRX
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������USART_TO_LengthArrayRX
���ܣ�������ڽ������鳤��
��ڲ�����	GPIO�����ź�
����ֵ��ArrayRX
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������USART_TO_ArrayRX
���ܣ�������ڷ��������ַ
��ڲ�����	GPIO�����ź�
����ֵ��ArrayRX
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������USART_TO_LengthArrayTX
���ܣ�������ڽ������鳤��
��ڲ�����	GPIO�����ź�
����ֵ��ArrayTX
Ӧ�÷�Χ���ڲ�����
��ע��
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
��������BSP_USART_Init
���ܣ�USART��ʼ��
��ڲ�����	BSP_USARTx�����ں�
					PreemptionPriority����ռ���ȼ� 0xffʱʧ�ܴ����ж�
					SubPriority�������ȼ� 0xffʱʧ�ܴ����ж�
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע�����ô����ж�ʱ��  PreemptionPriority=0xff��SubPriority=0xff
***************************************************
*/
void BSP_USART_Init(BSP_USART_TypeDef *BSP_USARTx,uint8_t PreemptionPriority,uint8_t SubPriority){
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct = BSP_USARTx->USART_InitStructure;
	
	/*************��ʼ��USARTxʱ��***************/
	BSP_USART_RCC_Init(BSP_USARTx->USARTx);
	
	/*************��ʼ��USARTx����***************/
	if(BSP_USARTx->USART_TX != NULL)
		BSP_GPIO_Init(BSP_USARTx->USART_TX,GPIO_Mode_AF_PP);	//��ʼ��USART_TX����Ϊ��������
	if(BSP_USARTx->USART_RX != NULL)
		BSP_GPIO_Init(BSP_USARTx->USART_RX,GPIO_Mode_AF_PP);	//��ʼ��USART_RX����Ϊ��������
	
	/*************���Ÿ���ӳ������***************/
	if(BSP_USARTx->USART_TX != NULL)
		GPIO_Pin_TO_PinAFConfig(BSP_USARTx->USART_TX,USARTx_TO_GPIO_AF(BSP_USARTx->USARTx));	//USART_TX���Ÿ���Ϊ USARTx
	if(BSP_USARTx->USART_RX != NULL)
		GPIO_Pin_TO_PinAFConfig(BSP_USARTx->USART_RX,USARTx_TO_GPIO_AF(BSP_USARTx->USARTx));	//USART_RX���Ÿ���Ϊ USARTx
	
	/*************USARTx��ʼ������***************/
	USART_Init(BSP_USARTx->USARTx, &USART_InitStruct); //��ʼ������x
	
	/*************USARTx NVIC����***************/
	if( (PreemptionPriority!=0xff) && (SubPriority!=0xff) ){
		NVIC_InitStructure.NVIC_IRQChannel = USART_TO_NVIC_IRQChannel(BSP_USARTx->USARTx);
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
		USART_ITConfig(BSP_USARTx->USARTx, USART_IT_IDLE, ENABLE);//�������ڿ����ж�
	}
	
	if(BSP_USARTx->USART_TX != NULL)
		USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Tx,ENABLE);	//��������DMA����
	if(BSP_USARTx->USART_RX != NULL)
		USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Rx,ENABLE);	//��������DMA����
	
  USART_Cmd(BSP_USARTx->USARTx, ENABLE);                    	//ʹ�ܴ���
}

void BSP_USART_TX_DMA_Init(BSP_USART_TypeDef *BSP_USARTx){
	uint32_t mar = USART_TO_ArrayTX(BSP_USARTx->USARTx);
	BSP_DMA_TypeDef *BSP_DMA_Streamx_chx = USART_TO_BSP_DMA_Streamx_chx(BSP_USARTx->USARTx,USART_DMAReq_Tx);
	BSP_DMA_TX_Init(BSP_DMA_Streamx_chx,(uint32_t)&BSP_USARTx->USARTx->DR,mar,0);
	USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Tx,ENABLE);	//��������DMA����
}

void BSP_USART_RX_DMA_Init(BSP_USART_TypeDef *BSP_USARTx){
	uint32_t mar = USART_TO_ArrayRX(BSP_USARTx->USARTx);
	uint32_t ndtr = USART_TO_LengthArrayRX(BSP_USARTx->USARTx);
	BSP_DMA_TypeDef *BSP_DMA_Streamx_chx = USART_TO_BSP_DMA_Streamx_chx(BSP_USARTx->USARTx,USART_DMAReq_Rx);
	BSP_DMA_RX_Init(BSP_DMA_Streamx_chx,(uint32_t)&BSP_USARTx->USARTx->DR,mar,ndtr);
	USART_DMACmd(BSP_USARTx->USARTx,USART_DMAReq_Rx,ENABLE);	//��������DMA����
}

/*
***************************************************
��������BSP_USART_SendData
���ܣ�������ͨ����һ������
��ڲ�����	BSP_USARTx�����ں�
					Array����������ָ��
					len�����ݳ���
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_USART_SendData(BSP_USART_TypeDef *BSP_USARTx,uint8_t *Array,uint16_t len){
	uint8_t i;
	for(i=0;i<len;i++){
		BSP_USARTx->USARTx->DR = Array[i];
		while((BSP_USARTx->USARTx->SR & USART_FLAG_TC)==0);	//�ȴ����ͽ���
	}
}

/*
***************************************************
��������BSP_USART_SendData
���ܣ�������ͨ����һ������
��ڲ�����	BSP_USARTx�����ں�
					Str�������ַ���ָ��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_USART_SendStr(BSP_USART_TypeDef *BSP_USARTx,uint8_t *Str){
	uint16_t i;
	for(i=0;Str[i]!=0;i++){
		BSP_USARTx->USARTx->DR = Str[i];
		while((BSP_USARTx->USARTx->SR & USART_FLAG_TC)==0);	//�ȴ����ͽ���
	}
}

/*
***************************************************
��������BSP_USART1_DMA_SendData
���ܣ�����1 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_USART1_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA2_Stream7->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA2_Stream7, DISABLE); 
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA2_Stream7, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7 | DMA_FLAG_HTIF7);	//��ձ�־λ
	DMA2_Stream7->M0AR = (uint32_t)Array;
	DMA2_Stream7->NDTR = len;
	DMA_Cmd(DMA2_Stream7, ENABLE);   
	return 0;
}

/*
***************************************************
��������BSP_USART2_DMA_SendData
���ܣ�����2 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_USART2_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream6->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA1_Stream6, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream6) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream6, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6 | DMA_FLAG_HTIF6);	//��ձ�־λ
	DMA1_Stream6->M0AR = (uint32_t)Array;
	DMA1_Stream6->NDTR = len;
	DMA_Cmd(DMA1_Stream6, ENABLE);   
	return 0;
}

/*
***************************************************
��������BSP_USART3_DMA_SendData
���ܣ�����3 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_USART3_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream3->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA1_Stream3, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream3, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3 | DMA_FLAG_HTIF3);	//��ձ�־λ
	DMA1_Stream3->M0AR = (uint32_t)Array;
	DMA1_Stream3->NDTR = len;
	DMA_Cmd(DMA1_Stream3, ENABLE);   
	return 0;
}

/*
***************************************************
��������BSP_UART4_DMA_SendData
���ܣ�����4 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_UART4_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream4->NDTR){													  //DMAͨ�����Ƿ���δ���������s
		return 1;
	}
	DMA_Cmd(DMA1_Stream4, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream4) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream4, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4 | DMA_FLAG_HTIF4);	//��ձ�־λ
	DMA1_Stream4->M0AR = (uint32_t)Array;
	DMA1_Stream4->NDTR = len;
	DMA_Cmd(DMA1_Stream4, ENABLE);  
	return 0;	
}

/*
***************************************************
��������BSP_UART5_DMA_SendData
���ܣ�����5 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_UART5_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream7->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA1_Stream7, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream7) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream7, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7 | DMA_FLAG_HTIF7);	//��ձ�־λ
	DMA1_Stream7->M0AR = (uint32_t)Array;
	DMA1_Stream7->NDTR = len;
	DMA_Cmd(DMA1_Stream7, ENABLE);  
	return 0;
}

/*
***************************************************
��������BSP_USART6_DMA_SendData
���ܣ�����6 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_USART6_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA2_Stream6->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA2_Stream6, DISABLE); 
	while (DMA_GetCmdStatus(DMA2_Stream6) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA2_Stream6, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA2_Stream6, DMA_FLAG_TCIF6 | DMA_FLAG_HTIF6);	//��ձ�־λ
	DMA2_Stream6->M0AR = (uint32_t)Array;
	DMA2_Stream6->NDTR = len;
	DMA_Cmd(DMA2_Stream6, ENABLE); 
	return 0;
}

/*
***************************************************
��������BSP_UART7_DMA_SendData
���ܣ�����7 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_UART7_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream1->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA1_Stream1, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream1, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1 | DMA_FLAG_HTIF1);	//��ձ�־λ
	DMA1_Stream1->M0AR = (uint32_t)Array;
	DMA1_Stream1->NDTR = len;
	DMA_Cmd(DMA1_Stream1, ENABLE); 
	return 0;
}

/*
***************************************************
��������BSP_UART8_DMA_SendData
���ܣ�����8 DMA����һ������
��ڲ�����	Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
uint8_t BSP_UART8_DMA_SendData(uint8_t *Array,uint16_t len){
	unsigned char retry=0;
	if(DMA1_Stream0->NDTR){														//DMAͨ�����Ƿ���δ���������
		return 1;
	}
	DMA_Cmd(DMA1_Stream0, DISABLE); 
	while (DMA_GetCmdStatus(DMA1_Stream0) != DISABLE){//ȷ�� DMA ���Ա�����
		retry++;
		if(retry > 200){
			DMA_Cmd(DMA1_Stream0, ENABLE);
			return 2;
		}
	}
	DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0);	//��ձ�־λ
	DMA1_Stream0->M0AR = (uint32_t)Array;
	DMA1_Stream0->NDTR = len;
	DMA_Cmd(DMA1_Stream0, ENABLE); 
	return 0;
}

/*
***************************************************
��������BSP_USART_DMA_SendData
���ܣ���������ӦDMA����һ������
��ڲ�����	USARTx:���ں�
					Str�������ַ���ָ��
					len������ָ��
����ֵ��	0�����ͳɹ�
				1��DMA����δ��������
				2��DMA���ó�ʱ
Ӧ�÷�Χ���ⲿ����
��ע��
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
