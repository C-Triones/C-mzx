#include "BSP_CAN.h"

/******************************外部调用函数************************************/
void BSP_CAN_Mode_Init(BSP_CAN_TypeDef *BSP_CANx,u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u8 PreemptionPriority,u8 SubPriority);
 u8	 BSP_CAN_Send_Msg(BSP_CAN_TypeDef *BSP_CANx,CanTxMsg *TxMessage);
 u8	 BSP_CAN_Receive_Msg(BSP_CAN_TypeDef *BSP_CANx,CanRxMsg *RxMessage);
/*****************************************************************************/

const CAN_FilterInitTypeDef  CAN1_FilterInitStructure = {
	.CAN_FilterNumber = 0,										/*过滤器0*/					
	.CAN_FilterMode = CAN_FilterMode_IdMask,	/*标识符屏蔽位模式*/	
	.CAN_FilterScale = CAN_FilterScale_32bit,	/*32位的模式*/				
	.CAN_FilterIdHigh = 0x0000,								/*32位MASK*/				
	.CAN_FilterIdLow = 0x0000,
	.CAN_FilterMaskIdHigh = 0x0000,
	.CAN_FilterMaskIdLow = 0x0000,
	.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0,	/*过滤器0关联到FIFO0*/	
	.CAN_FilterActivation = ENABLE,								/*激活过滤器*/					
};

const CAN_FilterInitTypeDef  CAN2_FilterInitStructure = {
	.CAN_FilterNumber = 14,										/*过滤器0*/					
	.CAN_FilterMode = CAN_FilterMode_IdMask,	/*标识符屏蔽位模式*/	
	.CAN_FilterScale = CAN_FilterScale_32bit,	/*32位的模式*/				
	.CAN_FilterIdHigh = 0x0000,								/*32位MASK*/				
	.CAN_FilterIdLow = 0x0000,
	.CAN_FilterMaskIdHigh = 0x0000,
	.CAN_FilterMaskIdLow = 0x0000,
	.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0,	/*过滤器0关联到FIFO0*/	
	.CAN_FilterActivation = ENABLE,								/*激活过滤器*/					
};

/*
***************************************************
函数名：BSP_SPI_RCBSP_CAN_RCC_InitC_Init
功能：配置CAN外设时钟
入口参数：	CANx：CAN号
返回值：无
应用范围：内部调用
备注：
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
函数名：CANx_TO_GPIO_AF
功能：从CAN号输出GPIO_AF
入口参数：	CANx：CAN号
返回值：GPIO_AF:复用的CAN模式
应用范围：内部调用
备注：
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
函数名：GPIO_TO_NVIC_IRQChannel
功能：输出NVIC中断通道
入口参数：	GPIO：引脚号
返回值：NVIC_IRQChannel
应用范围：内部调用
备注：
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
函数名：BSP_CAN_Mode_Init
功能：CAN初始化
入口参数：	BSP_CANx：CAN号
					tsjw：重新同步跳跃时间单元.范围:CAN_SJW_1tq~ CAN_SJW_4tq
					tbs2：时间段2的时间单元.   范围:CAN_BS2_1tq~CAN_BS2_8tq;
					tbs1：时间段1的时间单元.   范围:CAN_BS1_1tq ~CAN_BS1_16tq
					brp ：波特率分频器.				范围:1~1024; tq=(brp)*tpclk1
					mode：CANx模式							范围:CAN_Mode_Normal,普通模式;CAN_Mode_LoopBack,回环模式;
					PreemptionPriority：抢占优先级
					SubPriority：子优先级
返回值：无
应用范围：外部调用
备注：已解决初始化CAN2必须先初始化CAN1
***************************************************
*/
void BSP_CAN_Mode_Init(BSP_CAN_TypeDef *BSP_CANx,u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u8 PreemptionPriority,u8 SubPriority){
	CAN_InitTypeDef		CAN_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	
	CAN_FilterInitStruct = BSP_CANx->CAN_FilterInitStructure;
	
	/*************初始化CANx时钟***************/
	BSP_CAN_RCC_Init(BSP_CANx->CANx);
	
	/*************初始化CANx引脚***************/
	BSP_GPIO_Init(BSP_CANx->CANx_RX,GPIO_Mode_AF_PP);	//初始化CANx_RX引脚为复用推挽
	BSP_GPIO_Init(BSP_CANx->CANx_TX,GPIO_Mode_AF_PP);	//初始化CANx_TX引脚为复用推挽
	
	/*************引脚复用映射配置***************/
	GPIO_Pin_TO_PinAFConfig(BSP_CANx->CANx_RX,CANx_TO_GPIO_AF(BSP_CANx->CANx));	//CANx_RX引脚复用为 CANx
	GPIO_Pin_TO_PinAFConfig(BSP_CANx->CANx_TX,CANx_TO_GPIO_AF(BSP_CANx->CANx));	//CANx_TX引脚复用为 CANx
	
	/****************CAN单元设置*****************/
	CAN_InitStructure.CAN_TTCM=DISABLE;		//非时间触发通信模式   
	CAN_InitStructure.CAN_ABOM=ENABLE;		//软件自动离线管理	  
	CAN_InitStructure.CAN_AWUM=DISABLE;		//睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART=DISABLE;		//禁止报文自动传送 
	CAN_InitStructure.CAN_RFLM=DISABLE;		//报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP=DISABLE;		//优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode= mode;	 		//模式设置 
	CAN_InitStructure.CAN_SJW=tsjw;				//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=tbs1; 			//Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=tbs2;				//Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=brp;  //分频系数(Fdiv)为brp+1	
	CAN_Init(BSP_CANx->CANx, &CAN_InitStructure);   // 初始化CANx 
	
	/****************CAN配置过滤器*****************/
	CAN_FilterInit(&CAN_FilterInitStruct);
	
	/****************CAN配置消息中断*****************/
	CAN_ITConfig(BSP_CANx->CANx,CAN_IT_FMP0,ENABLE);	//FIFO0消息挂号中断允许
	NVIC_InitStructure.NVIC_IRQChannel = CAN_TO_NVIC_IRQChannel(BSP_CANx->CANx);	//CANx接收中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;		//抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;									//子优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能CANx接收中断通道
  NVIC_Init(&NVIC_InitStructure);	//配置
}

/*
***************************************************
函数名：BSP_CAN_Send_Msg
功能：CAN发送一组数据
入口参数：	BSP_CANx：CAN号
					TxMessage：数据指针
返回值：	0：成功;
				1：失败
应用范围：外部调用
备注：
***************************************************
*/
u8 BSP_CAN_Send_Msg(BSP_CAN_TypeDef *BSP_CANx,CanTxMsg *TxMessage){	
  u8 mbox;
  u16 i=0;        
  mbox= CAN_Transmit(BSP_CANx->CANx, TxMessage);   
	
	//等待发送结束
  while(CAN_TransmitStatus(BSP_CANx->CANx, mbox)==CAN_TxStatus_Failed){
		i++;	
		if(i>=0xFFF)
			return 1;
	}
  return 0;		
}

/*
***************************************************
函数名：BSP_CAN_Receive_Msg
功能：CAN发送一组数据
入口参数：	BSP_CANx：CAN号
					RxMessage：接收数据指针
返回值：	0：无数据;
				其它：有数据
应用范围：外部调用
备注：
***************************************************
*/
u8 BSP_CAN_Receive_Msg(BSP_CAN_TypeDef *BSP_CANx,CanRxMsg *RxMessage){		   		   
	if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)	//没有接收到数据,直接退出 
		return 0;		
	CAN_Receive(BSP_CANx->CANx, CAN_FIFO0, RxMessage);//读取数据	
	return RxMessage->DLC;	
}
