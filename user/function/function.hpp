#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.hpp"
#include "Adc.hpp"
#include "Flash.hpp"
#include "Usart.hpp"
#include "Tim.hpp"
#include "pwr.hpp"
//function
#include "me.hpp"
#include "Ui.hpp"
#include "ans.hpp"
#include "FCT.hpp"
#include "servo.hpp"
#include "RFID.hpp"
#include "eeprom.hpp"



//GPIO
extern Gpio K3;
extern Gpio CH_PD;
extern Gpio WIFI_RST;
extern Gpio Lock_Ctrl;
extern Gpio PWM;
extern Gpio RF_RST;
extern Gpio RFPOWER_CTL;
extern Gpio BAT_AD;
extern Gpio V_Ctrl;
extern Gpio LED0;
extern Gpio LED1;
extern Gpio K2;
extern Gpio PB7;
extern Gpio PB8;
extern Gpio PB9;
extern Gpio SPI2_CS;
extern Gpio LOCK_FB;
extern Gpio YK_JYM;

//全局变量
extern Eeprom AT24Cxx;
extern RFID rfid;

extern u8 CardType[2];
extern u8 CardID[4];//IC卡ID
extern u8 CardAll[4];//总部管理员
extern u8 CardSub[4];//社区管理员

//用户函数
void ReadCard(void);
void setUser(u8* ID);
s8 isUser(u8* ID);
void openLock(void);
void pwm_config(void);
u8 getBat10();
void displayLed(Gpio& id,s8 way,u8 time=1,u16 speed=1000);

#endif //__FUNCTION_H
