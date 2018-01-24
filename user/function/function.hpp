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

#include "ultrasonic.hpp"


//GPIO
extern gpio K1;
extern gpio K2;
extern gpio O1;
extern gpio O2;
extern gpio TRIG;
extern gpio ECHO;

//全局变量

//用户函数
void myArmInit();
void myArmRun();
void myMeasure();

#endif //__FUNCTION_H
