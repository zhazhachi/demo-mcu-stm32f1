#include "setup.hpp"

void RCC_Setup(){
	{//初始化时钟
		rcc::Init(9);//系统时钟设置(HSE 9倍频)
		//SystemInit();
		RCC->AHBENR |= 1;//DMA1
		RCC->APB2ENR|= 1;//AF
	}
	rcc::Cmd(2, APB2_GPIOA, ENABLE);
	rcc::Cmd(2, APB2_GPIOB, ENABLE);
}
void NVIC_Setup(){
	nvic::GroupConfig(2);//2抢占2响应
}
void GPIO_Setup(){
	{//模拟输入，低功耗
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
	}
	
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	zigbee.Config(9600,0x7E,0x7D);
	wifi.Config(115200,0x7E,0x7D);
	//i2c2.Config();
	//spi2.Config();
}
void setup(){
	//IWDG_Config(6,1250);
}
void loop(){
	//IWDG_Feed();
	pwr::Sleep(1);//休眠 且不返回main函数
	
}
