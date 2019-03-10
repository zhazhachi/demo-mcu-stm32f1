#ifndef __FIIPLISTENER_H
#define __FIIPLISTENER_H
#include "config.h"
#include "function.h"
#include "fiip-base/fiip.h"
#include "fiip-protocol/stdp.h"

void funListener0xFFFF(Stdp_FieldStruct* msg);
void funListener0xF011(Stdp_FieldStruct* msg);
void funListener0xF012(Stdp_FieldStruct* msg);
void funListener0xF016(Stdp_FieldStruct* msg);
void funListener0x7811(Stdp_FieldStruct* msg);
void funListener0x7812(Stdp_FieldStruct* msg);
void funListener0x7822(Stdp_FieldStruct* msg);



#endif  //__FIIPLISTENER_H
