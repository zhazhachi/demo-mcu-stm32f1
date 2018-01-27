#include "function.hpp"

//GPIO
gpio K3=gpio(PA, 0);//薄膜按键
gpio CH_PD=gpio(PA, 1);//ESP8266 高 工作；低 断电
gpio WIFI_RST=gpio(PA, 4);//ESP8266 高 工作；低 重启
gpio Lock_Ctrl=gpio(PA, 5);//电磁锁 高 工作；低 断电
gpio PWM=gpio(PA, 6);//控制舵机
gpio RF_RST=gpio(PA, 8);
gpio RFPOWER_CTL=gpio(PA, 11);//RFID 高 工作；低 断电

gpio BAT_AD=gpio(PB, 0);//AD采集电池电压（已二分压）
gpio V_Ctrl=gpio(PB, 1);//5V升压 高 工作；低 断电
gpio LED0=gpio(PB, 4);//LED 高 灭；低 亮
gpio LED1=gpio(PB, 5);//LED 高 灭；低 亮
gpio K2=gpio(PB, 6);//薄膜按键
gpio PB7=gpio(PB, 7);
gpio PB8=gpio(PB, 8);
gpio PB9=gpio(PB, 9);
gpio SPI2_CS=gpio(PB, 12);//RFID_CS

gpio LOCK_FB=gpio(PC, 14);//电磁锁反馈端 高 已开锁；低 未开锁
gpio YK_JYM=gpio(PC, 15);//继电器 高 工作；低 断电

//全局变量
eeprom AT24Cxx(i2c2, 128, 0x0);

u8 CardID[4];//IC卡ID
u8 CardAll[4]={0xff,0xff,0xff,0xff};//总部管理员
u8 CardSub[4]={0xe0,0xe6,0xd5,0xe5};//社区管理员

//用户函数
void ReadCard(void){
	std::memset(CardID,0,4);
	*RFPOWER_CTL.O=0;
	RFID::GetCard(0x26);
	std::memcpy(CardID,RFID::pSnr,4);
	*RFPOWER_CTL.O=1;
}
void setUser(u8* ID){
	char num[1];
	AT24Cxx.Read(0x00, num, 1);
	AT24Cxx.Write(0x10+(num[0]>>2), (char*)ID, 4);
	num[0] = num[0]+1;
	AT24Cxx.Write(0x00, num, 1);
}
s8 isUser(u8* ID){
	s8 state=0,i;
	char num[1], CardID[4];
	AT24Cxx.Read(0x00, num, 1);
	for(i=0; i<num[0]; i++){
		AT24Cxx.Read(0x10+(i>>2), CardID, 4);
		if(std::memcmp(ID,CardID,4)==0){state=1;}
	}
	return(state);
}
void openLock(void){
	/*
	TIM3->CCR1 = 24;
	delay(3000);
	TIM3->CCR1 = 0;
	delay(3000);
	TIM3->CCR1 = 6;
	delay(3000);
	TIM3->CCR1 = 0;
	*/
	*V_Ctrl.O=1;
	*Lock_Ctrl.O=1;
	//while(*LOCK_FB.I==0);
	delay_ms(1000);
	*Lock_Ctrl.O=0;
	*V_Ctrl.O=0;
}
void pwm_config(){
	rcc::Cmd(1, APB1_TIM3,ENABLE);
	PWM.Config(P_PPAF,P_50MHz);
	tim3.BaseConfig(7200,200,0);//定时器周期
	tim3.OCConfig(2,0);
	
	TIM3->CR1 |= 1;//使能
	
	TIM3->CCR1 = 6;
	delay(3000);
	TIM3->CCR1 = 0;
}
u8 getBat10(){
	u8 a;
	a = 2*10*3.3*adc1.Get(8)/4096;
	return a;
}
void displayLed(gpio& id,s8 way,u8 time,u16 speed){
	u8 i=0;
	if(way == -1){
		for(i=0; i<time; i++){
			*id.O=0;
			delay_ms(speed);
			*id.O=1;
			delay_ms(speed);
		}
	}else{
		*id.O=way;
	}
}
