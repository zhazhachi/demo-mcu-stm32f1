#ifndef __ME_H
#define __ME_H
#include "sys.hpp"
#include "function.hpp"

typedef struct{
	u8 ID[8];
	u8 status[4];
}Me_TypeDef;
extern Me_TypeDef me;

#endif //__ME_H
