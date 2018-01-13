#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}

void USART1_Do(void){
	if(usart1.RX_BUF[0]=='A' && usart1.RX_BUF[1]=='T'){
		usart1.printf("OK\r\n");
	}
}
void USART2_Do(void){
	usart3.Send(usart2.RX_BUF,usart2.RX_Len);
}
void USART3_Do(void){
	usart2.Send(usart3.RX_BUF,usart3.RX_Len);
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
