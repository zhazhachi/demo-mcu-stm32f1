#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}


void USART1_Do(char* msg, u16 len){
	usart1.send(msg, len);
}
void USART2_Do(char* msg, u16 len){
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

_C void CAN1_RX1_IRQHandler(){
	can.rcv(&can.rx);
	usart3.printf("ID :%x\r\n", can.rx.ExtId);
	usart3.printf("IDE:%x\r\n", can.rx.IDE);
	usart3.printf("RTR:%x\r\n", can.rx.RTR);
	usart3.printf("DLC:%x\r\n", can.rx.DLC);
	usart3.printf("FMI:%x\r\n", can.rx.FMI);
	for(u8 i=0; i<can.rx.DLC; i++)
		usart3.printf("FMI:%x\r\n", can.rx.Data[i]);
	
}
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
