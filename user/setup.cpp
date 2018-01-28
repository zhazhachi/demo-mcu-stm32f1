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
	WIFI_RST.Config(P_PPO);
	*WIFI_RST.O=1;//WIFI禁用重启
	CH_PD.Config(P_PPO);
	*CH_PD.O=0;//WIFI断电
	K1.Config(P_DIN);
	K1.ExConfig(RTI);
	K2.Config(P_DIN);
	K2.ExConfig(RTI);
	K3.Config(P_DIN);
	K3.ExConfig(RTI);
	O1.Config(P_PPO);
	*O1.O=1;
	O2.Config(P_PPO);
	*O2.O=1;
	O3.Config(P_PPO);
	*O3.O=1;
	O4.Config(P_PPO);
	*O4.O=1;
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	usart2.Config(115200,0x00,0x0A);
	//i2c2.Config();
	//spi2.Config();
}
void setup(){
	flash::Read(FLASH_START_ADDR, &me, sizeof(me));//读取设备信息
	if(me.status[0]!=0x67){//设备初始化
		u8 ID_def[8]={0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x01};//设备ID
		std::memcpy(me.ID, ID_def, 8);
		me.status[0]=0x67;
		flash::Write(FLASH_START_ADDR, &me, sizeof(me));
	}
	*CH_PD.O=1;//WIFI上电
}
void loop(){
	pwr::Sleep(0);//休眠
}
