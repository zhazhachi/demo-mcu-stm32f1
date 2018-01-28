#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}

void EXTI9_5_IRQHandler(void){
	delay_ms(100);
	if(*K1.I==1){
		EXTI->PR=1<<6;
		
		if(state[0]=='0'){
			state[0]='1';
			*relay[0].O=0;
		}else{
			state[0]='0';
			*relay[0].O=1;
		}
	}else if(*K2.I==1){
		EXTI->PR=1<<7;
		
		if(state[1]=='0'){
			state[1]='1';
			*relay[1].O=0;
		}else{
			state[1]='0';
			*relay[1].O=1;
		}
	}else if(*K3.I==1){
		EXTI->PR=1<<8;
		
		if(state[2]=='0'){
			state[2]='1';
			*relay[2].O=0;
		}else{
			state[2]='0';
			*relay[2].O=1;
		}
	}
	EXTI->PR=0x03E0;
}

void USART1_Do(void){
}
void USART2_Do(void){
	if(usart2.RX_BUF[0]=='T' && usart2.RX_BUF[1]=='A' && usart2.RX_BUF[2]=='+'){
		if(usart2.RX_BUF[3]=='s' && usart2.RX_BUF[4]=='e' && usart2.RX_BUF[5]=='t'){//设置
			state[0]=usart2.RX_BUF[7];
			state[1]=usart2.RX_BUF[8];
			state[2]=usart2.RX_BUF[9];
			if(state[0]=='0'){*relay[0].O=1;}else{*relay[0].O=0;}
			if(state[1]=='0'){*relay[1].O=1;}else{*relay[1].O=0;}
			if(state[2]=='0'){*relay[2].O=1;}else{*relay[2].O=0;}
		}else if(usart2.RX_BUF[3]=='o' && usart2.RX_BUF[4]=='n' && usart2.RX_BUF[5]=='\n'){//设备上线
			
		}else if(usart2.RX_BUF[3]=='o' && usart2.RX_BUF[4]=='f' && usart2.RX_BUF[5]=='f'){//设备关机
			
		}else if(usart2.RX_BUF[3]=='f' && usart2.RX_BUF[4]=='i' && usart2.RX_BUF[5]=='n' && usart2.RX_BUF[6]=='d'){//进入微信发现
			
		}/*else if(usart2.RX_BUF[3]=='s' && usart2.RX_BUF[4]=='c' && usart2.RX_BUF[5]=='o' && usart2.RX_BUF[6]=='k'){//配网成功
			*CH_PD.O=0;//WIFI断电
			displayLed(LED0,1);//LED灭
		}*/
	}
}
void USART3_Do(void){
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
