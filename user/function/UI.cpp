/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: Ui.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 显示屏用户交互界面
Usage: 
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "Ui.hpp"

Ui ui;

void Ui::show(void){
	//static char display[16];
	
	if(oldID!=ID){
		oldID=ID;
		//LCD12864::Clear();
	}
	switch(ID){
		case 0://主界面
			
			break;
		case 1000://输密码
			
			break;
		case 2000://万年历
			
			break;
		case 3000://订单信息
			
			break;
		case 65000://FCT
			
			break;
	}
}
