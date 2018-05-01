#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}

void TIM3_IRQHandler(void){
	if(TIM3->SR & 0X0001){
		TIM3->SR &= ~1;//清除中断
		usart1.printf("%d\n", adc1.get(0,2));
	}
}

void USART1_Do(char* msg, u16 len){
	u16 Prescaler;
	u32 rate_set;
	u32 rate;
	
	if(usart1.rx.buf[0]=='A' && usart1.rx.buf[1]=='T'){
		switch(usart1.rx.buf[2]){
			case '+':
				switch(usart1.rx.buf[3]){
					case 'e'://结束
						//if(USART1_RX_BUF[4]=='n'&&USART1_RX_BUF[5]=='d')
						tim3.cmd(DISABLE);
						usart1.printf("ok\n");
					break;
					case 'm'://峰值
						//if(USART1_RX_BUF[4]=='a'&&USART1_RX_BUF[5]=='x')
						usart1.printf("max:ok\n");
					break;
					case 'r'://采样频率
						Prescaler=1;
						//if(USART1_RX_BUF[4]=='a'&&USART1_RX_BUF[5]=='t'&&USART1_RX_BUF[6]=='e')
						sscanf(usart1.rx.buf, "AT+rate=%d\r\n",&rate);
						rate=72*rate;
						rate_set=rate;
						while(rate_set>0xffff){
							Prescaler++;
							rate_set=rate/Prescaler;
						}
						tim3.config(Prescaler, rate_set, 1);
						usart1.printf("ARR:%d\n",rate_set);
					break;
					case 's'://开始
						//if(USART1_RX_BUF[4]=='t'&&USART1_RX_BUF[5]=='a'&&USART1_RX_BUF[6]=='r'&&USART1_RX_BUF[7]=='t')
						tim3.cmd(ENABLE);
						usart1.printf("ok\n");
					break;
					default:
						usart1.printf("error\n");
					break;
				}
			break;
			case '\r':
				usart1.printf("ok\n");
			break;
			default:
				usart1.printf("error\n");
			break;
		}
	}else{
		usart1.printf("%s",usart1.rx.buf);
	}
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
