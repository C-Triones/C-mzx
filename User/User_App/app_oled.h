#ifndef _APP_OLED_H
#define _APP_OLED_H

#define WAITTING_NEXT_TIME  12
#define NEXT_TIME_PERIOD     2

enum{
	NO_FLAG = 0,														//�޲�����־λ
	UPDATEMENU_FLAG,												//���ܼ�������ʾ��־λ
	FUNCTION_MANUAL_FLAG,										//�����ֶ�ˢ��
	FUNCTION_AUTO_FLAG,
	ERRORSAVE_FLAG,                         //��������־λ
	FLASH_SAVE_FLAG,                         //FLASH�����־λ
	CAIL_WAIT_FLAG
};

typedef struct {
	TaskHandle_t xHandleTask;
	uint8_t dataInitFlag;
	uint32_t loops;
}oledStruct_t;

typedef struct 
{
	u8 showFrom;														//��ʾѡ����ʼ���
	u8 showTo;															//��ʾѡ��ĩβ���
	u8 subMenuNumber;												//�Ӳ˵�����
	u8 currentOption;												//��ǰѡ��
	u8 *menuOption[20];											//ѡ������
	struct menu **subMenu;									//�Ӳ˵�
	struct menu *preMenu;										//�ϼ��˵�
	u8 displayFlag;													//ˢ�±�־λ
	void (**func)(void);										//ִ�к���	
}oledMenuStruct_t;

#endif

