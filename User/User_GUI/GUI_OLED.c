#include "GUI.h"

typedef void DeviceActivation_t(void);

oled_t oled;
uint32_t faning = 0;
menuStruct_t mainMenu;
menuStruct_t testModeMenu,workChooseMenu,fireChooseMenu;			      //���˵����Ӳ˵�
menuStruct_t testHcSr04Menu;
menuStruct_t testWalkMenu,testWalkMoreParameterMenu;
menuStruct_t clawGrabMenu,clawMoveMenu,cameraSiteMenu;
menuStruct_t FOMenu,FTMenu,RMenu;

menuStruct_t *currentMenu;										      //��ǰ�˵�

void menuInit()
{
	u8 i = 0;
	/***************************���˵�*********************************************/
	{
		mainMenu.showFrom = 0;
		mainMenu.showTo = 3;
		mainMenu.subMenuNumber = 3;
		mainMenu.currentOption = 0;
		mainMenu.menuOption[0] = "TestMode";
		mainMenu.menuOption[1] = "WorkChoose";
		mainMenu.menuOption[2] = "TYPE_CHOOSE";
		mainMenu.subMenu = malloc(sizeof(menuStruct_t *) * mainMenu.subMenuNumber);
		mainMenu.subMenu[0] = &testModeMenu;
		mainMenu.subMenu[1] = &workChooseMenu;
		mainMenu.subMenu[2] = &fireChooseMenu;
		mainMenu.func = (void (**)(void))malloc(sizeof(NULL) * mainMenu.subMenuNumber);
		mainMenu.func[0] = NULL;
		mainMenu.func[1] = NULL;
		mainMenu.func[2] = NULL;
	}
	/***************************TestMode�˵�*********************************************/
	{
		testModeMenu.showFrom = 0;
		testModeMenu.showTo = 3;
		testModeMenu.subMenuNumber = 23;
		testModeMenu.currentOption = 0;
		testModeMenu.menuOption[0] = "HC-SR04";
		testModeMenu.menuOption[1] = "AD";
		testModeMenu.menuOption[2] = "FAN";
		testModeMenu.menuOption[3] = "Zero_Set";
		testModeMenu.menuOption[4] = "FTL_90";
		testModeMenu.menuOption[5] = "FTL_180";
		testModeMenu.menuOption[6] = "FTR_90";
		testModeMenu.menuOption[7] = "FTR_180";
		testModeMenu.menuOption[8] = "FTL_135";
		testModeMenu.menuOption[9] = "FTL_45";
		testModeMenu.menuOption[10] = "FTR_135";
		testModeMenu.menuOption[11] = "FTR_45";
		testModeMenu.menuOption[12] = "BTL_45";
		testModeMenu.menuOption[13] = "BTR_45";
		testModeMenu.menuOption[14] = "RTL_45";
		testModeMenu.menuOption[15] = "RTR_45";
		testModeMenu.menuOption[16] = "RTL_90";
		testModeMenu.menuOption[17] = "RTR_90";
		testModeMenu.menuOption[18] = "RTL_135";
		testModeMenu.menuOption[19] = "RTR_135";
		testModeMenu.menuOption[20] = "RTL_180";
		testModeMenu.menuOption[21] = "RTR_180";
		testModeMenu.menuOption[22] = "GS";
		testModeMenu.subMenu = malloc(sizeof(menuStruct_t *) * testModeMenu.subMenuNumber);
		testModeMenu.subMenu[0] = NULL;
		testModeMenu.subMenu[1] = NULL;
		testModeMenu.subMenu[2] = NULL;
		for(i = 3;i<23;i++){
			testModeMenu.subMenu[i] = &testWalkMenu;
		}
		testModeMenu.preMenu = &mainMenu;
		testModeMenu.func = (void (**)(void))malloc(sizeof(NULL) * testModeMenu.subMenuNumber);
		testModeMenu.func[0] = testSr04Function;
		testModeMenu.func[1] = adFunction;
		testModeMenu.func[2] = fanTest;
		for(i = 3;i<23;i++){
			testModeMenu.func[i] = NULL;
		}
	}
	/***************************WorkChoose�˵�*********************************************/
	{
		workChooseMenu.showFrom = 0;
		workChooseMenu.showTo = 3;
		workChooseMenu.subMenuNumber = 2;
		workChooseMenu.currentOption = 0;
		workChooseMenu.menuOption[0] = "TestMode";
		workChooseMenu.menuOption[1] = "WorkMode";
		workChooseMenu.subMenu = malloc(sizeof(menuStruct_t *) * workChooseMenu.subMenuNumber);
		for(i = 0;i<2;i++){
			workChooseMenu.subMenu[i] = NULL;
		}
		workChooseMenu.preMenu = &mainMenu;
		workChooseMenu.func = (void (**)(void))malloc(sizeof(NULL) * workChooseMenu.subMenuNumber);
		for(i = 0;i<2;i++){
			workChooseMenu.func[i] = workChoose;
		}
	}
	/***************************fireChoose�˵�*********************************************/
	{
		fireChooseMenu.showFrom = 0;
		fireChooseMenu.showTo = 3;
		fireChooseMenu.subMenuNumber = 3;
		fireChooseMenu.currentOption = 0;
		fireChooseMenu.menuOption[0] = "FIRE-01";
		fireChooseMenu.menuOption[1] = "FIRE-02";
		fireChooseMenu.menuOption[2] = "RESCUE";
		fireChooseMenu.subMenu = malloc(sizeof(menuStruct_t *) * fireChooseMenu.subMenuNumber);
		fireChooseMenu.subMenu[0] = &FOMenu;
		fireChooseMenu.subMenu[1] = &FTMenu;
		fireChooseMenu.subMenu[2] = &RMenu;
		fireChooseMenu.preMenu = &mainMenu;
		fireChooseMenu.func = (void (**)(void))malloc(sizeof(NULL) * fireChooseMenu.subMenuNumber);
		for(i = 0;i<3;i++){
			fireChooseMenu.func[i] = NULL;
		}
	}
	/***************************FO�˵�*********************************************/
	{
		FOMenu.showFrom = 0;
		FOMenu.showTo = 3;
		FOMenu.subMenuNumber = 5;
		FOMenu.currentOption = 0;
		FOMenu.menuOption[0] = "fire1";
		FOMenu.menuOption[1] = "fire2";
		FOMenu.menuOption[2] = "fire3";
		FOMenu.menuOption[3] = "fire9";
		FOMenu.menuOption[4] = "CLEAR_ALL";
		FOMenu.subMenu = malloc(sizeof(menuStruct_t *) * FOMenu.subMenuNumber);
		for(i = 0;i < 5;i++){
			FOMenu.subMenu[i] = NULL;
		}
		FOMenu.preMenu = &fireChooseMenu;
		FOMenu.func = (void (**)(void))malloc(sizeof(NULL) * FOMenu.subMenuNumber);
		for(i = 0;i<5;i++){
			FOMenu.func[i] = fireChoose;
		}
	}
	/***************************FT�˵�*********************************************/
	{
		FTMenu.showFrom = 0;
		FTMenu.showTo = 3;
		FTMenu.subMenuNumber = 6;
		FTMenu.currentOption = 0;
		FTMenu.menuOption[0] = "fire4";
		FTMenu.menuOption[1] = "fire5";
		FTMenu.menuOption[2] = "fire6";
		FTMenu.menuOption[3] = "fire7";
		FTMenu.menuOption[4] = "fire8";
		FTMenu.menuOption[5] = "CLEAR_ALL";
		FTMenu.subMenu = malloc(sizeof(menuStruct_t *) * FTMenu.subMenuNumber);
		for(i = 0;i < 6;i++){
			FTMenu.subMenu[i] = NULL;
		}
		FTMenu.preMenu = &fireChooseMenu;
		FTMenu.func = (void (**)(void))malloc(sizeof(NULL) * FTMenu.subMenuNumber);
		for(i = 0;i<6;i++){
			FTMenu.func[i] = fireChoose;
		}
	}
	/***************************R�˵�*********************************************/
	{
		RMenu.showFrom = 0;
		RMenu.showTo = 3;
		RMenu.subMenuNumber = 4;
		RMenu.currentOption = 0;
		RMenu.menuOption[0] = "ROOM1";
		RMenu.menuOption[1] = "ROOM2";
		RMenu.menuOption[2] = "ROOM3";
		RMenu.menuOption[3] = "ROOM4";
		RMenu.subMenu = malloc(sizeof(menuStruct_t *) * RMenu.subMenuNumber);
		for(i = 0;i < 4;i++){
			RMenu.subMenu[i] = NULL;
		}
		RMenu.preMenu = &fireChooseMenu;
		RMenu.func = (void (**)(void))malloc(sizeof(NULL) * RMenu.subMenuNumber);
		for(i = 0;i<4;i++){
			RMenu.func[i] = fireChoose;
		}
	}
	/***************************testWalk�˵�*********************************************/
	{
		testWalkMenu.showFrom = 0;
		testWalkMenu.showTo = 3;
		testWalkMenu.subMenuNumber = 4;
		testWalkMenu.currentOption = 0;
		testWalkMenu.menuOption[0] = "Walk_Test";
		testWalkMenu.menuOption[1] = "Left_Wheel";
		testWalkMenu.menuOption[2] = "Right_Wheel";
		testWalkMenu.menuOption[3] = "Turn_Time";
		testWalkMenu.subMenu = malloc(sizeof(menuStruct_t *) * testWalkMenu.subMenuNumber);
		for(i = 0;i<4;i++){
			testWalkMenu.subMenu[i] = NULL;
		}
		testWalkMenu.preMenu = &testModeMenu;
		testWalkMenu.func = (void (**)(void))malloc(sizeof(NULL) * testWalkMenu.subMenuNumber);
		for(i = 0;i<4;i++){
			testWalkMenu.func[i] = testWalkFuction;
		}
	}


	/***************************��ʼ�˵�����********************************************/
	{
		currentMenu = &mainMenu;
		OLED_ShowChar(120,(currentMenu -> currentOption - currentMenu -> showFrom) * 2,'*',16);
		for(i=0;i<4;++i)
		{
			OLED_ShowString(0,i * 2,currentMenu -> menuOption[i + currentMenu -> showFrom],16);
			if( i == currentMenu -> subMenuNumber - 1 )			//����˵�ѡ����ĸ�������ѭ��~
				break;
		}
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
	}
}
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
			GUI.waitKeyTime[i] = NULL;
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
		GUI.waitKeyTime[OLED_NULL]++;
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
	/*����ڲ˵�������*/
	if((currentMenu ->displayFlag == FUNCTION_MANUAL_FLAG)||(currentMenu ->displayFlag == TEST_FLAG)||(currentMenu ->displayFlag == WORK_FLAG)){
		enterOn();
	}
	/*������ڲ˵�������*/

	else{
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
	/*����ʱ���Լ�*/
	GUI.waitKeyTime[OLED_ENTER]++;
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
	if((currentMenu ->displayFlag == FUNCTION_MANUAL_FLAG)||(currentMenu ->displayFlag == TEST_FLAG)||(currentMenu ->displayFlag == WORK_FLAG)){
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}	
	}
	/*����ڲ˵�������*/
	else{
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
	/*����ʱ���Լ�*/
	GUI.waitKeyTime[OLED_UP]++;
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
	/*����ڲ˵�������*/	
	if((currentMenu ->displayFlag == FUNCTION_MANUAL_FLAG)||(currentMenu ->displayFlag == TEST_FLAG)||(currentMenu ->displayFlag == WORK_FLAG)){
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*������ڲ˵�������*/
	else{
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
	/*����ʱ���Լ�*/
	GUI.waitKeyTime[OLED_DOWN]++;
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
	/*����ڲ˵�������*/
	if((currentMenu ->displayFlag == FUNCTION_MANUAL_FLAG)||(currentMenu ->displayFlag == TEST_FLAG)||(currentMenu ->displayFlag == WORK_FLAG)){
		/*ִ�в˵�����*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*������ڲ˵�������*/
	else{
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
	/*����ʱ���Լ�*/
	GUI.waitKeyTime[OLED_BACK]++;
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
	//if((currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG)||(currentMenu ->displayFlag != TEST_FLAG))
	if((currentMenu ->displayFlag != TEST_FLAG)&&(currentMenu ->displayFlag != WORK_FLAG)){
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
		else if(GUI.waitKeyTime[OLED_SAVE] == 30){
			/*���³�ʼ��OLED,���������*/
			driver_InitOLED();
			currentMenu -> displayFlag = UPDATEMENU_FLAG;
		}
	}
	
	/*����ʱ���Լ�*/
	GUI.waitKeyTime[OLED_SAVE]++;	
}

/*
***************************************************
��������parameterCalibration
���ܣ�д��;��Ȳ���У׼
��ڲ�����	*parameter������ָ��
          limitMin��  ������Сֵ
          limitMax:   �������ֵ
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void parameterCalibration(uint32_t *parameter,uint32_t limitMin,uint32_t limitMax)
{
	static uint8_t incrementMin = 0,incrementMiddle = 0,incrementMax = 0;
	static float realParameter = 0;
  /************�������������Χ�仯********************************************/
	if(limitMax - limitMin <= 250){
		incrementMin = 1;incrementMiddle = 2;incrementMax = 10;
	}
	else if(limitMax - limitMin > 250){
		incrementMin = 1;incrementMiddle = 10;incrementMax = 100;
	}
	/************�����ڰ����Ĺ���********************************************/
	switch(oled.keyValue){
			case OLED_ENTER:{
				/*��λ�����һ�α������*/
				realParameter = *parameter;
				break;
			}
			case OLED_UP:{
				/*�����Լ�*/
				if(GUI.waitKeyTime[OLED_UP] <= KEY_EXPEDITE_LEVEL_1){
					realParameter += incrementMin;
				}
				else if(GUI.waitKeyTime[OLED_UP] > KEY_EXPEDITE_LEVEL_1&& GUI.waitKeyTime[OLED_UP] <= KEY_EXPEDITE_LEVEL_2){
					realParameter += incrementMiddle;
				}
				else if(GUI.waitKeyTime[OLED_UP] > KEY_EXPEDITE_LEVEL_2){
					realParameter += incrementMax;
				}
				/*�����޷�*/
				if(realParameter >= limitMax){
					realParameter = limitMax;
				}
				break;
			}
			case OLED_DOWN:{
					/*�����Լ�*/
				if(GUI.waitKeyTime[OLED_DOWN] <= KEY_EXPEDITE_LEVEL_1){
					realParameter -= incrementMin;
				}
				else if(GUI.waitKeyTime[OLED_DOWN] > KEY_EXPEDITE_LEVEL_1&& GUI.waitKeyTime[OLED_DOWN] <= KEY_EXPEDITE_LEVEL_2){
					realParameter -= incrementMiddle;
				}
				else if(GUI.waitKeyTime[OLED_DOWN] > KEY_EXPEDITE_LEVEL_2){
					realParameter -= incrementMax;
				}	
				if(realParameter <= limitMin){
					realParameter = limitMin;
				}
				/*�����޷�*/
				else{
					
				} 
				break;
			}
			case OLED_BACK:{
				/*�ָ����˵�����*/
				currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
				break;
			} 
			case OLED_SAVE:{
				*parameter = realParameter;
				app_FlashWriteUdata();
				saveGUIFinish();
				break;
			}
			default:{
				break;
			}
		}
	OLED_Clear();
	
	OLED_ShowNum(0,0,limitMin,4,16);
	OLED_ShowString(42,0,"to",16);
	OLED_ShowNum(80,0,limitMax,5,16);
	OLED_ShowString(0,2,currentMenu ->preMenu->menuOption[currentMenu ->preMenu->currentOption],16);
	OLED_ShowString(0,4,currentMenu ->menuOption[currentMenu ->currentOption],16);
	OLED_ShowNum(36,6,realParameter,5,16);
}
/*
***************************************************
��������fuctionParameterCalibration
���ܣ�д�뺯�������У׼
��ڲ�����*parameter :�����Ĵ�����
          *realParameter:������ʵ������ֵ
          *displayFunction����ʾ���������ú���
          *chooseFunction��ѡ���������
          *saveFunction�������������
����ֵ����
Ӧ�÷�Χ���ⲿ����
��ע��
***************************************************
*/
void fuctionParameterCalibration(float *parameter,uint16_t *realParameter,DeviceActivation_t *displayFunction,DeviceActivation_t *chooseFunction,DeviceActivation_t *saveFunction)
{
	switch(oled.keyValue){
		case OLED_ENTER:{
			OLED_Clear();
			/*��ʾ���������ú���*/
			displayFunction();
			break;
		}
		case OLED_UP:{
			/*ѡ���������*/
			chooseFunction();
			currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
			break;
		}
		case OLED_DOWN:{
			/*ѡ���������*/
			chooseFunction();
			currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
			break;
		}
		case OLED_BACK:{
			/*���ú��������ز˵�Ŀ¼*/
			*realParameter = *parameter ;
			currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
			break;
		} 
		case OLED_SAVE:{
			/*ѡ���������*/
			chooseFunction();
			saveFunction();
			app_FlashWriteUdata();									//�������浽flash
			saveGUIFinish();
			break;
		}
		default:break;
	}
}

void testSr04Data(ultrasonicStruct_t *sr04Data,uint8_t x,uint8_t y,uint8_t Char_Size)
{

		OLED_ShowNum(x,y,(uint8_t)(sr04Data->getDistance),4,Char_Size);

}

void adShowData(adcTestStruct_t *adcShowData,uint8_t x,uint8_t y,adcDevice_e device,uint8_t Char_Size){
	OLED_ShowNum(x,y,(uint8_t)(adcShowData->adcData[device]),4,Char_Size);
}

void adFunction(void){
	switch(oled.keyValue){
		case OLED_BACK:{
			outfireRobotState.step = INIT;
			currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
			break;
		}
		case OLED_ENTER:{
			break;
		}
		case OLED_SAVE:{
			outfireRobotState.workMode = OUT_FIRE;
			outfireRobotState.step = READY;
		break;
		}
	}
	adShowData(&adcTestData,0,0,L_ADC,16);
	adShowData(&adcTestData,80,0,R_ADC,16);
	OLED_ShowString(16,6,"LEFT",16);
	OLED_ShowString(80,6,"RIGHT",16);
	currentMenu->displayFlag = FUNCTION_AUTO_FLAG;
}

void testSr04Function(void)
{
	
	switch(oled.keyValue){
		case OLED_BACK:{
			outfireRobotState.step = INIT;
			rescueRobotState.step = INIT;
			currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
			break;
		}
		case OLED_ENTER:{
			break;
		}
		case OLED_SAVE:{
			outfireRobotState.workMode = OUT_FIRE;
			outfireRobotState.step = READY;
			rescueRobotState.workMode = RESCUEING;
			rescueRobotState.step = READY;
		break;
		}
	}
	testSr04Data(&SRF_04_Data1,20,0,16);
	testSr04Data(&SRF_04_Data2,60,0,16);
	testSr04Data(&SRF_04_Data3,0,3,16);
	testSr04Data(&SRF_04_Data4,0,6,16);
	testSr04Data(&SRF_04_Data5,80,3,16);
	testSr04Data(&SRF_04_Data6,80,6,16);
	
	currentMenu->displayFlag = FUNCTION_AUTO_FLAG;
}

void testWalkFuction(void)
{ 
	switch(currentMenu -> currentOption){
		case WALK_TEST: {
			switch(oled.keyValue){
				case OLED_ENTER:{
						currentMenu -> displayFlag = TEST_FLAG;
						if(outfireRobotState.testTarget != TESTING||rescueRobotState.testTarget != TESTING){
						switch(currentMenu ->preMenu->currentOption){
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{outfireRobotState.moveWays = FRONT_TURN_LEFT_90;rescueRobotState.moveWays = FRONT_TURN_LEFT_90;break;}
							case 5:{outfireRobotState.moveWays = FRONT_TURN_LEFT_180;rescueRobotState.moveWays = FRONT_TURN_LEFT_180;break;}
							case 6:{outfireRobotState.moveWays = FRONT_TURN_RIGHT_90;rescueRobotState.moveWays = FRONT_TURN_RIGHT_90;break;}
							case 7:{outfireRobotState.moveWays = FRONT_TURN_RIGHT_180;rescueRobotState.moveWays = FRONT_TURN_RIGHT_180;break;}
							case 8:{outfireRobotState.moveWays = FRONT_TURN_LEFT_135;rescueRobotState.moveWays = FRONT_TURN_LEFT_135;break;}
							case 9:{outfireRobotState.moveWays = FRONT_TURN_LEFT_45;rescueRobotState.moveWays = FRONT_TURN_LEFT_45;break;}
							case 10:{outfireRobotState.moveWays = FRONT_TURN_RIGHT_135;rescueRobotState.moveWays = FRONT_TURN_RIGHT_135;break;}
							case 11:{outfireRobotState.moveWays = FRONT_TURN_RIGHT_45;rescueRobotState.moveWays = FRONT_TURN_RIGHT_45;break;}
							case 12:{outfireRobotState.moveWays = BEHIND_TURN_LEFT_45;rescueRobotState.moveWays = BEHIND_TURN_LEFT_45;break;}
							case 13:{outfireRobotState.moveWays = BEHIND_TURN_RIGHT_45;rescueRobotState.moveWays = BEHIND_TURN_RIGHT_45;break;}
							case 14:{outfireRobotState.moveWays = REVERSE_LEFT_TURN_45;rescueRobotState.moveWays = REVERSE_LEFT_TURN_45;break;}
							case 15:{outfireRobotState.moveWays = REVERSE_RIGHT_TURN_45;rescueRobotState.moveWays = REVERSE_RIGHT_TURN_45;break;}
							case 16:{outfireRobotState.moveWays = REVERSE_LEFT_TURN_90;rescueRobotState.moveWays = REVERSE_LEFT_TURN_90;break;}
							case 17:{outfireRobotState.moveWays = REVERSE_RIGHT_TURN_90;rescueRobotState.moveWays = REVERSE_RIGHT_TURN_90;break;}
							case 18:{outfireRobotState.moveWays = REVERSE_LEFT_TURN_135;rescueRobotState.moveWays = REVERSE_LEFT_TURN_135;break;}
							case 19:{outfireRobotState.moveWays = REVERSE_RIGHT_TURN_135;rescueRobotState.moveWays = REVERSE_RIGHT_TURN_135;break;}
							case 20:{outfireRobotState.moveWays = REVERSE_LEFT_TURN_180;rescueRobotState.moveWays = REVERSE_LEFT_TURN_180;break;}
							case 21:{outfireRobotState.moveWays = REVERSE_RIGHT_TURN_180;rescueRobotState.moveWays = REVERSE_RIGHT_TURN_180;break;}
							case 22:{outfireRobotState.moveWays = GO_STRAIGHT;rescueRobotState.moveWays = GO_STRAIGHT;break;} 
							default:break;
						}
						OLED_Clear();
						outfireRobotState.testTarget = TESTING;
						rescueRobotState.testTarget = TESTING;
					}
						OLED_ShowString(42,0,"Testing",16);
						OLED_ShowString(42,2,currentMenu ->preMenu->menuOption[currentMenu ->preMenu->currentOption],16);
					break;
				}
				case OLED_BACK: {
					currentMenu -> displayFlag = UPDATEMENU_FLAG;
					rescueRobotState.testTarget = WAITING;
					rescueRobotState.moveWays = STOP;
					outfireRobotState.testTarget = WAITING;
					outfireRobotState.moveWays = STOP;
					break;	
				}
			}
				break;
				
		}
		case LEFT_WHEEL:{
			currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
			switch(currentMenu->preMenu->currentOption){
				case 0:break;
				case 1:break;
				case 2:break;
				case 3:{parameterCalibration(&parameter[NAME_SET_ZERO__LEFT_RATE],0,200);break;}
				case 4:{parameterCalibration(&parameter[NAME_TURN_LEFT__LEFT_RATE],0,50);break;}
				case 5:{parameterCalibration(&parameter[NAME_TURN_LEFT__LEFT_RATE],0,50);break;}
				case 6:{parameterCalibration(&parameter[NAME_TURN_RIGHT__LEFT_RATE],0,50);break;}
				case 7:{parameterCalibration(&parameter[NAME_TURN_RIGHT__LEFT_RATE],0,50);break;}
				case 8:{parameterCalibration(&parameter[NAME_TURN_LEFT__LEFT_RATE],0,50);break;}
				case 9:{parameterCalibration(&parameter[NAME_TURN_LEFT__LEFT_RATE],0,50);break;}
				case 10:{parameterCalibration(&parameter[NAME_TURN_RIGHT__LEFT_RATE],0,50);break;}
				case 11:{parameterCalibration(&parameter[NAME_TURN_RIGHT__LEFT_RATE],0,50);break;}
				case 12:{parameterCalibration(&parameter[NAME_TURN_LEFT__LEFT_RATE],0,50);break;}
				case 13:{parameterCalibration(&parameter[NAME_TURN_RIGHT__LEFT_RATE],0,50);break;}
				case 14:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],0,50);break;}
				case 15:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],0,50);break;}
				case 16:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],0,50);break;}
				case 17:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],0,50);break;}
				case 18:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],0,50);break;}
				case 19:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],0,50);break;}
				case 20:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE],0,50);break;}
				case 21:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE],0,50);break;}
				case 22:{parameterCalibration(&parameter[NAME_GO_STRAIGHT__LEFT_RATE],0,50);break;}
				default:break;
		}
			break;
		}
		case RIGHT_WHEEL:{
			currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
			switch(currentMenu ->preMenu->currentOption){
				case 0:break;
				case 1:break;
				case 2:break;
				case 3:{parameterCalibration(&parameter[NAME_SET_ZERO__RIGHT_RATE],0,200);break;}
				case 4:{parameterCalibration(&parameter[NAME_TURN_LEFT__RIGHT_RATE],0,50);break;}
				case 5:{parameterCalibration(&parameter[NAME_TURN_LEFT__RIGHT_RATE],0,50);break;}
				case 6:{parameterCalibration(&parameter[NAME_TURN_RIGHT__RIGHT_RATE],0,50);break;}
				case 7:{parameterCalibration(&parameter[NAME_TURN_RIGHT__RIGHT_RATE],0,50);break;}
				case 8:{parameterCalibration(&parameter[NAME_TURN_LEFT__RIGHT_RATE],0,50);break;}
				case 9:{parameterCalibration(&parameter[NAME_TURN_LEFT__RIGHT_RATE],0,50);break;}
				case 10:{parameterCalibration(&parameter[NAME_TURN_RIGHT__RIGHT_RATE],0,50);break;}
				case 11:{parameterCalibration(&parameter[NAME_TURN_RIGHT__RIGHT_RATE],0,50);break;}
				case 12:{parameterCalibration(&parameter[NAME_TURN_LEFT__RIGHT_RATE],0,50);break;}
				case 13:{parameterCalibration(&parameter[NAME_TURN_RIGHT__RIGHT_RATE],0,50);break;}
				case 14:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],0,50);break;}
				case 15:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],0,50);break;}
				case 16:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],0,50);break;}
				case 17:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],0,50);break;}
				case 18:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],0,50);break;}
				case 19:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],0,50);break;}
				case 20:{parameterCalibration(&parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE],0,50);break;}
				case 21:{parameterCalibration(&parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE],0,50);break;}
				case 22:{parameterCalibration(&parameter[NAME_GO_STRAIGHT__RIGHT_RATE],0,50);break;}
			}
			break;
		}
		case TURN_TIME:{
			currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
			switch(currentMenu ->preMenu->currentOption){
				case 0:break;
				case 1:break;
				case 2:break;
				case 3:{parameter[NAME_FRONT_TURN_LEFT_TIME_90] = SET_ZERO_TIME;
						parameter[NAME_FRONT_TURN_LEFT_TIME_180] = SET_ZERO_TIME;
						parameter[NAME_FRONT_TURN_RIGHT_TIME_90] = SET_ZERO_TIME;
						parameter[NAME_FRONT_TURN_RIGHT_TIME_180] = SET_ZERO_TIME;
						parameter[NAME_FRONT_TURN_LEFT_TIME_135] = SET_ZERO_TIME;
						parameter[NAME_FRONT_TURN_RIGHT_TIME_135] = SET_ZERO_TIME;
						parameter[NAME_FRONT_TURN_RIGHT_TIME_45] = SET_ZERO_TIME;
						parameter[NAME_BEHIND_TURN_LEFT_TIME_45] = SET_ZERO_TIME;
						parameter[NAME_BEHIND_TURN_RIGHT_TIME_45] = SET_ZERO_TIME;
						parameter[NAME_REVERSE_TURN_TIME_45] = SET_ZERO_TIME;
						parameter[NAME_REVERSE_TURN_TIME_90] = SET_ZERO_TIME;
						parameter[NAME_REVERSE_TURN_TIME_135] = SET_ZERO_TIME;
						parameter[NAME_REVERSE_TURN_TIME_180] = SET_ZERO_TIME;
						parameter[NAME_GO_STRAIGHT_TIME] = SET_ZERO_TIME;
						app_FlashWriteUdata();
						saveGUIFinish();
						break;
						}
				case 4:{parameterCalibration(&parameter[NAME_FRONT_TURN_LEFT_TIME_90],200,3000);break;}
				case 5:{parameterCalibration(&parameter[NAME_FRONT_TURN_LEFT_TIME_180],200,5000);break;}
				case 6:{parameterCalibration(&parameter[NAME_FRONT_TURN_RIGHT_TIME_90],200,5000);break;}
				case 7:{parameterCalibration(&parameter[NAME_FRONT_TURN_RIGHT_TIME_180],200,5000);break;}
				case 8:{parameterCalibration(&parameter[NAME_FRONT_TURN_LEFT_TIME_135],200,5000);break;}
				case 9:{parameterCalibration(&parameter[NAME_FRONT_TURN_LEFT_TIME_45],200,5000);break;}
				case 10:{parameterCalibration(&parameter[NAME_FRONT_TURN_RIGHT_TIME_135],200,5000);break;}
				case 11:{parameterCalibration(&parameter[NAME_FRONT_TURN_RIGHT_TIME_45],200,5000);break;}
				case 12:{parameterCalibration(&parameter[NAME_BEHIND_TURN_LEFT_TIME_45],200,5000);break;}
				case 13:{parameterCalibration(&parameter[NAME_BEHIND_TURN_RIGHT_TIME_45],200,5000);break;}
				case 14:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_45],200,5000);break;}
				case 15:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_45],200,5000);break;}
				case 16:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_90],200,5000);break;}
				case 17:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_90],200,5000);break;}
				case 18:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_135],200,5000);break;}
				case 19:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_135],200,5000);break;}
				case 20:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_180],200,5000);break;}
				case 21:{parameterCalibration(&parameter[NAME_REVERSE_TURN_TIME_180],200,5000);break;}
				case 22:{parameterCalibration(&parameter[NAME_GO_STRAIGHT_TIME],200,5000);break;}
			}
			break;
		}		
	}
}

void fanTest(void)
{
	switch(oled.keyValue){
		case OLED_UP:{
			PDout(14) = 1;
			break;
		}
		case OLED_DOWN:{
			PDout(14) = 0;
//			currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
			break;
		}
	}
	OLED_Clear();
	if(PDout(14) == 1){
		OLED_ShowString(63,3,"ON",16);
	}
	if(PDout(14) == 0){
		OLED_ShowString(63,3,"OFF",16);
		faning = 0;
	}
	currentMenu -> displayFlag = TEST_FLAG;
	
}
 


void testSetZero(void)
{
	switch(oled.keyValue){
				case OLED_SAVE:{
					app_walkStop();
					currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
					break;
				}
				case OLED_ENTER:{
					app_walkStop();
					OLED_ShowString(0,0,"GoStraightTest",16);
					break;
				}
	}
	
}

void workChoose(void)
{

	switch(currentMenu -> currentOption){
		case TEST:{ 
			currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
			switch(oled.keyValue){
				case OLED_BACK:{
					currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
					break;
				}
				case OLED_ENTER:{
					OLED_Clear();
					OLED_ShowString(0,0,"ChooseTest",16);
					outfireRobotState.workMode = TEST;
					outfireRobotState.step = INIT;
					rescueRobotState.workMode = TEST;
					rescueRobotState.step = INIT;
					break;
				}
			}
		break;}
		case OUT_FIRE:{  
			currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
			switch(oled.keyValue){
				case OLED_BACK:{
					currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
					break;
				}
				case OLED_ENTER:{
					OLED_Clear();
					OLED_ShowString(0,0,"ChooseWork",16);
					outfireRobotState.workMode = OUT_FIRE;
					rescueRobotState.workMode = RESCUEING;
					rescueRobotState.step = READY;
					outfireRobotState.step = READY;
					break;
				}
			}
		break;}
	}
}

void fireChoose(void){
	int i;
	switch(currentMenu -> preMenu -> currentOption){
		case FIRE01:{
			robotSelect.robotSelect = OUT_FIRE1;
			switch(currentMenu -> currentOption){
				case FIRE1:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[FIRST_FIRE]){
								outfireRobotState.fireArray[FIRST_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[FIRST_FIRE]){
								outfireRobotState.fireArray[FIRST_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE2:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[SECOND_FIRE]){
								outfireRobotState.fireArray[SECOND_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[SECOND_FIRE]){
								outfireRobotState.fireArray[SECOND_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE3:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[THIRD_FIRE]){
								outfireRobotState.fireArray[THIRD_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[THIRD_FIRE]){
								outfireRobotState.fireArray[THIRD_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE9:{	
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[FOURTH_FIRE]){
								outfireRobotState.fireArray[FOURTH_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[FOURTH_FIRE]){
								outfireRobotState.fireArray[FOURTH_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case CLEAR_ALL01:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							for(i = 0;i < 9;i++){outfireRobotState.returnFlag[i] = 0;} //��ʼ�����Ѱ�Һͷ��غ���
							for(i = 0;i < 9;i++){outfireRobotState.fireArray[i] = 0;}
							OLED_ShowString(0,0,"CLEAR_ALL",16);
							OLED_ShowString(0,2,"SUCCESSFULY",16);
							break;
						}
					}
				}
			}
			break;
		}
		case FIRE02:{
			robotSelect.robotSelect = OUT_FIRE2;
			switch(currentMenu -> currentOption){
				case FIRE4:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[FOURTH_FIRE]){
								outfireRobotState.fireArray[FOURTH_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[FOURTH_FIRE]){
								outfireRobotState.fireArray[FOURTH_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE5:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[FIFTH_FIRE]){
								outfireRobotState.fireArray[FIFTH_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[FIFTH_FIRE]){
								outfireRobotState.fireArray[FIFTH_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE6:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[SIXTH_FIRE]){
								outfireRobotState.fireArray[SIXTH_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[SIXTH_FIRE]){
								outfireRobotState.fireArray[SIXTH_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE7:{	
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[SENVENTH_FIRE]){
								outfireRobotState.fireArray[SENVENTH_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[SENVENTH_FIRE]){
								outfireRobotState.fireArray[SENVENTH_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case FIRE8:{	
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							if(outfireRobotState.fireArray[EIGHTH_FIRE]){
								outfireRobotState.fireArray[EIGHTH_FIRE] = 0;
								OLED_ShowString(0,0,"CHOOSE_NO",16);
							}
							else if(!outfireRobotState.fireArray[EIGHTH_FIRE]){
								outfireRobotState.fireArray[EIGHTH_FIRE] = 1;
								OLED_ShowString(0,0,"CHOOSE_YES",16);
							}break;
						}
					}break;
				}
				case CLEAR_ALL02:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							for(i = 0;i < 9;i++){outfireRobotState.returnFlag[i] = 0;} //��ʼ�����Ѱ�Һͷ��غ���
							for(i = 0;i < 9;i++){outfireRobotState.fireArray[i] = 0;}
							OLED_ShowString(0,0,"CLEAR_ALL",16);
							OLED_ShowString(0,2,"SUCCESSFULY",16);
							break;
						}
					}break;
				}
			}
			break;
		}
		case RESCUEMAN:{
			robotSelect.robotSelect = RESCUE;
			switch(currentMenu -> currentOption){
				case ROOM1:{	
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							rescueRobotState.rescuePosition = ROOM_ONE;
							OLED_ShowString(0,0,"ROOM1_OK",16);
						}break;
					}
					break;
				}
				case ROOM2:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							rescueRobotState.rescuePosition = ROOM_TWO;
							OLED_ShowString(0,0,"ROOM2_OK",16);
						}break;
					}
					break;
				}
				case ROOM3:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							rescueRobotState.rescuePosition = ROOM_THREE;
							OLED_ShowString(0,0,"ROOM3_OK",16);
						}break;
					}
					break;
				}
				case ROOM4:{
					switch(oled.keyValue){
						case OLED_BACK:{
							currentMenu -> displayFlag = UPDATEMENU_FLAG;				//ˢ��һ�β˵�~
							break;
						}
						case OLED_ENTER:{
							OLED_Clear();
							rescueRobotState.rescuePosition = ROOM_FOUR;
							OLED_ShowString(0,0,"ROOM4_OK",16);
						}break;
					}
					break;
				}
			}
		}	
	}
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
	oled.keyValue = key.realValue;
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
			OLED_ShowChar(120,(currentMenu -> currentOption - currentMenu -> showFrom) * 2,'*',16);
			for(i=0;i<4;++i)
			{
				OLED_ShowString(2,i * 2,currentMenu -> menuOption[i + currentMenu -> showFrom],16);
				if( i == currentMenu -> subMenuNumber - 1 )			//����˵�ѡ����ĸ�������ѭ��~
					break;
			}
			currentMenu -> displayFlag = NO_FLAG;							//���ˢ����ʾ��־λ~
			break;
		}
		/*WORKģʽ*/
		case WORK_FLAG:{
			OLED_Clear();
			//OLED_ShowNum(48,7,outfireRobotState.allTarget,6,12);
//			OLED_ShowString(48,5,"Next",12);
//			OLED_ShowString(0,5,"Now",12);
//			OLED_ShowString(94,5,"Step",12);
//			OLED_ShowNum(94,7,outfireRobotState.workStep,2,12);

			break;
		}
		/*�Զ�ˢ��ģʽ*/
		case FUNCTION_AUTO_FLAG:{
			OLED_Clear();
			currentMenu -> func[currentMenu -> currentOption]();
			if(oled.keyValue == OLED_BACK){
				currentMenu -> displayFlag = UPDATEMENU_FLAG;
			}
			break;
		}
	  /*����ģʽ*/
		case FLASH_SAVE_FLAG:{
			if(GUI.updateTime>0&&GUI.updateTime<2)				//ֻˢ��һ��~
			{
				OLED_Clear();
				OLED_ShowString(20,2,"Save",16);
				OLED_ShowString(36,4,"Being",16);					
				GUI.updateTime++;
			}
			else{ 
				if(GUI.updateTime >= 2&& GUI.updateTime < 3){
					driver_InitOLED();
				}
				if( GUI.updateTime >= 3&& GUI.updateTime < 10)
			  {
					OLED_Clear();
					OLED_ShowString(20,2,"Save",16);
					OLED_ShowString(36,4,"Success",16);
			  }	
        else if( GUI.updateTime >= 10 && oled.keyValue == 0 ){
					GUI.updateTime = NULL;
					resetGUIState();
				}
				GUI.updateTime++;			
			}
			break;
		}
		case TEST_FLAG:{
			if(oled.keyValue == OLED_BACK){
//				app_WorkCommandReset();
				GUI.testFlag = 0;
				currentMenu -> displayFlag = UPDATEMENU_FLAG;
			}
			else{
				currentMenu -> func[currentMenu -> currentOption]();
			}
		}
		default:break;
	}
	/*��������*/	
	oled.keyValue = OLED_NULL;
}


