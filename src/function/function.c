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
#include "./function.h"

/***  定义IO口(别忘记在function.hpp中引用)  ***/
GpioStruct* led_red;
GpioStruct* led_green;

/*  定义全局变量(别忘记在function.hpp中引用)  */

/*  定义用户函数(别忘记在function.hpp中引用)  */
void initGpio() {
  led_red = gpio_new(PB, 8);
  gpio_config(led_red, P_PPO, 0, P_2MHz);
  led_green = gpio_new(PB, 9);
  gpio_config(led_green, P_PPO, 0, P_2MHz);
}
void switchLed() {
  *led_red->O = ~(*led_red->I);
}

void setVar(uint8_t key, uint8_t val) {
  switch (key) {
    case 0x01:
      *led_red->O = val;
      break;
    case 0x02:
      *led_green->O = val;
      break;
    default:
      break;
  }
  fiipCloud_setActualVar(config.myId, config.myKey, &key, 0x01,&val,0x01);
}
