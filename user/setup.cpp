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
	V_Ctrl.Config(P_PPO);
	*V_Ctrl.O=0;//5V升压电路断电
	Lock_Ctrl.Config(P_PPO);
	*Lock_Ctrl.O=0;//电磁铁断电
	LOCK_FB.Config(P_FIN);
	YK_JYM.Config(P_PPO);
	*YK_JYM.O=0;//继电器关断
	//PWM.Config(P_PPAF);
	
	RFPOWER_CTL.Config(P_PPO);
	*RFPOWER_CTL.O=1;//RFID读卡器断电
	WIFI_RST.Config(P_PPO);
	*WIFI_RST.O=1;//WIFI禁用重启
	CH_PD.Config(P_PPO);
	*CH_PD.O=0;//WIFI断电
	K2.Config(P_DIN);
	K2.ExConfig(RTI);
	K3.Config(P_DIN);
	K3.ExConfig(RTI);
	LED0.Config(P_PPO);
	*LED0.O=1;//LED灭
	LED1.Config(P_PPO);
	*LED1.O=1;//LED灭
	BAT_AD.Config(P_AIN);
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	usart2.Config(115200,0x00,0x0A);
	i2c2.Config();
	spi2.Config();
}
void setup(){
	flash::Read(FLASH_START_ADDR, &me, sizeof(me));//读取设备信息
	if(me.status[0]!=0x67){//设备初始化
		u8 ID_def[8]={0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x01};//设备ID
		std::memcpy(me.ID, ID_def, 8);
		me.status[0]=0x67;
		flash::Write(FLASH_START_ADDR, &me, sizeof(me));
	}
	RFID::com = spi2;
	RFID::RST=RF_RST;
	RFID::CS=SPI2_CS;
	RFID::Init();
	//pwm_config();
	*CH_PD.O=1;//WIFI上电
	adc1.Init();
	if(getBat10()<31){
		//低电量
	}
}
void loop(){
	pwr::Sleep(1);//休眠,且不返回main函数
}
