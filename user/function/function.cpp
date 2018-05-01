#include "function.hpp"

//GPIO
Gpio TRIG(PB,8);
Gpio ECHO(PB,9);
Gpio K1(PA, 11);
Gpio K2(PA, 15);
Gpio O1(PB, 12);
Gpio O2(PB, 15);
Gpio PWM0(PA,0);
Gpio PWM1(PA,1);
Gpio PWM2(PA,6);
Gpio PWM3(PA,7);
Gpio PWM4(PB,0);
Gpio PWM5(PB,1);

//全局变量
Ultrasonic ultrasonic(&TRIG, &ECHO);

//用户函数
void myArmInit(){
	rcc.cmd(1, APB1_TIM2,ENABLE);
	Gpio(PA,0).config(P_ODAF,P_50MHz);
	Gpio(PA,1).config(P_ODAF,P_50MHz);
	tim2.config(7200,200,0);//定时器周期
	tim2.configOC(1,0);
	tim2.configOC(2,0);
	TIM2->CR1 |= 1;//使能
	
	rcc.cmd(1, APB1_TIM3,ENABLE);
	Gpio(PA,6).config(P_ODAF,P_50MHz);
	Gpio(PA,7).config(P_ODAF,P_50MHz);
	Gpio(PB,0).config(P_ODAF,P_50MHz);
	Gpio(PB,1).config(P_ODAF,P_50MHz);
	tim3.config(7200,200,0);//定时器周期
	tim3.configOC(1,0);
	tim3.configOC(2,0);
	tim3.configOC(3,0);
	tim3.configOC(4,0);
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
		ultrasonic.ranging();
		distance0=ultrasonic.distance;
		if(distance0>110 && distance0<145){
			*O1.O=1;//LED1灭
			*O2.O=0;//LED2亮
		}
		delay_ms(4000);//4s
		ultrasonic.ranging();
		distance1=ultrasonic.distance;
		if(distance1>110 && distance1<145){
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
	do{//等待车辆到0.4米之外
		delay_ms(5000);//5s
		ultrasonic.ranging();
		distance0=ultrasonic.distance;
	}while(distance0<400);
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
	ultrasonic.ranging();
	usart1.printf("distance: %d\r\n",ultrasonic.distance);
}
