#ifndef __SETUP_H
#define __SETUP_H
#include "sys.hpp"
#include "function.hpp"

void setup(void);
void loop(void);
void RCC_Setup(void);
void NVIC_Setup(void);
void GPIO_Setup(void);
void Other_Setup(void);
void COM_Setup(void);
#endif //__SETUP_H
