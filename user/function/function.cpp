#include "function.hpp"

//GPIO
gpio K1=gpio(PB, 6);
gpio K2=gpio(PB, 7);
gpio K3=gpio(PB, 8);
gpio CH_PD=gpio(PA, 1);//ESP8266 高 工作；低 断电
gpio WIFI_RST=gpio(PA, 4);//ESP8266 高 工作；低 重启
gpio O1=gpio(PB, 14);
gpio O2=gpio(PB, 15);
gpio O3=gpio(PB, 13);
gpio O4=gpio(PB, 12);

//全局变量
char state[5]="0000";
gpio relay[4]={O1,O2,O3,O4};

//用户函数
void myTest(){
	usart1.printf("hello:%d\r\n",RunTime);
}
