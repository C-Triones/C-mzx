#ifndef _DRIVER_FAN_MOTER_H
#define _DRIVER_FAN_MOTER_H

#define Motor1  PDout(12)  
#define Motor2  PDout(13)

#define Motor3  PDout(14)
#define Motor4  PDout(15)

void driver_InitFanMotor(void);
void driver_FanMotorFront(void);
void driver_FanMotorBehind(void);
void driver_FanMotorOff(void);

#endif
