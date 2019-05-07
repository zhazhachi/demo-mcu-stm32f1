/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: main.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 程序入口
Usage: 
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "bsp.hpp"

/*************************************************
Function: setup
Description: 起始函数(仅执行1次)
*************************************************/
static void setup(void){
  mempool_init(0x1000);
  config_init();
  initFiip();
  if (config.myStatus[1] != 0x89) {  //设备初始化
    fiipCloud_getId(config.myTypeId, config.myTypeKey);
  }
  fiipCloud_login();
  task.init(1000);                                // 1000ms(1s)心跳1次
  task.add(0x01, switchLed, 10, 0xFFFF, 0, 0xFFFF);  // 10秒1次,执行无限次
  task.add(0x02, fiipCloud_heart, 90, 0xFFFF, 0, 0xFFFF);  // 90秒1次,执行无限次

	//iwdg::config(6,1250);
}

/*************************************************
Function: loop
Description: 循环函数(无限循环)
*************************************************/
static void loop(void){
	//iwdg::feed();
	task.run();
	
	//pwr::sleep(0);//休眠
}


/*************************************************
Function: main
Description: 入口函数
*************************************************/
int main(void){
  initBsp(); // 初始化底层驱动

	setup();
	while(1){
		loop();
	}
}
