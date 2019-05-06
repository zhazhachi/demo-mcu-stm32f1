#ifndef __UI_H
#define __UI_H
#include "sys.hpp"
#include "function.hpp"

class Ui{
	public:
		uint16_t ID;//64主界面 99次界面 9交互框
		
		void show(void);
	
	private:
		uint16_t oldID;
};
extern Ui ui;

#endif //__UI_H
