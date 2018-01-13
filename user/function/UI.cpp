#include "UI.hpp"

namespace UI{
	u16 ID=0;//64主界面 99次界面 9交互框
	static u16 oldID;
	
	void show(void){
		static char display[16];
		static u8 i;
		
		
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
}
