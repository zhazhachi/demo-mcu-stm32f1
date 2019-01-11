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
#include "setup.h"
#include "map.h"

/*************************************************
Function: setupRCC
Description: 初始化时钟树
*************************************************/
void setupRCC(void){
	/***  初始化系统时钟  ***/
	rcc_init(9); //HSE 9倍频
	//SystemInit();
	
	/***  初始化外设时钟  ***/
	rcc_cmd(0, AHB_DMA1, ENABLE);//DMA1
	rcc_cmd(2, APB2_AFIO, ENABLE);//AF
	rcc_cmd(2, APB2_GPIOA, ENABLE);//GPIOA
	rcc_cmd(2, APB2_GPIOB, ENABLE);//GPIOB
}

/*************************************************
Function: setupOther
Description: 其他初始化
*************************************************/
void setupOther(void){
	nvic_configGroup(2);//2抢占2响应
	
	map_jtag(1);//关闭JTAG,仅使用SWD
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
	
}

/*************************************************
Function: setupCOM
Description: 初始化通信接口,如USART、I2C、SPI、CAN
*************************************************/
UsartStruct* usart1;
UsartStruct* usart2;
UsartStruct* usart3;
void setupCOM(void){
  usart1=usart_new(1);
  usart2=usart_new(2);
  usart3=usart_new(3);
  
	usart_init(usart1,9600);
	usart_init(usart2,9600);
	usart_init(usart3,115200);
	//i2c2.config();
	//spi2.config();
	//can.init();
}

/*************************************************
Function: setup
Description: 起始函数(仅执行1次)
*************************************************/
void setup(void){
	flash_read(FLASH_ADDR_START, &me, sizeof(me));//读取设备信息
	if(me.status[0]!=0x67){//设备初始化
		u8 ID_def[8]={0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x01};//设备ID
		memcpy(me.ID, ID_def, 8);
		me.status[0]=0x67;
		flash_write(FLASH_ADDR_START, &me, sizeof(me));
	}
	task_init(1000);//1000ms(1s)心跳1次
	task_add(0x01, myTest, 10, 0xFFFF,0,0xFFFF);//10秒1次,执行无限次

	//iwdg::config(6,1250);
}

/*************************************************
Function: loop
Description: 循环函数(无限循环)
*************************************************/
void loop(void){
	//iwdg::feed();
	task_run();
	
	//pwr_sleep(0);//休眠
}
