#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.hpp"
#include "Flash.hpp"
#include "Usart.hpp"
#include "Can.hpp"
#include "pwr.hpp"
#include "Task.hpp"
/***  引用用户函数  ***/
#include "../config.h"
#include "./Ui.hpp"
#include "./FCT.hpp"
#include "./fiipTask.h"
#include "./recvHandle.hpp"
#include "./Ui.hpp"
#include "fiip-base/fiip.h"
#include "fiip-protocol/stdp.h"
#include "fiip-cloud/fiipCloud.h"
/***    定义IO口    ***/


/***  定义全局变量  ***/


/***  定义用户函数  ***/
void switchLed(void);
void setVar(uint8_t key, uint8_t val);

#endif //__FUNCTION_H
