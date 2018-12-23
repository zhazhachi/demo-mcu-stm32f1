/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: it.c
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 中断服务函数
Usage: 
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}


/*************************************************
Function: USART1_IRQHandler
Description: 串口接收中断
*************************************************/
_C void USART1_IRQHandler(void){
	u8 res;

	if(USART1->SR&(1<<5)){
		res=USART1->DR;
		//to do something
		recvHadle_usart1(res);
	}
}
_C void USART2_IRQHandler(void){
	u8 res;

	if(USART2->SR&(1<<5)){
		res=USART2->DR;
		//to do something
	}
}
_C void USART3_IRQHandler(void){
	u8 res;

	if(USART3->SR&(1<<5)){
		res=USART2->DR;
		//to do something
	}
}


/*************************************************
Function: CAN1_RX1_IRQHandler
Description: CAN总线接收中断
*************************************************/
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

/*************************************************
Function: RTC_IRQHandler
Description: RTC实时时钟中断
*************************************************/
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
