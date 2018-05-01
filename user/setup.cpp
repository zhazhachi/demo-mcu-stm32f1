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
	WIFI_RST.config(P_PPO);
	*WIFI_RST.O=1;//WIFI禁用重启
	CH_PD.config(P_PPO);
	*CH_PD.O=0;//WIFI断电
	K1.config(P_DIN);
	K1.configExti(RTI);
	K2.config(P_DIN);
	K2.configExti(RTI);
	K3.config(P_DIN);
	K3.configExti(RTI);
	O1.config(P_PPO);
	*O1.O=1;
	O2.config(P_PPO);
	*O2.O=1;
	O3.config(P_PPO);
	*O3.O=1;
	O4.config(P_PPO);
	*O4.O=1;
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	usart2.init(115200,0x00,0x0A);
	//i2c2.init();
	//spi2.init();
}
void setup(){
	flash.read(FLASH_ADDR_START, &me, sizeof(me));//读取设备信息
	if(me.status[0]!=0x67){//设备初始化
		u8 ID_def[8]={0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x01};//设备ID
		std::memcpy(me.ID, ID_def, 8);
		me.status[0]=0x67;
		flash.write(FLASH_ADDR_START, &me, sizeof(me));
	}
	*CH_PD.O=1;//WIFI上电
}
void loop(){
	pwr::sleep(0);//休眠
}
