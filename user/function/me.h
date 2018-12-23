#ifndef __ME_H
#define __ME_H
#include "sys.h"
#include "function.h"

typedef struct{
	u8 ID[8];
	u8 status[4];
}MyInfoStruct;
extern MyInfoStruct me;

#endif //__ME_H
