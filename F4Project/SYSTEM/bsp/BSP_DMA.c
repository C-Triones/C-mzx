#include "BSP_DMA.h"
#include "BSP_DMA_Define.h"

/*
***************************************************
��������BSP_DMA_Init
���ܣ�DMAx�ĸ�ͨ������
��ڲ�����	*BSP_DMA_Streamx_chx��DMA������ͨ���ṹ��ָ��
					par��	�����ַ
					mar��	�洢����ַ
					ndtr�����ݴ����� 
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void BSP_DMA_Init(BSP_DMA_TypeDef *BSP_DMA_Streamx_chx,u32 par,u32 mar,u16 ndtr){
	DMA_InitTypeDef  DMA_InitStructure;
	
	//�õ���ǰstream������DMA2����DMA1
	if((u32)BSP_DMA_Streamx_chx->DMA_Streamx > (u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 	
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
	}
  DMA_DeInit(BSP_DMA_Streamx_chx->DMA_Streamx);
	
	while (DMA_GetCmdStatus(BSP_DMA_Streamx_chx->DMA_Streamx) != DISABLE){
	}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  
	DMA_InitStructure.DMA_Channel = BSP_DMA_Streamx_chx->DMA_channel;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(BSP_DMA_Streamx_chx->DMA_Streamx, &DMA_InitStructure);//��ʼ��DMA Stream
}

void BSP_DMA_DSHOT_Init(BSP_DMA_TypeDef *BSP_DMA_Streamx_chx,u32 par,u32 mar,u16 ndtr){
  DMA_InitTypeDef  DMA_InitStructure;
	//�õ���ǰstream������DMA2����DMA1
	if((u32)BSP_DMA_Streamx_chx->DMA_Streamx > (u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
	}
  DMA_DeInit(BSP_DMA_Streamx_chx->DMA_Streamx);
	
	while (DMA_GetCmdStatus(BSP_DMA_Streamx_chx->DMA_Streamx) != DISABLE){
	}//�ȴ�DMA������ 
	
	 /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = BSP_DMA_Streamx_chx->DMA_channel;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable; 
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݳ���:16λ	
  DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;			//�洢�����ݳ���:16λ		
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�����ȼ�
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(BSP_DMA_Streamx_chx->DMA_Streamx, &DMA_InitStructure);//��ʼ��DMA Stream
	DMA_ITConfig(BSP_DMA_Streamx_chx->DMA_Streamx, DMA_IT_TC, ENABLE);//ʹ��DMA�жϣ����ݴ�����ϴ���	
}

void BSP_DMA_SK6812_Init(BSP_DMA_TypeDef *BSP_DMA_Streamx_chx,u32 par,u32 mar,u16 ndtr){
  DMA_InitTypeDef  DMA_InitStructure;
	//�õ���ǰstream������DMA2����DMA1
	if((u32)BSP_DMA_Streamx_chx->DMA_Streamx > (u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
		
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
	}
  DMA_DeInit(BSP_DMA_Streamx_chx->DMA_Streamx);
	while (DMA_GetCmdStatus(BSP_DMA_Streamx_chx->DMA_Streamx) != DISABLE){
	}//�ȴ�DMA������ 
	
	 /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = BSP_DMA_Streamx_chx->DMA_channel;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable; 
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݳ���:32λ	
  DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;			//�洢�����ݳ���:32λ		
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//�����ȼ�
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(BSP_DMA_Streamx_chx->DMA_Streamx, &DMA_InitStructure);//��ʼ��DMA Stream
	DMA_ITConfig(BSP_DMA_Streamx_chx->DMA_Streamx, DMA_IT_TC, ENABLE);//ʹ��DMA�жϣ����ݴ�����ϴ���	
}

void BSP_DMA_TX_Init(BSP_DMA_TypeDef *BSP_DMA_Streamx_chx,u32 par,u32 mar,u16 ndtr){
	DMA_InitTypeDef  DMA_InitStructure;
	//�õ���ǰstream������DMA2����DMA1
	if((u32)BSP_DMA_Streamx_chx->DMA_Streamx > (u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
		
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
	}
  DMA_DeInit(BSP_DMA_Streamx_chx->DMA_Streamx);
	
	while (DMA_GetCmdStatus(BSP_DMA_Streamx_chx->DMA_Streamx) != DISABLE){
	}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = BSP_DMA_Streamx_chx->DMA_channel;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(BSP_DMA_Streamx_chx->DMA_Streamx, &DMA_InitStructure);//��ʼ��DMA Stream
}

void BSP_DMA_RX_Init(BSP_DMA_TypeDef *BSP_DMA_Streamx_chx,u32 par,u32 mar,u16 ndtr){
	DMA_InitTypeDef  DMA_InitStructure;
	//�õ���ǰstream������DMA2����DMA1
	if((u32)BSP_DMA_Streamx_chx->DMA_Streamx > (u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
		
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
	}
  DMA_DeInit(BSP_DMA_Streamx_chx->DMA_Streamx);
	
	while (DMA_GetCmdStatus(BSP_DMA_Streamx_chx->DMA_Streamx) != DISABLE){
	}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = BSP_DMA_Streamx_chx->DMA_channel;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(BSP_DMA_Streamx_chx->DMA_Streamx, &DMA_InitStructure);//��ʼ��DMA Stream
}

/*
DAM1����ӳ�䣺
-----------------------------------------------------------------------------------------------------------------------------------------
��������	|	 DMA1_Stream0	|	 DMA1_Stream1	|	 DMA1_Stream2	|	 DMA1_Stream3	|	 DMA1_Stream4	|	 DMA1_Stream5	|	 DMA1_Stream6	|	 DMA1_Stream7	|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��0	|    SPI3_RX    |								|			SPI3_RX		|			SPI2_RX		|			SPI2_TX		|			SPI3_TX		|								|		 SPI3_TX		|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��1	|		 I2C1_RX		|								|			TIM7_UP		|								|			TIM7_UP		|    I2C1_RX    |    I2C1_TX    |    I2C1_TX    |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��2	|		 TIM4_CH1	 	|								|  I2S3_EXT_RX  |		 TIM4_CH2	 	|  I2S2_EXT_TX  |  I2S3_EXT_TX  |    TIM4_UP    |    TIM4_CH3   |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��3	|  I2S3_EXT_RX  |	 TIM2_CH3/UP	|		 I2C3_RX		|  I2S2_EXT_RX  |		 I2C3_RX		|    TIM2_CH1   |  TIM2_CH2/CH4 |  TIM2_CH4/UP  |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��4	|		 UART5_RX		|   USART3_RX   |		 UART4_RX		|   USART3_TX   |		 UART4_TX		|   USART2_RX   |   USART2_TX   |    UART5_TX   |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��5	|		 UART8_TX		|    UART7_TX   |	 TIM3_CH4/UP	|    UART7_RX   | TIM3_CH1/TRIG |    TIM3_CH2   |    UART8_RX   |    TIM3_CH3   |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��6	|	 TIM5_CH3/UP	|	TIM5_CH4/TRIG	|		 TIM5_CH1	 	|	TIM5_CH4/TRIG	|		 TIM5_CH2	 	|								|    TIM5_UP    |								|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��7	|								|    TIM6_UP    |		 I2C2_RX		|		 I2C2_RX		|   USART3_TX   |      DAC1     |      DAC2     |		 I2C2_TX		|
-----------------------------------------------------------------------------------------------------------------------------------------

DMA2����ӳ�䣺
-----------------------------------------------------------------------------------------------------------------------------------------
��������	|	 DMA2_Stream0	|	 DMA2_Stream1	|	 DMA2_Stream2	|	 DMA2_Stream3	|	 DMA2_Stream4	|	 DMA2_Stream5	|	 DMA2_Stream6	|	 DMA2_Stream7	|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��0	|     ADC1      |								| TIM8_CH1/2/3  |								|     ADC1      |								| TIM1_CH1/2/3  |								|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��1	|								|     DCMI      |      ADC2     |      ADC2     |								|    SPI6_TX    |    SPI6_RX    |      DCMI     |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��2	|		  ADC3  	 	|		  ADC3  	 	|								|		 SPI5_RX	 	|    SPI5_TX    |    CRYP_OUT   |    CRYP_IN    |     HASH_IN   |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��3	|    SPI1_RX    |								|		 SPI1_RX		|    SPI1_TX    |								|    SPI1_TX    |								|								|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��4	|		 SPI4_RX 		|    SPI4_TX    |	  USART1_RX 	|      SDIO     |								|   USART1_RX   |      SDIO     |   USART1_TX   |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��5	|								|   USART6_RX   |	  USART6_RX 	|    SPI4_RX    |    SPI4_TX    |								|   USART6_TX   |   USART6_TX   |
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��6	|	  TIM1_TRIG 	|    TIM1_CH1   |		 TIM1_CH2	 	|	   TIM1_CH1   |TIM1C4/TRIG/COM|    TIM1_UP    |    TIM1_CH3   |								|
-----------------------------------------------------------------------------------------------------------------------------------------
 ͨ��7	|								|    TIM8_UP    |		 TIM8_CH1  	|		 TIM8_CH2		|		 TIM8_CH3		|    SPI5_RX    |    SPI5_TX    |TIM8C4/TRIG/COM|
-----------------------------------------------------------------------------------------------------------------------------------------

*/
