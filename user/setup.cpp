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
	K1.config(P_DIN);//下拉输入
	K1.configExti(RTI);//上升沿中断
	K2.config(P_DIN);//下拉输入
	K2.configExti(RTI);//上升沿中断
	O1.config(P_PPO);//推挽输出
	*O1.O=1;//灭灯
	O2.config(P_PPO);//推挽输出
	*O2.O=1;//灭灯
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	usart1.init(9600,0xab,0xcd);
	usart2.init(115200,0x77,0x30);
	//i2c2.init();
	//spi2.init();
}
void setup(){
	//ultrasonic.init();
	myArmInit();
    
	task.init();
	task.add(0x01, myMeasure, 1, 0xff, 0, 0xff);//1秒1次,执行无限次,立即开始,永不停止

	//iwdg::config(6,1250);
}
void loop(){
	//iwdg::feed();
	//task.run();
	
	//pwr::sleep(0);//休眠
}
