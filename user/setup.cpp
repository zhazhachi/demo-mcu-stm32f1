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
	V_Ctrl.config(P_PPO);
	*V_Ctrl.O=0;//5V升压电路断电
	Lock_Ctrl.config(P_PPO);
	*Lock_Ctrl.O=0;//电磁铁断电
	LOCK_FB.config(P_FIN);
	YK_JYM.config(P_PPO);
	*YK_JYM.O=0;//继电器关断
	//PWM.config(P_PPAF);
	
	RFPOWER_CTL.config(P_PPO);
	*RFPOWER_CTL.O=1;//RFID读卡器断电
	WIFI_RST.config(P_PPO);
	*WIFI_RST.O=1;//WIFI禁用重启
	CH_PD.config(P_PPO);
	*CH_PD.O=0;//WIFI断电
	K2.config(P_DIN);
	K2.configExti(RTI);
	K3.config(P_DIN);
	K3.configExti(RTI);
	LED0.config(P_PPO);
	*LED0.O=1;//LED灭
	LED1.config(P_PPO);
	*LED1.O=1;//LED灭
	BAT_AD.config(P_AIN);
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	usart2.init(115200,0x00,0x0A);
	i2c2.init();
	spi2.init();
}
void setup(){
	flash.read(FLASH_ADDR_START, &me, sizeof(me));//读取设备信息
	if(me.status[0]!=0x67){//设备初始化
		u8 ID_def[8]={0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x01};//设备ID
		std::memcpy(me.ID, ID_def, 8);
		me.status[0]=0x67;
		flash.write(FLASH_ADDR_START, &me, sizeof(me));
	}
	rfid.init();
	//pwm_config();
	*CH_PD.O=1;//WIFI上电
	adc1.init();
	if(getBat10()<31){
		//低电量
	}
}
void loop(){
	pwr::sleep(1);//休眠,且不返回main函数
}
