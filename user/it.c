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
Function: USART1_Do
Description: 串口1接收完字符串后,会自动调用此函数
Input: 
	msg   串口1接收到的字符串
	len   串口1接收到的字符串长度
Return: void
*************************************************/
void USART1_Do(char* msg, u16 len){
	usart1.send(msg, len);
}

/*************************************************
Function: USART2_Do
Description: 串口2接收完字符串后,会自动调用此函数
Input: 
	msg   串口2接收到的字符串
	len   串口2接收到的字符串长度
Return: void
*************************************************/
void USART2_Do(char* msg, u16 len){
	usart3.send(msg, len);
}

/*************************************************
Function: USART3_Do
Description: 串口3接收完字符串后,会自动调用此函数
Input: 
	msg   串口3接收到的字符串
	len   串口3接收到的字符串长度
Return: void
*************************************************/
void USART3_Do(char* msg, u16 len){
	usart2.send(msg, len);
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

/*************************************************
Function: RTC_IRQHandler
Description: RTC实时时钟中断
Input: void
Return: void
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
