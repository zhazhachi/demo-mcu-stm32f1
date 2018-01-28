#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.hpp"
#include "adc.hpp"
//function
#include "me.hpp"
#include "task.hpp"
#include "UI.hpp"
#include "Ans.hpp"
#include "FCT.hpp"



//GPIO
extern gpio K1;
extern gpio K2;
extern gpio K3;
extern gpio CH_PD;
extern gpio WIFI_RST;
extern gpio RFPOWER_CTL;
extern gpio O1;
extern gpio O2;
extern gpio O3;
extern gpio O4;

//全局变量
extern char state[5];
extern gpio relay[4];

//用户函数
void myTest();

#endif //__FUNCTION_H
