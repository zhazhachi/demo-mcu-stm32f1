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
void startCharge(){
	u32 distance0,distance1;
	
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
}
void finishCharge(){
	u32 distance0;
	
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
}
void myMeasure(){
	ultrasonic::Ranging();
	usart1.printf("distance: %d\r\n",ultrasonic::distance);
}
