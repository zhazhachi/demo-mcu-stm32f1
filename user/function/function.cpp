#include "function.hpp"

//GPIO
gpio TRIG=gpio(PB,8);
gpio ECHO=gpio(PB,9);
gpio K1=gpio(PA, 11);
gpio K2=gpio(PA, 15);
gpio O1=gpio(PB, 12);
gpio O2=gpio(PB, 15);
gpio PWM0=gpio(PA,0);
gpio PWM1=gpio(PA,1);
gpio PWM2=gpio(PA,6);
gpio PWM3=gpio(PA,7);
gpio PWM4=gpio(PB,0);
gpio PWM5=gpio(PB,1);

//全局变量

//用户函数
void myArmInit(){
	rcc::Cmd(1, APB1_TIM2,ENABLE);
	gpio(PA,0).Config(P_ODAF,P_50MHz);
	gpio(PA,1).Config(P_ODAF,P_50MHz);
	tim2.BaseConfig(7200,200,0);//定时器周期
	tim2.OCConfig(1,0);
	tim2.OCConfig(2,0);
	TIM2->CR1 |= 1;//使能
	
	rcc::Cmd(1, APB1_TIM3,ENABLE);
	gpio(PA,6).Config(P_ODAF,P_50MHz);
	gpio(PA,7).Config(P_ODAF,P_50MHz);
	gpio(PB,0).Config(P_ODAF,P_50MHz);
	gpio(PB,1).Config(P_ODAF,P_50MHz);
	tim3.BaseConfig(7200,200,0);//定时器周期
	tim3.OCConfig(1,0);
	tim3.OCConfig(2,0);
	tim3.OCConfig(3,0);
	tim3.OCConfig(4,0);
	TIM3->CR1 |= 1;//使能
	
	TIM2->CCR1 = 15;
	TIM2->CCR2 = 6;
	TIM3->CCR1 = 15;
	TIM3->CCR2 = 5;
	TIM3->CCR3 = 11;
	TIM3->CCR4 = 15;
}
void myArmRun(){
	TIM2->CCR1 = 10; //1号舵机
	TIM2->CCR2 = 7; //2号舵机
	TIM3->CCR1 = 15; //3号舵机
	TIM3->CCR2 = 12; //4号舵机
	TIM3->CCR3 = 23; //5号舵机
	TIM3->CCR4 = 9; //6号舵机
	delay_ms(500);
	TIM2->CCR1 = 10; //1号舵机
	TIM2->CCR2 = 8; //2号舵机
	TIM3->CCR1 = 15; //3号舵机
	TIM3->CCR2 = 18; //4号舵机
	TIM3->CCR3 = 22; //5号舵机
	TIM3->CCR4 = 13; //6号舵机
	delay_ms(3000);
	TIM2->CCR1 = 15; //1号舵机
}
void myMeasure(){
	ultrasonic::Ranging();
	usart1.printf("distance: %d\r\n",ultrasonic::distance);
}
