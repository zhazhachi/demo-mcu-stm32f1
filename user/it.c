#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}

void EXTI15_10_IRQHandler(void){
	
	delay_ms(100);
	if(*K1.I==1){//启动信号
		EXTI->PR=1<<11;//清除中断标志位
		startCharge();
	}else if(*K2.I==1){//充电完成信号
		EXTI->PR=1<<15;//清除中断标志位
		finishCharge();
	}else{
		EXTI->PR=0xffff;//清除中断标志位
	}
}

void USART1_Do(void){
	switch(usart1.RX_BUF[1]){
		//6~24
		case 1:TIM2->CCR1 = usart1.RX_BUF[2];break;
		case 2:TIM2->CCR2 = usart1.RX_BUF[2];break;
		case 3:TIM3->CCR1 = usart1.RX_BUF[2];break;
		case 4:TIM3->CCR2 = usart1.RX_BUF[2];break;
		case 5:TIM3->CCR3 = usart1.RX_BUF[2];break;
		case 6:TIM3->CCR4 = usart1.RX_BUF[2];break;
		case 0xff:
			TIM2->CCR1 = usart1.RX_BUF[2];
			TIM2->CCR2 = usart1.RX_BUF[3];
			TIM3->CCR1 = usart1.RX_BUF[4];
			TIM3->CCR2 = usart1.RX_BUF[5];
			TIM3->CCR3 = usart1.RX_BUF[6];
			TIM3->CCR4 = usart1.RX_BUF[7];
		break;
	}
	usart1.printf("%d:%d\r\n",usart1.RX_BUF[1],usart1.RX_BUF[2]);
}
void USART2_Do(void){
	if(usart2.RX_BUF[1]=='a' && usart2.RX_BUF[2]=='y' && usart2.RX_BUF[3]=='='){
		if(usart2.RX_BUF[4]=='1'){
			startCharge();
		}
		if(usart2.RX_BUF[4]=='2'){
			finishCharge();
		}
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
