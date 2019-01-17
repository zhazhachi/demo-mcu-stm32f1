#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.h"
#include "flash.h"
#include "usart.h"
#include "pwr.h"
#include "task.h"
/***  引用用户函数  ***/
#include "../config.h"
#include "./me.h"
#include "./recvHadle.h"
#include "./ui.h"
#include "./FCT.h"

/***    定义IO口    ***/


/***  定义全局变量  ***/
extern UsartStruct* usart1;
extern UsartStruct* usart2;
extern UsartStruct* usart3;


/***  定义用户函数  ***/
void myTest(void);

#endif //__FUNCTION_H
