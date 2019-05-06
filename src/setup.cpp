/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: setup.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 用户主函数
Usage: 
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "./setup.hpp"

/*************************************************
Function: setupRCC
Description: 初始化时钟树
*************************************************/
void setupRCC(void){
	/***  初始化系统时钟  ***/
	rcc.init(9); //HSE 9倍频
	//SystemInit();
	
	/***  初始化外设时钟  ***/
	rcc.cmd(0, AHB_DMA1, ENABLE);//DMA1
	rcc.cmd(2, APB2_AFIO, ENABLE);//AF
	rcc.cmd(2, APB2_GPIOA, ENABLE);//GPIOA
	rcc.cmd(2, APB2_GPIOB, ENABLE);//GPIOB
  rcc.cmd(2, APB2_GPIOC, ENABLE);  // GPIOC
}

/*************************************************
Function: setupOther
Description: 其他初始化
*************************************************/
void setupOther(void){
	nvic.configGroup(2);//2抢占2响应
	
	map::JTAG(1);//关闭JTAG,仅使用SWD
}

/*************************************************
Function: setupGPIO
Description: 初始化GPIO
*************************************************/
void setupGPIO(void){
	/***  将所有GPIO设置为模拟输入(低功耗)  ***/
	RCC->APB2ENR |= 0x1fc;
	GPIOA->CRL=0;
	GPIOA->CRH=0;
	GPIOB->CRL=0;
	GPIOB->CRH=0;
	GPIOC->CRL=0;
	GPIOC->CRH=0;
	GPIOD->CRL=0;
	GPIOD->CRH=0;
	RCC->APB2ENR &= ~0x1fc;
	
	/***  用户GPIO(请先在function.cpp中定义)  ***/
	gpio_default.config(P_PPO);
}

/*************************************************
Function: setupCOM
Description: 初始化通信接口,如USART、I2C、SPI、CAN
*************************************************/
void setupCOM(void){
	usart1.init(9600,0x00,0x0A);
	usart2.init(9600,0x00,0x0A);
	usart3.init(115200,0x00,0x0A);
	//i2c2.config();
	//spi2.config();
	//can.init();
}

/*************************************************
Function: setup
Description: 起始函数(仅执行1次)
*************************************************/
void setup(void){
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
void loop(void){
	//iwdg::feed();
	task.run();
	
	//pwr::sleep(0);//休眠
}
