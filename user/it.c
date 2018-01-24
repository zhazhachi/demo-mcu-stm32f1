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
	u32 distance0,distance1;
	
	delay_ms(100);
	if(*K1.I==1){//启动信号
		EXTI->PR=1<<11;//清除中断标志位
		
		*O1.O=0;//LED1亮
		*O2.O=1;//LED2灭
		/* 机械臂向上抬起 */
		TIM2->CCR1 = 10; //1号舵机
		TIM2->CCR2 = 6; //2号舵机
		TIM3->CCR1 = 15; //3号舵机
		TIM3->CCR2 = 5; //4号舵机
		TIM3->CCR3 = 25; //5号舵机
		TIM3->CCR4 = 5; //6号舵机
		do{//等待车辆停止运动
			delay_ms(6000);//6s
			ultrasonic::Ranging();
			distance0=ultrasonic::distance;
			if(distance0>130 && distance0<145){
				*O1.O=1;//LED1灭
				*O2.O=0;//LED2亮
			}
			delay_ms(4000);//4s
			ultrasonic::Ranging();
			distance1=ultrasonic::distance;
			if(distance1>130 && distance1<145){
				*O1.O=1;//LED1灭
				*O2.O=0;//LED2亮
			}
		}while((s32)(distance0-distance1)>10 || (s32)(distance0-distance1)<-10 || *O2.O!=0);
		*O1.O=1;//LED1灭
		*O2.O=1;//LED2灭
		myArmRun();//机械臂插入充电口
	}else if(*K2.I==1){//充电完成信号
		EXTI->PR=1<<15;//清除中断标志位
		
		//*O1.O=0;//LED1亮
		//*O2.O=1;//LED2灭
		/* 机械臂向上抬起 */
		TIM2->CCR1 = 10; //1号舵机
		delay_ms(1500);
		TIM2->CCR2 = 6; //2号舵机
		TIM3->CCR1 = 15; //3号舵机
		TIM3->CCR2 = 5; //4号舵机
		TIM3->CCR3 = 25; //5号舵机
		TIM3->CCR4 = 5; //6号舵机
		//*O1.O=0;//LED1亮
		//*O2.O=0;//LED2亮
		do{//等待车辆到0.5米之外
			delay_ms(5000);//5s
			ultrasonic::Ranging();
			distance0=ultrasonic::distance;
		}while(distance0<500);
		//*O1.O=1;//LED1灭
		//*O2.O=1;//LED2灭
		/* 机械臂水平伸直 */
		TIM2->CCR1 = 15;
		TIM2->CCR2 = 6;
		TIM3->CCR1 = 15;
		TIM3->CCR2 = 5;
		TIM3->CCR3 = 11;
		TIM3->CCR4 = 15;
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
