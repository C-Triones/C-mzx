#include "HJ_USART.h"
#include "app.h"
void wifi_Init(void){
GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = WIFI_BAUD;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}

void wifiControl(uint8_t command){
		switch(command){ 
		case RESCUE_STOP:{    //所有舵机停止
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			break;
		}
		case RESCUE_FORWARD :  //前1	
                   if(LimiFlag.forward){	 
										 if(speed_cut){			
	                    app_LeftWheel(FRONT,0.3*parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
	                    app_RightWheel(FRONT,0.3*parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
		                 }
                      else{										 
	                    app_LeftWheel(FRONT,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
	                    app_RightWheel(FRONT,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
											}
		                 }
									 if(LimiFlag.forward==stop){
	                    app_LeftWheel(FRONT,0);
		                  app_RightWheel(FRONT,0);
		                  } 	                								  
			break;
		case RESCUE_BACK :    //后2
											app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
											app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
			break;
		case RESCUE_LEFT :    //左3
			              if(LimiFlag.left){ 
										 app_LeftWheel(BEHIND,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE]);	
										 app_RightWheel(FRONT,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE]);
			                }
				            if( LimiFlag.left==stop){
		                  app_LeftWheel(FRONT,0);
		                  app_RightWheel(FRONT,0);
			                } 
	
			break;
		case RESCUE_RIGHT :   //右4 
										 if(LimiFlag.right){			
											 app_LeftWheel(FRONT,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE]);				
											 app_RightWheel(BEHIND,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE]);
										 }
			              if(LimiFlag.right==stop){
		                  app_LeftWheel(FRONT,0);
		                  app_RightWheel(FRONT,0);
		                  } 
			break;
		case CLAW_UP :        //爪子张开自动任务5
		rescue_AUTOTASK_PUTCLAW();
			break;
		case CLAW_DOWN :     //爪子抓取自动任务6
		rescue_AUTOTASK_HOLDCLAW();
			break;
		case CLAW_HOLD :     //寻物时相机位置7
			app_CAMERA_UPorDOWN(camera_DOWN,150);
			break;
		case 0x38 : /////用来控制自动回城
//			app_CAMERA_UPorDOWN(camera_DOWN,90);	
		rescueRobotState.rescueTaskstep = DRIVER_INDEEP;
		 break;
		default:
		break;
	}
}
