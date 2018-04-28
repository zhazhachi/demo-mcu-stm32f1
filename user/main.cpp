/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: main.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 程序入口,进入setup.cpp编写主函数
Usage: 
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "setup.hpp"

int main(void){
	setupRCC();
	setupOther();
	setupGPIO();
	setupCOM();

	setup();
	while(1){
		loop();
	}
}
