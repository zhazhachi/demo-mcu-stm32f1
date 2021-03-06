/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: function.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 定义用户函数
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "function.hpp"

/***  定义IO口(别忘记在function.hpp中引用)  ***/

/*  定义全局变量(别忘记在function.hpp中引用)  */

/*  定义用户函数(别忘记在function.hpp中引用)  */
void switchLed(){
	*gpio_default.O = !(*gpio_default.I);
}

void setVar(uint8_t key, uint8_t val) {
  switch (key) {
    case 0x01:
      *gpio_default.O = val;
      break;
    default:
      break;
  }
  fiipCloud_setActualVar(config.myId, config.myKey, &key, 0x01,&val,0x01);
}
