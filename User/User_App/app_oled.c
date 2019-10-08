#include "app.h"

oledMenuStruct_t mainMenu;
oledMenuStruct_t testMenu,workMENU;		       //���˵����Ӳ˵�


oledMenuStruct_t *currentMenu;	 //��ǰ�˵�


/*
***************************************************
��������menuReset
���ܣ��˻ظ��˵�ʱ���ø��˵�
��ڲ�����	*menu
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void menuReset(menuStruct_t* menu)
{
	if(menu -> preMenu != NULL)
	{
		menu -> showFrom = 0;
		menu -> showTo = 3;
		menu -> currentOption = 0;
	}	
}

/*
***************************************************
��������OLEDKeyNoReset
���ܣ����㰴������ʱ��
��ڲ�����	noReset������Ҫ����İ���ʱ��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void OLEDKeyNoReset(uint8_t noReset)
{
	uint8_t i = 0;
	for(i = 0;i < OLED_KEY_LIST;i++){
		/*����ָ���İ���ʱ��������ȫ����*/
		if(i != noReset){
			digitalClan(&GUI.waitKeyTime[i]);
		}
	}
}
/*
***************************************************
��������nullHandle
���ܣ����ް�������ʱִ�еĲ���
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void nullHandle()
{
	/*ֻ���ް�������ʱ�����200ms���������а�������ʱ��*/
	if(GUI.waitKeyTime[OLED_NULL] < 2){
	digitalIncreasing(&GUI.waitKeyTime[OLED_NULL]);
	}
	else{
		OLEDKeyNoReset(OLED_ALL_NEED);
	}
}
/*
***************************************************
��������enterOn
���ܣ�����������ΪENTER��ʱִ�е�ʵ�ʲ���
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void enterOn()
{
	/*�����Ӳ˵�*/
	if(currentMenu -> subMenu[currentMenu -> currentOption] != NULL ){
		/*�����Ӳ˵�*/
		currentMenu = currentMenu -> subMenu[currentMenu->currentOption];
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
	}
	/*���ڿ�ִ�еĲ˵�����*/
	else if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
		/*ִ�в˵�����*/
		currentMenu -> func[currentMenu -> currentOption]();
		currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
	}
}
/*
***************************************************
��������enterHandle
���ܣ�����������ΪENTER��ʱִ�еı�ʶ����
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void enterHandle()
{
	/*�������ENTER���������ֵ����ʱ��*/
	OLEDKeyNoReset(OLED_ENTER);
	/*������ڲ˵�������*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*��ִ��һ�β���*/
		if(!GUI.waitKeyTime[OLED_ENTER]){
			enterOn();
		}
		/*һ��ʱ�����������*/
		else if(GUI.waitKeyTime[OLED_ENTER] > WAITTING_NEXT_TIME){
			if(!(GUI.waitKeyTime[OLED_ENTER] % NEXT_TIME_PERIOD)){
				enterOn();
			}
		} 
	}
	/*����ڲ˵�������*/
	else{
		enterOn();
	}
	/*����ʱ���Լ�*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_ENTER]);
}
/*
***************************************************
��������upHandle
���ܣ�����������ΪUP��ʱִ�еı�ʶ����
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void upHandle()
{
	/*�������UP���������ֵ����ʱ��*/
	OLEDKeyNoReset(OLED_UP);
	/*������ڲ˵�������*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*�˵�ѡ��û����ͷ��ѡ��ѡ������һ��ѡ��*/
		if(currentMenu -> currentOption != 0){
			currentMenu -> currentOption--;
			if(currentMenu -> currentOption < currentMenu -> showFrom){
				currentMenu -> showFrom--;
				currentMenu -> showTo--;
			}
		}
		/*���²˵�*/
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
		GUI.workState = GUI_CHOOSE;
	}
	/*����ڲ˵�������*/
	else{
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*����ʱ���Լ�*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_UP]);
}
/*
***************************************************
��������downHandle
���ܣ�����������ΪDOWN��ʱִ�еı�ʶ����
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void downHandle()
{
	/*�������DOWN���������ֵ����ʱ��*/
	OLEDKeyNoReset(OLED_DOWN);
	/*������ڲ˵�������*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*�˵�ѡ��û���ײ���ѡ��ѡ������һ��ѡ��*/
		if(currentMenu -> currentOption != currentMenu -> subMenuNumber - 1)
		{
			currentMenu -> currentOption++;
			if(currentMenu -> currentOption > currentMenu -> showTo)
			{
				currentMenu -> showTo++;
				currentMenu -> showFrom++;
			}
		}
		/*���²˵�*/
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
		GUI.workState = GUI_CHOOSE;
	}
	/*����ڲ˵�������*/
	else{
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*����ʱ���Լ�*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_DOWN]);
}
/*
***************************************************
��������backOn
���ܣ�����������ΪBACK��ʱִ�е�ʵ�ʲ���
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void backOn()
{
	/*���ڸ��˵�*/
	if(currentMenu ->preMenu != NULL){
		/*���ظ��˵�*/
		menuReset(currentMenu);
		currentMenu = currentMenu ->preMenu;
	}
	/*���ø�У׼״̬*/
	resetGUIState();
}
/*
***************************************************
��������backOn
���ܣ�����������ΪBACK��ʱִ�еı�ʶ����
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void backHandle()
{
	/*�������BACK���������ֵ����ʱ��*/
	OLEDKeyNoReset(OLED_BACK);
	/*������ڲ˵�������*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*��ִ��һ�β���*/
		if(!GUI.waitKeyTime[OLED_BACK]){
			backOn();
		}
		/*һ��ʱ�����������*/
		else if(GUI.waitKeyTime[OLED_BACK] > WAITTING_NEXT_TIME){
			if(!(GUI.waitKeyTime[OLED_BACK] % NEXT_TIME_PERIOD)){
				backOn();
			}	
		}
	}
	/*����ڲ˵�������*/
	else{
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*����ʱ���Լ�*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_BACK]);
}
/*
***************************************************
��������saveHandle
���ܣ�����������ΪSAVE��ʱִ�еı�ʶ����
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
static void saveHandle()
{
	/*�������BACK���������ֵ����ʱ��*/
	OLEDKeyNoReset(OLED_SAVE);
	/*����ʱ��500ms*/
	if(GUI.waitKeyTime[OLED_SAVE] == 5){
		/*���뱣���У׼*/
		GUI.workState = GUI_SAVE_BEING;
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*����ʱ��6s*/
	else if(GUI.waitKeyTime[OLED_SAVE] == 60){
		/*���³�ʼ��OLED,���������*/
		OLED_Init();
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
	}
	/*����ʱ���Լ�*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_SAVE]);
	
}
/*
***************************************************
��������menuUpdate
���ܣ��˵�����
��ڲ�����	��
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void menuUpdate()
{
	u8 i = 0;	
  /*��ȡ����*/	
	OLED_ADKeyScan();
	switch(oled.keyValue)
	{
		case OLED_NULL:   nullHandle(); break;
		case OLED_ENTER:	enterHandle();break;
		case OLED_UP:		  upHandle();		break;
		case OLED_DOWN:  	downHandle();	break;
		case OLED_BACK:  	backHandle();	break;
		case OLED_SAVE:	  saveHandle();	break;
		default:									break;
	}
	/*oled����ģʽ*/
	switch(currentMenu -> displayFlag){
		/*ˢ�²˵�ģʽ*/
		case UPDATEMENU_FLAG:{
			OLED_Clear();
			OLED_ShowChar(120,(currentMenu -> currentOption - currentMenu -> showFrom) * 2,'*');
			for(i=0;i<4;++i)
			{
				OLED_ShowString(2,i * 2,currentMenu -> menuOption[i + currentMenu -> showFrom]);
				if( i == currentMenu -> subMenuNumber - 1 )			//����˵�ѡ����ĸ�������ѭ��~
					break;
			}
			currentMenu -> displayFlag = NO_FLAG;							//���ˢ����ʾ��־λ~
			break;
		}
		/*�������ģʽ*/
		case ERRORSAVE_FLAG:{
			if(GUI.updateTime>0&&GUI.updateTime<10)	{			//ֻˢ��һ��~
				if(supervisorData.busyState && RC_RELAX && parameterRunData.TFInsertState == TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,2,"Wait Busy Over");
				}
				else if(!supervisorData.busyState && !RC_RELAX && parameterRunData.TFInsertState == TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,2,"RELAX RC !");
				}
				else if(supervisorData.busyState && RC_RELAX && parameterRunData.TFInsertState != TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,2,"NO TF Card");
				}
				
				else if(supervisorData.busyState && !RC_RELAX && parameterRunData.TFInsertState == TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,2,"RELAX RC !");
					OLED_ShowString(20,4,"Wait Busy Over");
				}
				else if(supervisorData.busyState && RC_RELAX && parameterRunData.TFInsertState != TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,2,"Wait Busy Over");
					OLED_ShowString(20,4,"NO TF Card");		
				}
				else if(!supervisorData.busyState && !RC_RELAX && parameterRunData.TFInsertState != TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,2,"RELAX RC !");
					OLED_ShowString(20,4,"NO TF Card");		
				}
				
				else if(supervisorData.busyState && !RC_RELAX && parameterRunData.TFInsertState != TFCARD_INSERT){
					OLED_Clear();
					OLED_ShowString(20,0,"RELAX RC !");
					OLED_ShowString(20,2,"Wait Busy Over");
					OLED_ShowString(20,4,"NO TF Card");
				}
				
				digitalIncreasing(&GUI.updateTime);
			}	
			else{
				digitalIncreasing(&GUI.updateTime);
				if(GUI.updateTime >= 20&& GUI.updateTime < 22){
					OLED_Init();
				}
				if( GUI.updateTime >= 21){
					GUI.updateTime = 0;
					GUI.alterType = GUI_NO_NEED_ALTER;
					GUI.workState = GUI_NO_NEED_SAVE;
					currentMenu -> displayFlag = UPDATEMENU_FLAG;
					digitalClan(&GUI.updateTime);
				}
			}
			break;
	  }
		/*�Զ�ˢ��ģʽ*/
		case FUNCTION_AUTO_FLAG:{
			OLED_Clear();
			for(i=0;i<4;++i)
			{
				OLED_ShowString(0,i * 2,currentMenu -> menuOption[i + currentMenu -> showFrom]);
				if( i == currentMenu -> subMenuNumber - 1 )			//����˵�ѡ����ĸ�������ѭ��~
					break;
			}
			currentMenu -> func[currentMenu -> currentOption]();
			break;
		}
	  /*����ģʽ*/
		case FLASH_SAVE_FLAG:{
			if(GUI.updateTime>0&&GUI.updateTime<10)				//ֻˢ��һ��~
			{
				OLED_Clear();
				OLED_ShowString(20,2,"Save");
				OLED_ShowString(36,4,"Being");					

				digitalIncreasing(&GUI.updateTime);
			}
			else{ 
				if(GUI.updateTime >= 20&& GUI.updateTime < 22){
					OLED_Init();
				}
				if( GUI.updateTime >= 21&& GUI.updateTime < 30)
			  {
					OLED_Clear();
					OLED_ShowString(20,2,"Save");
					OLED_ShowString(36,4,"Success");
			  }	
        else if( GUI.updateTime >= 25 && oled.keyValue == 0 ){
					digitalClan(&GUI.updateTime);
					resetGUIState();
				}
				digitalIncreasing(&GUI.updateTime);				
			}
			break;
		}
		/*У׼�ȴ�ģʽ*/
		case CAIL_WAIT_FLAG:{
			/*imuУ׼�ȴ�*/
			if(imuSensorData.state == IMU_CAIL_BEING||IMU_CAIL_START){
				OLED_Clear();
	      OLED_ShowString(0,2,"Cali Being");
			}
			else if(imuSensorData.state == IMU_CAIL_FINISH){
				GUIImuCalibration();
			}
			/*tofУ׼�ȴ�*/
			else if(tofReadDate.state[currentMenu ->currentOption] == IMU_CAIL_BEING||IMU_CAIL_START){
				OLED_Clear();
	      OLED_ShowString(0,2,"Cali Being");
				digitalLo(&tofSendDate.state[currentMenu ->currentOption]);
			}
			else if(tofReadDate.state[currentMenu ->currentOption] == IMU_CAIL_FINISH){
				tofCalibration();
			}
		}
	}
	/*��������*/	
	oled.keyValue = OLED_NULL;
}