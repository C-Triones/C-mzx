#include "HJ_USART.h"
#include "app.h"
void wifi_Init(void){
GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = WIFI_BAUD;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}

void wifiControl(uint8_t command){
		switch(command){ 
		case RESCUE_STOP:{    //���ж��ֹͣ
			app_LeftWheel(FRONT,0);
			app_RightWheel(FRONT,0);
			break;
		}
		case RESCUE_FORWARD :  //ǰ1	
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
		case RESCUE_BACK :    //��2
											app_LeftWheel(BEHIND,parameter[NAME_GO_STRAIGHT__LEFT_RATE]);
											app_RightWheel(BEHIND,parameter[NAME_GO_STRAIGHT__RIGHT_RATE]);
			break;
		case RESCUE_LEFT :    //��3
			              if(LimiFlag.left){ 
										 app_LeftWheel(BEHIND,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE]);	
										 app_RightWheel(FRONT,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE]);
			                }
				            if( LimiFlag.left==stop){
		                  app_LeftWheel(FRONT,0);
		                  app_RightWheel(FRONT,0);
			                } 
	
			break;
		case RESCUE_RIGHT :   //��4 
										 if(LimiFlag.right){			
											 app_LeftWheel(FRONT,parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE]);				
											 app_RightWheel(BEHIND,parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE]);
										 }
			              if(LimiFlag.right==stop){
		                  app_LeftWheel(FRONT,0);
		                  app_RightWheel(FRONT,0);
		                  } 
			break;
		case CLAW_UP :        //צ���ſ��Զ�����5
		rescue_AUTOTASK_PUTCLAW();
			break;
		case CLAW_DOWN :     //צ��ץȡ�Զ�����6
		rescue_AUTOTASK_HOLDCLAW();
			break;
		case CLAW_HOLD :     //Ѱ��ʱ���λ��7
			app_CAMERA_UPorDOWN(camera_DOWN,150);
			break;
		case 0x38 : /////���������Զ��س�
//			app_CAMERA_UPorDOWN(camera_DOWN,90);	
		rescueRobotState.rescueTaskstep = DRIVER_INDEEP;
		 break;
		default:
		break;
	}
}
