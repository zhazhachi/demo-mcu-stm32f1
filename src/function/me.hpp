#ifndef __ME_H
#define __ME_H
#include "sys.hpp"
#include "function.hpp"

typedef struct{
	uint8_t ID[8];
	uint8_t status[4];
}Me_TypeDef;
extern Me_TypeDef me;

#endif //__ME_H
