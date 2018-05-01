#include "function.hpp"

//GPIO
Gpio K1(PB, 6);
Gpio K2(PB, 7);
Gpio K3(PB, 8);
Gpio CH_PD(PA, 1);//ESP8266 高 工作；低 断电
Gpio WIFI_RST(PA, 4);//ESP8266 高 工作；低 重启
Gpio O1(PB, 14);
Gpio O2(PB, 15);
Gpio O3(PB, 13);
Gpio O4(PB, 12);

//全局变量
char state[5]="0000";
Gpio relay[4]={O1,O2,O3,O4};

//用户函数
void myTest(){
	usart1.printf("hello:%d\r\n",RunTime);
}
