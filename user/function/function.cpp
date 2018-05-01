/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: function.cpp
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 定义用户函数
History: 
	rise0chen   2018.4.26   编写注释
*************************************************/
#include "function.hpp"

/***  定义IO口(别忘记在function.hpp中引用)  ***/

/*  定义全局变量(别忘记在function.hpp中引用)  */

/*  定义用户函数(别忘记在function.hpp中引用)  */
void myTest(){
	can.tx.IDE = CAN_Id_Extended;
	can.tx.RTR = CAN_RTR_Data;
	can.tx.ExtId = 0x1821FDFA;
	can.tx.DLC = 5;
	can.tx.Data[0] = 0x41;
	can.tx.Data[1] = 0x1F;
	can.tx.Data[2] = 0xC2;
	can.tx.Data[3] = 0x31;
	can.tx.Data[4] = 0x03;
	can.send(&can.tx);
}
