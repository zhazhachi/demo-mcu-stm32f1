/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: ans.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 通信指令响应
Usage: 
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "recvHadle.h"
#include "DataFormat.hpp"

void recvHadle_init(void){
	
}
void recvHadle_usart1(u8 res){
	static DataFormat* rx=new DataFormat();
	if(rx->recv(&res,1)==0){
		if (rx->getMsg()) {
			//rx->msg;
		} else {
			//crc error
		}
	}
}
