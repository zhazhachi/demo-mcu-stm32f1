#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "flash.h"
#include "pwr.h"
#include "sys.h"
#include "task.h"
#include "usart.h"
/***  引用用户函数  ***/
#include "../config.h"
#include "./FCT.h"
#include "./fiipTask.h"
#include "./recvHadle.h"
#include "./ui.h"
#include "fiip-base/fiip.h"
#include "fiip-protocol/stdp.h"

/***    定义IO口    ***/

/***  定义全局变量  ***/
extern UsartStruct* usart1;
extern UsartStruct* usart2;
extern UsartStruct* usart3;

/***  定义用户函数  ***/
void initGpio(void);
void switchLed(void);
void setVar(uint8_t key, uint8_t val);

#endif  //__FUNCTION_H
