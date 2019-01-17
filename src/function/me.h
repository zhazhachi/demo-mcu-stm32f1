#ifndef __ME_H
#define __ME_H
#include "sys.h"
#include "./function.h"

typedef struct{
	uint8_t ID[8];
	uint8_t status[4];
}MyInfoStruct;
extern MyInfoStruct me;

#endif //__ME_H
