#ifndef __DRIVER_PHOTOELECTRIC_SWITCH_H
#define __DRIVER_PHOTOELECTRIC_SWITCH_H


#define PHOTOELECTRIC_SWITCH_COUNT    11	   					/* 按键个数, 8个独立建 + 2个组合键 */

typedef enum
{
	EXIST = 0,/*检测到*/
	NO_EXIST,/*未检测到*/
}photoelectricSwitchValue_e;

typedef struct
{
	photoelectricSwitchValue_e frontLeftOblique;
	photoelectricSwitchValue_e frontMiddle;
	photoelectricSwitchValue_e frontRightOblique;
	photoelectricSwitchValue_e frontLeft;
	photoelectricSwitchValue_e frontRight;
}photoelectricSwitchList_t;


extern photoelectricSwitchList_t photoelectricSwitch;

void driver_InitPhotoelectricSwitchHard(void);
void driverPhotoelectricSwitchNowStateUpdate(void);

#endif
