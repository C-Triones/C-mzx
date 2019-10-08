#ifndef _APP_INPUT_H
#define _APP_INPUT_H

typedef enum{
	INPUT_PRIORITY = 6,
	INPUT_STACK_SIZE = 512,
}appInput_e;

void app_inputTaskInit(void);

#endif
