#include "setup.hpp"

int main(void){
	RCC_Setup();
	NVIC_Setup();
	GPIO_Setup();
	Other_Setup();
	COM_Setup();

	setup();
	while(1){
		loop();
	}
}
