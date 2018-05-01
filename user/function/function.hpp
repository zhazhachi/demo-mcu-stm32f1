#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.hpp"
#include "adc.hpp"
#include "tim.hpp"
#include "usart.hpp"
//function
#include "me.hpp"
#include "task.hpp"
#include "UI.hpp"
#include "Ans.hpp"
#include "FCT.hpp"

#include "ultrasonic.hpp"


//GPIO
extern Gpio K1;
extern Gpio K2;
extern Gpio O1;
extern Gpio O2;
extern Gpio TRIG;
extern Gpio ECHO;

//全局变量
extern Ultrasonic ultrasonic;

//用户函数
void myArmInit();
void myArmRun();
void startCharge();
void finishCharge();
void myMeasure();

#endif //__FUNCTION_H
