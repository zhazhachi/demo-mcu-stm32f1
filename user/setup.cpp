#include "setup.hpp"

void RCC_Setup(){
	{//初始化时钟
		rcc.init(9);//系统时钟设置(HSE 9倍频)
		//SystemInit();
		RCC->AHBENR |= 1;//DMA1
		RCC->APB2ENR|= 1;//AF
	}
	rcc.cmd(2, APB2_GPIOA, ENABLE);
	rcc.cmd(2, APB2_GPIOB, ENABLE);
}
void NVIC_Setup(){
	nvic.configGroup(2);//2抢占2响应
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
	usart2.init(9600,0x00,0x0D);
	//i2c2.init();
	//spi2.init();
}
void setup(){
	rcc.cmd(2, APB2_TIM1,ENABLE);//使能定时器的时钟
	Gpio(PA,8).config(P_PPAF,P_50MHz);//引脚复用
	Gpio(PA,9).config(P_PPAF,P_50MHz);
	Gpio(PB,13).config(P_PPAF,P_50MHz);
	Gpio(PB,14).config(P_PPAF,P_50MHz);
	tim1.config(1,3600,1);//设置定时器周期
	tim1.configOC(1,0,14);//输出SPWM波形并设置死区时间
	tim1.configOC(2,0,14);
	tim1.cmd(ENABLE);//使能定时器

	//IWDG_Config(6,1250);
}
void loop(){
	//IWDG_Feed();
	
	//pwr::Sleep(0);//休眠
}
