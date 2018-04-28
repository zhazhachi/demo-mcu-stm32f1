#ifndef __SETUP_H
#define __SETUP_H
#include "sys.hpp"
#include "function.hpp"

void setupRCC(void);
void setupOther(void);
void setupGPIO(void);
void setupCOM(void);
void setup(void);
void loop(void);
#endif //__SETUP_H
