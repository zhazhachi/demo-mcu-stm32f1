#include "servo.hpp"

namespace servo{
	void  Config(){
		rcc::Cmd(1, APB1_TIM3,ENABLE);
		PWM.Config(P_PPAF,P_50MHz);
		tim3.BaseConfig(7200,200,0);//定时器周期
		tim3.OCConfig(2,0);
		
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
