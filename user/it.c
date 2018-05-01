#include "it.h"
u16 T=3600;
u8 Fsin=50;
float bei=0.5,n=0.5;

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}

void TIM1_UP_IRQHandler(void){//spwm
	static float Counter_sine=0;
	static u16 sinewavetable[200]={
		3600,3714,3827,3940,4053,4166,4278,4389,4500,4609,4718,4825,4932,5037,5140,5242,5342,5441,5538,5632,5725,5816,5904,5991,6074,6156,6234,6311,6384,6455,6522,6587,6649,6708,6764,6817,6866,6912,6955,6995,7031,7063,7093,7119,7141,7160,7175,7186,7195,7199,
		7200,7197,7191,7181,7168,7151,7130,7106,7079,7048,7013,6975,6934,6890,6842,6791,6736,6679,6619,6555,6489,6420,6348,6273,6195,6115,6033,5948,5860,5771,5679,5585,5489,5392,5292,5191,5088,4984,4879,4772,4664,4555,4445,4334,4222,4110,3997,3884,3770,3657,
		3543,3430,3316,3203,3090,2978,2866,2755,2645,2536,2428,2321,2216,2112,2009,1908,1808,1711,1615,1521,1429,1340,1252,1167,1085,1005,927,852,780,711,645,581,521,464,409,358,310,266,225,187,152,121,94,70,49,32,19,9,3,0,1,5,14,25,40,59,81,107,137,169,205,
		245,288,334,383,436,492,551,613,678,745,816,889,966,1044,1126,1209,1296,1384,1475,1568,1662,1759,1858,1958,2060,2163,2268,2375,2482,2591,2700,2811,2922,3034,3147,3260,3373,3486,3600
	};
	if ((TIM1->SR & 1) == 1){
		Counter_sine=Counter_sine+n;
		if(Counter_sine>=200){
			Counter_sine=Counter_sine-200;
		}
		TIM1->CCR1=(u16)(bei*sinewavetable[(u8)Counter_sine]);//设置占空比
		TIM1->CCR2=(u16)(bei*sinewavetable[(u8)Counter_sine]);
		TIM1->SR = ~1;
	}
}

void USART1_Do(char* msg, u16 len){
}
void USART2_Do(char* msg, u16 len){
	if(usart2.rx.buf[0]=='A' && usart2.rx.buf[1]=='T'){
		switch(usart2.rx.buf[3]){
			case '0'://开关
				if(usart2.rx.buf[5]==1 || usart2.rx.buf[5]=='1'){
					tim1.config(1,T,1);
					bei=T/7200.0;
					n=200/(1000.0*(72000/T)/Fsin);
					
					tim1.cmd(ENABLE);//使能
				}else{
					tim1.cmd(DISABLE);//失能
				}
				break;
			case '1'://开关频率：7200=0.1ms 10kHz
				//开关频率：（1~20kHz）
				T=72000/usart2.rx.buf[5];
				break;
			case '2'://Sin周期：2*100*0.1ms=20ms 50Hz
				//周期：（1~100Hz）
				Fsin=usart2.rx.buf[5];
				break;
			case '3'://死区时间：72=1us
				//死区时间：（0~3.54us） 1=13.8888ns
				tim1.configOC(1,0,usart2.rx.buf[5]);
				tim1.configOC(2,0,usart2.rx.buf[5]);
				break;
			case '9':
				T=72000/usart2.rx.buf[5];//计算PWM周期
				tim1.config(1,T,1);//设置PWM周期
				Fsin=usart2.rx.buf[6];//获取基波频率
				tim1.configOC(1,0,usart2.rx.buf[7]);//设置死区时间
				tim1.configOC(2,0,usart2.rx.buf[7]);
				bei=T/7200.0;
				n=200/(1000.0*(72000/T)/Fsin);
				
				tim1.cmd(ENABLE);//使能
				break;
		}
	}
}
void USART3_Do(char* msg, u16 len){
}

void SPI1_Do(void){
}
void SPI2_Do(void){
}
#if I2C_DMA
void I2C_do(void){}
#endif

_C void RTC_IRQHandler(void){
	if(RTC->CRL & 0x0001){//秒钟中断
		RTC->CRL &= ~0x0001;//清除秒钟中断
		//RTC_GetTime();//更新时间
	}
	if(RTC->CRL & 0x0002){//闹钟中断
		RTC->CRL &= ~0x0002;//清闹钟中断
	}
	while(!(RTC->CRL & (1 << 5)));//等待RTC寄存器操作完成
}
