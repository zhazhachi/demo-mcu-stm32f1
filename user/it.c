#include "it.h"

void NMI_Handler(void){}
void HardFault_Handler(void){while (1){}}
void MemManage_Handler(void){while (1){}}
void BusFault_Handler(void){while (1){}}
void UsageFault_Handler(void){while (1){}}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}

void EXTI0_IRQHandler(void){
	delay_ms(10);
	if(*K3.I==1){
		EXTI->PR=1<<0;
		
		displayLed(LED1,0);//LED亮
		ReadCard();
		if(std::memcmp(CardID,CardSub,4)==0 || std::memcmp(CardID,CardAll,4)==0){
			delay_ms(1000);
			if(*K3.I==1){//设卡
				displayLed(LED1,-1,4,1000);//4次闪烁 8s
				
				ReadCard();
				setUser(CardID);
			}else{
				openLock();//管理员开锁
			}
		}else if(isUser(CardID) ){
			openLock();
		}
		displayLed(LED1,1);//LED灭
	}
}
void EXTI9_5_IRQHandler(void){
	delay_ms(10);
	if(*K2.I==1){
		EXTI->PR=1<<6;
		
		ReadCard();
		if(std::memcmp(CardID,CardSub,4)==0 || std::memcmp(CardID,CardAll,4)==0){
			delay_ms(1000);
			if(*K2.I==1){//配网+微信发现
				*CH_PD.O=1;//WIFI上电
				displayLed(LED0,-1,2,1000);//2次闪烁 4s
				usart2.printf("AT+LINK\r\n");
			}else{
				openLock();//管理员开锁
			}
		}else{
			*CH_PD.O=1;//WIFI上电
		}
	}
}

void USART1_Do(char* msg, u16 len){
}
void USART2_Do(char* msg, u16 len){
	if(usart2.rx.buf[0]=='T' && usart2.rx.buf[1]=='A' && usart2.rx.buf[2]=='+'){
		if(usart2.rx.buf[3]=='o' && usart2.rx.buf[4]=='p' && usart2.rx.buf[5]=='e' && usart2.rx.buf[6]=='n'){//开锁
			openLock();
			*CH_PD.O=0;//WIFI断电
			displayLed(LED0,1);//LED灭
		}else if(usart2.rx.buf[3]=='o' && usart2.rx.buf[4]=='n' && usart2.rx.buf[5]=='\n'){//设备上线
			displayLed(LED0,0);//LED亮
		}else if(usart2.rx.buf[3]=='o' && usart2.rx.buf[4]=='f' && usart2.rx.buf[5]=='f'){//设备关机
			*CH_PD.O=0;//WIFI断电
			displayLed(LED0,1);//LED灭
		}else if(usart2.rx.buf[3]=='f' && usart2.rx.buf[4]=='i' && usart2.rx.buf[5]=='n' && usart2.rx.buf[6]=='d'){//进入微信发现
			displayLed(LED0,-1,2,500);//2次闪烁 2s
		}/*else if(usart2.rx.buf[3]=='s' && usart2.rx.buf[4]=='c' && usart2.rx.buf[5]=='o' && usart2.rx.buf[6]=='k'){//配网成功
			*CH_PD.O=0;//WIFI断电
			displayLed(LED0,1);//LED灭
		}*/
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
