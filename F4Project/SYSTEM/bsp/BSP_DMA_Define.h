#ifndef __BSP_DMA_DEFINE_H
#define __BSP_DMA_DEFINE_H

#include "BSP_DMA.h"

/************************ DMA1_Stream0 ************************/
BSP_DMA_TypeDef BSP_DMA_SPI3_RX 		= {DMA1_Stream0, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_I2C1_RX 		= {DMA1_Stream0, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_TIM4_CH1 		= {DMA1_Stream0, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_I2S3_EXT_RX	= {DMA1_Stream0, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_UART5_RX 		= {DMA1_Stream0, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_UART8_TX 		= {DMA1_Stream0, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM5_CH3 		= {DMA1_Stream0, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_TIM5_UP 		= {DMA1_Stream0, DMA_Channel_6};

/************************ DMA1_Stream1 ************************/
BSP_DMA_TypeDef BSP_DMA_TIM2_CH3 		= {DMA1_Stream1, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_TIM2_UP 		= {DMA1_Stream1, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_USART3_RX 	= {DMA1_Stream1, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_UART7_TX 		= {DMA1_Stream1, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM5_CH4 		= {DMA1_Stream1, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_TIM5_TRIG		= {DMA1_Stream1, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_TIM6_UP 		= {DMA1_Stream1, DMA_Channel_7};

/************************ DMA1_Stream2 ************************/
BSP_DMA_TypeDef BSP_DMA1_SPI3_RX 		= {DMA1_Stream2, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_TIM7_UP 		= {DMA1_Stream2, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA1_I2S3_EXT_RX= {DMA1_Stream2, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_I2C3_RX			= {DMA1_Stream2, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_UART4_RX 		= {DMA1_Stream2, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_TIM3_CH4 		= {DMA1_Stream2, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM3_UP 		= {DMA1_Stream2, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM5_CH1 		= {DMA1_Stream2, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_I2C2_RX 		= {DMA1_Stream2, DMA_Channel_7};

/************************ DMA1_Stream3 ************************/
BSP_DMA_TypeDef BSP_DMA_SPI2_RX 		= {DMA1_Stream3, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_TIM4_CH2		= {DMA1_Stream3, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_I2S2_EXT_RX	= {DMA1_Stream3, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_USART3_TX		= {DMA1_Stream3, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_UART7_RX 		= {DMA1_Stream3, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA1_TIM5_CH4 	= {DMA1_Stream3, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_TIM5_TRIG	= {DMA1_Stream3, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_I2C2_RX 		= {DMA1_Stream3, DMA_Channel_7};

/************************ DMA1_Stream4 ************************/
BSP_DMA_TypeDef BSP_DMA_SPI2_TX 		= {DMA1_Stream4, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA1_TIM7_UP 		= {DMA1_Stream4, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_I2S2_EXT_TX	= {DMA1_Stream4, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_I2C3_TX			= {DMA1_Stream4, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_UART4_TX 		= {DMA1_Stream4, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_TIM3_CH1 		= {DMA1_Stream4, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM3_TRIG		= {DMA1_Stream4, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM5_CH2 		= {DMA1_Stream4, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_USART3_TX	= {DMA1_Stream4, DMA_Channel_7};

/************************ DMA1_Stream5 ************************/
BSP_DMA_TypeDef BSP_DMA_SPI3_TX 		= {DMA1_Stream5, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA1_I2C1_RX 		= {DMA1_Stream5, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_I2S3_EXT_TX	= {DMA1_Stream5, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_TIM2_CH1		= {DMA1_Stream5, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_USART2_RX		= {DMA1_Stream5, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_TIM3_CH2		= {DMA1_Stream5, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_DAC1				= {DMA1_Stream5, DMA_Channel_7};

/************************ DMA1_Stream6 ************************/
BSP_DMA_TypeDef BSP_DMA_I2C1_TX 		= {DMA1_Stream6, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_TIM4_UP			= {DMA1_Stream6, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_TIM2_CH2		= {DMA1_Stream6, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_TIM2_CH4		= {DMA1_Stream6, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_USART2_TX		= {DMA1_Stream6, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_UART8_RX 		= {DMA1_Stream6, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA1_TIM5_UP 		= {DMA1_Stream6, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_DAC2				= {DMA1_Stream6, DMA_Channel_7};

/************************ DMA1_Stream7 ************************/
BSP_DMA_TypeDef BSP_DMA1_SPI3_TX 		= {DMA1_Stream7, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA1_I2C1_TX 		= {DMA1_Stream7, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_TIM4_CH3		= {DMA1_Stream7, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA1_TIM2_CH4		= {DMA1_Stream7, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA1_TIM2_UP		= {DMA1_Stream7, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_UART5_TX 	= {DMA1_Stream7, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_TIM3_CH3 		= {DMA1_Stream7, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_I2C2_TX			= {DMA1_Stream7, DMA_Channel_7};

/***************************************************************************************/
/***************************************************************************************/

/************************ DMA2_Stream0 ************************/
BSP_DMA_TypeDef BSP_DMA_ADC1		 		= {DMA2_Stream0, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_ADC3 				= {DMA2_Stream0, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_SPI1_RX			= {DMA2_Stream0, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_SPI4_RX 		= {DMA2_Stream0, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_TIM1_TRIG		= {DMA2_Stream0, DMA_Channel_6};

/************************ DMA2_Stream1 ************************/
BSP_DMA_TypeDef BSP_DMA_DCMI 				= {DMA2_Stream1, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA1_ADC3		 		= {DMA2_Stream1, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_SPI4_TX		 	= {DMA2_Stream1, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_USART6_RX		= {DMA2_Stream1, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM1_CH1		= {DMA2_Stream1, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_TIM8_UP 		= {DMA2_Stream1, DMA_Channel_7};

/************************ DMA2_Stream2 ************************/
BSP_DMA_TypeDef BSP_DMA_TIM8_CH1 		= {DMA2_Stream2, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_TIM8_CH2 		= {DMA2_Stream2, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_TIM8_CH3 		= {DMA2_Stream2, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_ADC2		 		= {DMA2_Stream2, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA1_SPI1_RX		= {DMA2_Stream2, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_USART1_RX		= {DMA2_Stream2, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA1_USART6_RX	= {DMA2_Stream2, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM1_CH2 		= {DMA2_Stream2, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_TIM8_CH1 	= {DMA2_Stream2, DMA_Channel_7};

/************************ DMA2_Stream3 ************************/
BSP_DMA_TypeDef BSP_DMA1_ADC2		 		= {DMA2_Stream3, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_SPI5_RX			= {DMA2_Stream3, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_SPI1_TX			= {DMA2_Stream3, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA_SDIO				= {DMA2_Stream3, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA1_SPI4_RX 		= {DMA2_Stream3, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA1_TIM1_CH1 	= {DMA2_Stream3, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_TIM8_CH2		= {DMA2_Stream3, DMA_Channel_7};

/************************ DMA2_Stream4 ************************/
BSP_DMA_TypeDef BSP_DMA1_ADC1		 		= {DMA2_Stream4, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_SPI5_TX			= {DMA2_Stream4, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA1_SPI4_TX 		= {DMA2_Stream4, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM1_CH4		= {DMA2_Stream4, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_TIM1_TRIG	= {DMA2_Stream4, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA_TIM1_COM 		= {DMA2_Stream4, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_TIM8_CH3		= {DMA2_Stream4, DMA_Channel_7};

/************************ DMA2_Stream5 ************************/
BSP_DMA_TypeDef BSP_DMA_SPI6_TX 		= {DMA2_Stream5, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_CRYP_OUT		= {DMA2_Stream5, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA2_SPI1_RX		= {DMA2_Stream5, DMA_Channel_3};
BSP_DMA_TypeDef BSP_DMA1_USART1_RX	= {DMA2_Stream5, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_TIM1_UP			= {DMA2_Stream5, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_SPI5_RX		= {DMA2_Stream5, DMA_Channel_7};

/************************ DMA2_Stream6 ************************/
BSP_DMA_TypeDef BSP_DMA2_TIM1_CH1 	= {DMA2_Stream6, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA1_TIM1_CH2 	= {DMA2_Stream6, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_TIM1_CH3 		= {DMA2_Stream6, DMA_Channel_0};
BSP_DMA_TypeDef BSP_DMA_SPI6_RX 		= {DMA2_Stream6, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_CRYP_IN			= {DMA2_Stream6, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA1_SDIO				= {DMA2_Stream6, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA_USART6_TX		= {DMA2_Stream6, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA1_TIM1_CH3		= {DMA2_Stream6, DMA_Channel_6};
BSP_DMA_TypeDef BSP_DMA1_SPI5_TX		= {DMA2_Stream6, DMA_Channel_7};

/************************ DMA2_Stream7 ************************/
BSP_DMA_TypeDef BSP_DMA1_DCMI		 		= {DMA2_Stream7, DMA_Channel_1};
BSP_DMA_TypeDef BSP_DMA_HASH_IN			= {DMA2_Stream7, DMA_Channel_2};
BSP_DMA_TypeDef BSP_DMA_USART1_TX 	= {DMA2_Stream7, DMA_Channel_4};
BSP_DMA_TypeDef BSP_DMA1_USART6_TX 	= {DMA2_Stream7, DMA_Channel_5};
BSP_DMA_TypeDef BSP_DMA_TIM8_CH4		= {DMA2_Stream7, DMA_Channel_7};
BSP_DMA_TypeDef BSP_DMA_TIM8_TRIG		= {DMA2_Stream7, DMA_Channel_7};
BSP_DMA_TypeDef BSP_DMA_TIM8_COM		= {DMA2_Stream7, DMA_Channel_7};

/*
DAM1请求映射：
-----------------------------------------------------------------------------------------------------------------------------------------
外设请求	|	 DMA1_Stream0	|	 DMA1_Stream1	|	 DMA1_Stream2	|	 DMA1_Stream3	|	 DMA1_Stream4	|	 DMA1_Stream5	|	 DMA1_Stream6	|	 DMA1_Stream7	|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道0	|    SPI3_RX    |								|			SPI3_RX		|			SPI2_RX		|			SPI2_TX		|			SPI3_TX		|								|		 SPI3_TX		|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道1	|		 I2C1_RX		|								|			TIM7_UP		|								|			TIM7_UP		|    I2C1_RX    |    I2C1_TX    |    I2C1_TX    |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道2	|		 TIM4_CH1	 	|								|  I2S3_EXT_RX  |		 TIM4_CH2	 	|  I2S2_EXT_TX  |  I2S3_EXT_TX  |    TIM4_UP    |    TIM4_CH3   |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道3	|  I2S3_EXT_RX  |	 TIM2_CH3/UP	|		 I2C3_RX		|  I2S2_EXT_RX  |		 I2C3_RX		|    TIM2_CH1   |  TIM2_CH2/CH4 |  TIM2_CH4/UP  |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道4	|		 UART5_RX		|   USART3_RX   |		 UART4_RX		|   USART3_TX   |		 UART4_TX		|   USART2_RX   |   USART2_TX   |   USART5_TX   |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道5	|		 UART8_TX		|    UART7_TX   |	 TIM3_CH4/UP	|    UART7_RX   | TIM3_CH1/TRIG |    TIM3_CH2   |    UART8_RX   |    TIM3_CH3   |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道6	|	 TIM5_CH3/UP	|	TIM5_CH4/TRIG	|		 TIM5_CH1	 	|	TIM5_CH4/TRIG	|		 TIM5_CH2	 	|								|    TIM5_UP    |								|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道7	|								|    TIM6_UP    |		 I2C2_RX		|		 I2C2_RX		|   USART3_TX   |      DAC1     |      DAC2     |		 I2C2_TX		|
-----------------------------------------------------------------------------------------------------------------------------------------

DMA2请求映射：
-----------------------------------------------------------------------------------------------------------------------------------------
外设请求	|	 DMA2_Stream0	|	 DMA2_Stream1	|	 DMA2_Stream2	|	 DMA2_Stream3	|	 DMA2_Stream4	|	 DMA2_Stream5	|	 DMA2_Stream6	|	 DMA2_Stream7	|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道0	|     ADC1      |								| TIM8_CH1/2/3  |								|     ADC1      |								| TIM1_CH1/2/3  |								|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道1	|								|     DCMI      |      ADC2     |      ADC2     |								|    SPI6_TX    |    SPI6_RX    |      DCMI     |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道2	|		  ADC3  	 	|		  ADC3  	 	|								|		 SPI5_RX	 	|    SPI5_TX    |    CRYP_OUT   |    CRYP_IN    |     HASH_IN   |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道3	|    SPI1_RX    |								|		 SPI1_RX		|    SPI1_TX    |								|    SPI1_TX    |								|								|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道4	|		 SPI4_RX 		|    SPI4_TX    |	  USART1_RX 	|      SDIO     |								|   USART1_RX   |      SDIO     |   USART1_TX   |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道5	|								|   USART6_RX   |	  USART6_RX 	|    SPI4_RX    |    SPI4_TX    |								|   USART6_TX   |   USART6_TX   |
-----------------------------------------------------------------------------------------------------------------------------------------
 通道6	|	  TIM1_TRIG 	|    TIM1_CH1   |		 TIM1_CH2	 	|	   TIM1_CH1   |TIM1C4/TRIG/COM|    TIM1_UP    |    TIM1_CH3   |								|
-----------------------------------------------------------------------------------------------------------------------------------------
 通道7	|								|    TIM8_UP    |		 TIM8_CH1  	|		 TIM8_CH2		|		 TIM8_CH3		|    SPI5_RX    |    SPI5_TX    |TIM8C4/TRIG/COM|
-----------------------------------------------------------------------------------------------------------------------------------------

*/
#endif
