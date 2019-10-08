#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

typedef enum
{
	PRESS = 0,
	NO_PRESS,
}keyValue_e;

typedef enum
{
	KEY_NULL = 0,
	KEY_ENTER ,
	KEY_UP ,
	KEY_DOWN ,
	KEY_BACK ,
	KEY_SAVE ,
	
	KEY_LIST_NUM,
	
}key_e;


typedef struct
{
	keyValue_e enter;
	keyValue_e up;
	keyValue_e down;
	keyValue_e back;
	keyValue_e save;
	
}keyList_t;


typedef struct
{
	keyList_t nowState;
	uint8_t keepTime[KEY_LIST_NUM];
	uint8_t realValue;
}key_t;

extern key_t key;

void driver_InitKeyHard(void);
void driverKeyNowStateUpdate(void);
uint8_t driverKeyDetection(uint8_t mode);

#endif
