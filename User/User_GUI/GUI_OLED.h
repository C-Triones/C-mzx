#ifndef __GUI_OLED_H
#define __GUI_OLED_H

#define WAITTING_NEXT_TIME  12
#define NEXT_TIME_PERIOD     2
enum{
	OLED_NULL	= 0,                               //û��
	OLED_ENTER,															//ȷ�ϼ�
	OLED_UP,																			//�ϼ�
	OLED_DOWN,																		//�¼�
	OLED_BACK,																			//���ؼ�
	OLED_SAVE,                                    //�����
	OLED_KEY_LIST,
	OLED_ALL_NEED,                        //��������ȴ�ʱ��
};

typedef struct
{
	uint8_t init;
	uint8_t keyValue;
	float keyOriginalValue;
	
}oled_t;

enum{
	NO_FLAG = 0,														//�޲�����־λ
	UPDATEMENU_FLAG,												//���ܼ�������ʾ��־λ
	FUNCTION_MANUAL_FLAG,
	FUNCTION_AUTO_FLAG,
	WORK_FLAG,
	FLASH_SAVE_FLAG,                         //FLASH�����־λ
	TEST_FLAG,
};


typedef enum{
	WALK_TEST = 0,
	LEFT_WHEEL,
	RIGHT_WHEEL,
	TURN_TIME,
}testWalk_e;

typedef enum{
	FIRE1 = 0,
	FIRE2,
	FIRE3,
	FIRE9,
	CLEAR_ALL01,
}fireChoose01_e;

typedef enum{
	FIRE4 = 0,
	FIRE5,
	FIRE6,
	FIRE7,
	FIRE8,
	CLEAR_ALL02,
}fireChoose02_e;

typedef enum{
	ROOM1 = 0,
	ROOM2,
	ROOM3,
	ROOM4,
}rescueman_e;

typedef enum{
	FIRE01,
	FIRE02,
	RESCUEMAN,
}Choose_e;

typedef enum{
	GRAB_TEST = 0,
	GRAB_OPEN,
	GRAB_CLOSE,
}testGrab_e;

typedef enum{
	MOVE_TEST = 0,
	MOVE_DOWN,
	MOVE_UP,
}testClawMove_e;

typedef enum{
	CAMERA_SITE_TEST = 0,
	CAMERA_SITE_INIT,
	CAMERA_SITE_LOW,
	CAMERA_SITE_LOWEST,
}testCameraSite_e;

typedef enum{
	WALK_MORE_TEST = 0,
	LEFT_WHEEL_CLOSE,
	RIGHT_WHEEL_CLOSE,
	LEFT_WHEEL_LEAVE,
	RIGHT_WHEEL_LEAVE,
}testWalkMoreParameter_e;

typedef enum{
	ONE_POINT = 0,
	TWO_POINT,
	THREE_POINT,
	FOUR_POINT,
}workChoose_e;

typedef struct menu
{
	u8 showFrom;														//��ʾѡ����ʼ���
	u8 showTo;															//��ʾѡ��ĩβ���
	u8 subMenuNumber;												//�Ӳ˵�����
	u8 currentOption;												//��ǰѡ��
	u8 *menuOption[25];											//ѡ������
	struct menu **subMenu;									//�Ӳ˵�
	struct menu *preMenu;										//�ϼ��˵�
	u8 displayFlag;													//ˢ�±�־λ
	void (**func)(void);										//ִ�к���
	
}menuStruct_t;


extern oled_t oled;
extern menuStruct_t *currentMenu;

void GUI_OLEDInit(void);
void menuInit(void);
void menuReset(menuStruct_t *menu);
void menuUpdate(void);

static void enterHandle(void);
static void upHandle(void);
static void downHandle(void);
static void backHandel(void);
static void saveHandle(void);


void testSetZero(void);
void testGoStraight(void);
void testSr04Function(void);
void fireChoose(void);
void adFunction(void);
void fanTest(void);
void testPhotoelectricSwitchFuction(void);
void testWalkFuction(void);
void testWalkMoreParameterFuction(void);
void testFanFuction(void);
void workChoose(void);



#endif
