#include "BSP_CAN.h"

/******************************�ⲿ���ú���************************************/
void BSP_CAN_Mode_Init(BSP_CAN_TypeDef *BSP_CANx,u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u8 PreemptionPriority,u8 SubPriority);
 u8	 BSP_CAN_Send_Msg(BSP_CAN_TypeDef *BSP_CANx,CanTxMsg *TxMessage);
 u8	 BSP_CAN_Receive_Msg(BSP_CAN_TypeDef *BSP_CANx,CanRxMsg *RxMessage);
/*****************************************************************************/

const CAN_FilterInitTypeDef  CAN1_FilterInitStructure = {
	.CAN_FilterNumber = 0,										/*������0*/					
	.CAN_FilterMode = CAN_FilterMode_IdMask,	/*��ʶ������λģʽ*/	
	.CAN_FilterScale = CAN_FilterScale_32bit,	/*32λ��ģʽ*/				
	.CAN_FilterIdHigh = 0x0000,								/*32λMASK*/				
	.CAN_FilterIdLow = 0x0000,
	.CAN_FilterMaskIdHigh = 0x0000,
	.CAN_FilterMaskIdLow = 0x0000,
	.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0,	/*������0������FIFO0*/	
	.CAN_FilterActivation = ENABLE,								/*���������*/					
};

const CAN_FilterInitTypeDef  CAN2_FilterInitStructure = {
	.CAN_FilterNumber = 14,										/*������0*/					
	.CAN_FilterMode = CAN_FilterMode_IdMask,	/*��ʶ������λģʽ*/	
	.CAN_FilterScale = CAN_FilterScale_32bit,	/*32λ��ģʽ*/				
	.CAN_FilterIdHigh = 0x0000,								/*32λMASK*/				
	.CAN_FilterIdLow = 0x0000,
	.CAN_FilterMaskIdHigh = 0x0000,
	.CAN_FilterMaskIdLow = 0x0000,
	.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0,	/*������0������FIFO0*/	
	.CAN_FilterActivation = ENABLE,								/*���������*/					
};

/*
***************************************************
��������BSP_SPI_RCBSP_CAN_RCC_InitC_Init
���ܣ�����CAN����ʱ��
��ڲ�����	CANx��CAN��
����ֵ����
Ӧ�÷�Χ���ڲ�����
��ע��
***************************************************
*/
static void BSP_CAN_RCC_Init(CAN_TypeDef* CANx){
	uint32_t RCC_CANx;
	
	if(CANx == CAN1)
		RCC_CANx = RCC_APB1Periph_CAN1;
	else if(CANx == CAN2)
		RCC_CANx = RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2;
	
	RCC_APB1PeriphClockCmd(RCC_CANx,ENABLE);
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
static uint8_t CANx_TO_GPIO_AF(CAN_TypeDef *CANx){
	uint8_t GPIO_AF;
	if(CANx == CAN1)			
		GPIO_AF = GPIO_AF_CAN1;
	else if(CANx == CAN2)	
		GPIO_AF = GPIO_AF_CAN2;
	
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
static uint8_t	CAN_TO_NVIC_IRQChannel(CAN_TypeDef* CANx){
	uint8_t NVIC_IRQChannel;
	
	if(CANx == CAN1)			
		NVIC_IRQChannel = CAN1_RX0_IRQn;
	else if(CANx == CAN2)	
		NVIC_IRQChannel = CAN2_RX0_IRQn;
	
	return NVIC_IRQChannel;	
}

/*
***************************************************
��������BSP_CAN_Mode_Init
���ܣ�CAN��ʼ��
��ڲ�����	BSP_CANx��CAN��
					tsjw������ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
					tbs2��ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
					tbs1��ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
					brp �������ʷ�Ƶ��.				��Χ:1~1024; tq=(brp)*tpclk1
					mode��CANxģʽ							��Χ:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
					PreemptionPriority����ռ���ȼ�
					SubPriority�������ȼ�
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע���ѽ����ʼ��CAN2�����ȳ�ʼ��CAN1
***************************************************
*/
void BSP_CAN_Mode_Init(BSP_CAN_TypeDef *BSP_CANx,u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u8 PreemptionPriority,u8 SubPriority){
	CAN_InitTypeDef		CAN_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	
	CAN_FilterInitStruct = BSP_CANx->CAN_FilterInitStructure;
	
	/*************��ʼ��CANxʱ��***************/
	BSP_CAN_RCC_Init(BSP_CANx->CANx);
	
	/*************��ʼ��CANx����***************/
	BSP_GPIO_Init(BSP_CANx->CANx_RX,GPIO_Mode_AF_PP);	//��ʼ��CANx_RX����Ϊ��������
	BSP_GPIO_Init(BSP_CANx->CANx_TX,GPIO_Mode_AF_PP);	//��ʼ��CANx_TX����Ϊ��������
	
	/*************���Ÿ���ӳ������***************/
	GPIO_Pin_TO_PinAFConfig(BSP_CANx->CANx_RX,CANx_TO_GPIO_AF(BSP_CANx->CANx));	//CANx_RX���Ÿ���Ϊ CANx
	GPIO_Pin_TO_PinAFConfig(BSP_CANx->CANx_TX,CANx_TO_GPIO_AF(BSP_CANx->CANx));	//CANx_TX���Ÿ���Ϊ CANx
	
	/****************CAN��Ԫ����*****************/
	CAN_InitStructure.CAN_TTCM=DISABLE;		//��ʱ�䴥��ͨ��ģʽ   
	CAN_InitStructure.CAN_ABOM=ENABLE;		//����Զ����߹���	  
	CAN_InitStructure.CAN_AWUM=DISABLE;		//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	CAN_InitStructure.CAN_NART=DISABLE;		//��ֹ�����Զ����� 
	CAN_InitStructure.CAN_RFLM=DISABLE;		//���Ĳ�����,�µĸ��Ǿɵ�  
	CAN_InitStructure.CAN_TXFP=DISABLE;		//���ȼ��ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode= mode;	 		//ģʽ���� 
	CAN_InitStructure.CAN_SJW=tsjw;				//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=tbs1; 			//Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=tbs2;				//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=brp;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
	CAN_Init(BSP_CANx->CANx, &CAN_InitStructure);   // ��ʼ��CANx 
	
	/****************CAN���ù�����*****************/
	CAN_FilterInit(&CAN_FilterInitStruct);
	
	/****************CAN������Ϣ�ж�*****************/
	CAN_ITConfig(BSP_CANx->CANx,CAN_IT_FMP0,ENABLE);	//FIFO0��Ϣ�Һ��ж�����
	NVIC_InitStructure.NVIC_IRQChannel = CAN_TO_NVIC_IRQChannel(BSP_CANx->CANx);	//CANx�����ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;		//��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;									//�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ��CANx�����ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);	//����
}

/*
***************************************************
��������BSP_CAN_Send_Msg
���ܣ�CAN����һ������
��ڲ�����	BSP_CANx��CAN��
					TxMessage������ָ��
����ֵ��	0���ɹ�;
				1��ʧ��
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
u8 BSP_CAN_Send_Msg(BSP_CAN_TypeDef *BSP_CANx,CanTxMsg *TxMessage){	
  u8 mbox;
  u16 i=0;        
  mbox= CAN_Transmit(BSP_CANx->CANx, TxMessage);   
	
	//�ȴ����ͽ���
  while(CAN_TransmitStatus(BSP_CANx->CANx, mbox)==CAN_TxStatus_Failed){
		i++;	
		if(i>=0xFFF)
			return 1;
	}
  return 0;		
}

/*
***************************************************
��������BSP_CAN_Receive_Msg
���ܣ�CAN����һ������
��ڲ�����	BSP_CANx��CAN��
					RxMessage����������ָ��
����ֵ��	0��������;
				������������
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
u8 BSP_CAN_Receive_Msg(BSP_CAN_TypeDef *BSP_CANx,CanRxMsg *RxMessage){		   		   
	if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)	//û�н��յ�����,ֱ���˳� 
		return 0;		
	CAN_Receive(BSP_CANx->CANx, CAN_FIFO0, RxMessage);//��ȡ����	
	return RxMessage->DLC;	
}
