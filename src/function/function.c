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
static uint8_t cmd_body[64];
static uint8_t cmd_getId[] = {0x70, 0x11};
static uint8_t cmd_login[] = {0x70, 0x12};
static uint8_t cmd_heart[] = {0x70, 0x13};
static uint8_t cmd_enterBinding[] = {0x70, 0x16};
static uint8_t cmd_setVarCurrent[] = {0x70, 0x21};
static StdpStruct* txd;

/*  定义用户函数(别忘记在function.hpp中引用)  */
void initGpio() {
  led_red = gpio_new(PC, 0);
  gpio_config(led_red, P_PPO, 0, P_2MHz);
  led_green = gpio_new(PC, 1);
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
      *led_red->O = val;
      break;
    default:
      break;
  }
  stdp_setVar(txd, stdp_field_cmd, cmd_setVarCurrent, 2);
  memcpy(&cmd_body[0], config.myId, 8);
  memcpy(&cmd_body[8], config.myKey, 4);
  cmd_body[12] = 0x01;
  cmd_body[13] = key;
  cmd_body[14] = 0x01;
  cmd_body[15] = val;
  stdp_setVar(txd, stdp_field_body, cmd_body, 16);
  fiip_send(txd->frame, fiip_centerId, NULL);
}
