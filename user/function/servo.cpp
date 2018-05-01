#include "servo.hpp"

namespace servo{
	void  config(){
		rcc.cmd(1, APB1_TIM3,ENABLE);
		PWM.config(P_PPAF,P_50MHz);
		tim3.config(7200,200,0);//定时器周期
		tim3.configOC(2,0);
		
		TIM3->CR1 |= 1;//使能
		Close();
	}
	void  Open(){
		TIM3->CCR1 = 24;
		delay(3000);
		TIM3->CCR1 = 0;
	}
	void  Close(){
		TIM3->CCR1 = 6;
		delay(3000);
		TIM3->CCR1 = 0;
	}
}
