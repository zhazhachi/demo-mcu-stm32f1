#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.hpp"
#include "Adc.hpp"
#include "Flash.hpp"
#include "Usart.hpp"
#include "pwr.hpp"
//function
#include "me.hpp"
#include "Task.hpp"
#include "Ui.hpp"
#include "ans.hpp"
#include "FCT.hpp"



//GPIO
extern Gpio K1;
extern Gpio K2;
extern Gpio K3;
extern Gpio CH_PD;
extern Gpio WIFI_RST;
extern Gpio RFPOWER_CTL;
extern Gpio O1;
extern Gpio O2;
extern Gpio O3;
extern Gpio O4;

//全局变量
extern char state[5];
extern Gpio relay[4];

//用户函数
void myTest();

#endif //__FUNCTION_H
