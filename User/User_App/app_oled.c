#include "app.h"

oledMenuStruct_t mainMenu;
oledMenuStruct_t testMenu,workMENU;		       //主菜单的子菜单


oledMenuStruct_t *currentMenu;	 //当前菜单


/*
***************************************************
函数名：menuReset
功能：退回父菜单时重置父菜单
入口参数：	*menu
返回值：无
应用范围：外部调用
备注：
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
函数名：OLEDKeyNoReset
功能：清零按键长按时间
入口参数：	noReset：不需要清零的按键时间
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void OLEDKeyNoReset(uint8_t noReset)
{
	uint8_t i = 0;
	for(i = 0;i < OLED_KEY_LIST;i++){
		/*除了指定的按键时间外其他全清零*/
		if(i != noReset){
			digitalClan(&GUI.waitKeyTime[i]);
		}
	}
}
/*
***************************************************
函数名：nullHandle
功能：当无按键输入时执行的操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void nullHandle()
{
	/*只有无按键输入时间大于200ms后，清零所有按键长按时间*/
	if(GUI.waitKeyTime[OLED_NULL] < 2){
	digitalIncreasing(&GUI.waitKeyTime[OLED_NULL]);
	}
	else{
		OLEDKeyNoReset(OLED_ALL_NEED);
	}
}
/*
***************************************************
函数名：enterOn
功能：当按键输入为ENTER键时执行的实际操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void enterOn()
{
	/*存在子菜单*/
	if(currentMenu -> subMenu[currentMenu -> currentOption] != NULL ){
		/*进入子菜单*/
		currentMenu = currentMenu -> subMenu[currentMenu->currentOption];
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
	}
	/*存在可执行的菜单函数*/
	else if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
		/*执行菜单函数*/
		currentMenu -> func[currentMenu -> currentOption]();
		currentMenu -> displayFlag = FUNCTION_MANUAL_FLAG;
	}
}
/*
***************************************************
函数名：enterHandle
功能：当按键输入为ENTER键时执行的辨识操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void enterHandle()
{
	/*清零除了ENTER外的其他键值长按时间*/
	OLEDKeyNoReset(OLED_ENTER);
	/*如果不在菜单函数内*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*先执行一次操作*/
		if(!GUI.waitKeyTime[OLED_ENTER]){
			enterOn();
		}
		/*一段时间后连续操作*/
		else if(GUI.waitKeyTime[OLED_ENTER] > WAITTING_NEXT_TIME){
			if(!(GUI.waitKeyTime[OLED_ENTER] % NEXT_TIME_PERIOD)){
				enterOn();
			}
		} 
	}
	/*如果在菜单函数内*/
	else{
		enterOn();
	}
	/*长按时间自加*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_ENTER]);
}
/*
***************************************************
函数名：upHandle
功能：当按键输入为UP键时执行的辨识操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void upHandle()
{
	/*清零除了UP外的其他键值长按时间*/
	OLEDKeyNoReset(OLED_UP);
	/*如果不在菜单函数内*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*菜单选项没到顶头，选中选项向上一个选项*/
		if(currentMenu -> currentOption != 0){
			currentMenu -> currentOption--;
			if(currentMenu -> currentOption < currentMenu -> showFrom){
				currentMenu -> showFrom--;
				currentMenu -> showTo--;
			}
		}
		/*更新菜单*/
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
		GUI.workState = GUI_CHOOSE;
	}
	/*如果在菜单函数内*/
	else{
		/*执行菜单函数*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*长按时间自加*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_UP]);
}
/*
***************************************************
函数名：downHandle
功能：当按键输入为DOWN键时执行的辨识操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void downHandle()
{
	/*清零除了DOWN外的其他键值长按时间*/
	OLEDKeyNoReset(OLED_DOWN);
	/*如果不在菜单函数内*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*菜单选项没到底部，选中选项向下一个选项*/
		if(currentMenu -> currentOption != currentMenu -> subMenuNumber - 1)
		{
			currentMenu -> currentOption++;
			if(currentMenu -> currentOption > currentMenu -> showTo)
			{
				currentMenu -> showTo++;
				currentMenu -> showFrom++;
			}
		}
		/*更新菜单*/
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
		GUI.workState = GUI_CHOOSE;
	}
	/*如果在菜单函数内*/
	else{
		/*执行菜单函数*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*长按时间自加*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_DOWN]);
}
/*
***************************************************
函数名：backOn
功能：当按键输入为BACK键时执行的实际操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void backOn()
{
	/*存在父菜单*/
	if(currentMenu ->preMenu != NULL){
		/*返回父菜单*/
		menuReset(currentMenu);
		currentMenu = currentMenu ->preMenu;
	}
	/*重置各校准状态*/
	resetGUIState();
}
/*
***************************************************
函数名：backOn
功能：当按键输入为BACK键时执行的辨识操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void backHandle()
{
	/*清零除了BACK外的其他键值长按时间*/
	OLEDKeyNoReset(OLED_BACK);
	/*如果不在菜单函数内*/
	if(currentMenu ->displayFlag != FUNCTION_MANUAL_FLAG){
		/*先执行一次操作*/
		if(!GUI.waitKeyTime[OLED_BACK]){
			backOn();
		}
		/*一段时间后连续操作*/
		else if(GUI.waitKeyTime[OLED_BACK] > WAITTING_NEXT_TIME){
			if(!(GUI.waitKeyTime[OLED_BACK] % NEXT_TIME_PERIOD)){
				backOn();
			}	
		}
	}
	/*如果在菜单函数内*/
	else{
		/*执行菜单函数*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL ){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*长按时间自加*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_BACK]);
}
/*
***************************************************
函数名：saveHandle
功能：当按键输入为SAVE键时执行的辨识操作
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
static void saveHandle()
{
	/*清零除了BACK外的其他键值长按时间*/
	OLEDKeyNoReset(OLED_SAVE);
	/*长按时间500ms*/
	if(GUI.waitKeyTime[OLED_SAVE] == 5){
		/*进入保存或校准*/
		GUI.workState = GUI_SAVE_BEING;
		/*执行菜单函数*/
		if( currentMenu -> func[currentMenu -> currentOption] != NULL){
			currentMenu -> func[currentMenu -> currentOption]();
		}
	}
	/*长按时间6s*/
	else if(GUI.waitKeyTime[OLED_SAVE] == 60){
		/*重新初始化OLED,防意外黑屏*/
		OLED_Init();
		currentMenu -> displayFlag = UPDATEMENU_FLAG;
	}
	/*长按时间自加*/
	digitalIncreasing(&GUI.waitKeyTime[OLED_SAVE]);
	
}
/*
***************************************************
函数名：menuUpdate
功能：菜单更新
入口参数：	无
返回值：无
应用范围：外部调用
备注：
***************************************************
*/
void menuUpdate()
{
	u8 i = 0;	
  /*获取键码*/	
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
	/*oled运行模式*/
	switch(currentMenu -> displayFlag){
		/*刷新菜单模式*/
		case UPDATEMENU_FLAG:{
			OLED_Clear();
			OLED_ShowChar(120,(currentMenu -> currentOption - currentMenu -> showFrom) * 2,'*');
			for(i=0;i<4;++i)
			{
				OLED_ShowString(2,i * 2,currentMenu -> menuOption[i + currentMenu -> showFrom]);
				if( i == currentMenu -> subMenuNumber - 1 )			//如果菜单选项不足四个则跳出循环~
					break;
			}
			currentMenu -> displayFlag = NO_FLAG;							//清除刷新显示标志位~
			break;
		}
		/*保存错误模式*/
		case ERRORSAVE_FLAG:{
			if(GUI.updateTime>0&&GUI.updateTime<10)	{			//只刷新一次~
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
		/*自动刷新模式*/
		case FUNCTION_AUTO_FLAG:{
			OLED_Clear();
			for(i=0;i<4;++i)
			{
				OLED_ShowString(0,i * 2,currentMenu -> menuOption[i + currentMenu -> showFrom]);
				if( i == currentMenu -> subMenuNumber - 1 )			//如果菜单选项不足四个则跳出循环~
					break;
			}
			currentMenu -> func[currentMenu -> currentOption]();
			break;
		}
	  /*保存模式*/
		case FLASH_SAVE_FLAG:{
			if(GUI.updateTime>0&&GUI.updateTime<10)				//只刷新一次~
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
		/*校准等待模式*/
		case CAIL_WAIT_FLAG:{
			/*imu校准等待*/
			if(imuSensorData.state == IMU_CAIL_BEING||IMU_CAIL_START){
				OLED_Clear();
	      OLED_ShowString(0,2,"Cali Being");
			}
			else if(imuSensorData.state == IMU_CAIL_FINISH){
				GUIImuCalibration();
			}
			/*tof校准等待*/
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
	/*键码清零*/	
	oled.keyValue = OLED_NULL;
}