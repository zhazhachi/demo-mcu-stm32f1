#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.hpp"
#include "adc.hpp"
//function
#include "me.hpp"
#include "UI.hpp"
#include "Ans.hpp"
#include "FCT.hpp"
#include "servo.hpp"

#include "RFID.hpp"
#include "eeprom.hpp"
#include "wifi.hpp"



//GPIO
extern gpio K3;
extern gpio CH_PD;
extern gpio WIFI_RST;
extern gpio Lock_Ctrl;
extern gpio PWM;
extern gpio RF_RST;
extern gpio RFPOWER_CTL;
extern gpio BAT_AD;
extern gpio V_Ctrl;
extern gpio LED0;
extern gpio LED1;
extern gpio K2;
extern gpio PB7;
extern gpio PB8;
extern gpio PB9;
extern gpio SPI2_CS;
extern gpio LOCK_FB;
extern gpio YK_JYM;

//全局变量
extern eeprom AT24Cxx;

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
void displayLed(gpio& id,s8 way,u8 time=1,u16 speed=1000);

#endif //__FUNCTION_H
