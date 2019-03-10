#include "./fiipTask.h"
#include "fiip-base/fiip.h"
#include "fiip-link/linkUsart.h"
#include "fiip-protocol/stdp.h"

uint8_t myId[8] = {0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x01};
uint8_t myKey[4] = {0x95, 0x71, 0xF9, 0xAE};

void fiip_connectCloud() {
  uint8_t hostinfo[] = "1";

  LinkCfgStruct* centerServer = (LinkCfgStruct*)malloc(sizeof(LinkCfgStruct));
  centerServer->type = linkType_usart;
  centerServer->address = (uint8_t*)malloc(4);
  memcpy(centerServer->address, hostinfo, 4);
  centerServer->port = 9600;
  fiip_connect(fiip_centerId, centerServer);
  free(centerServer->address);
  free(centerServer);
}

void initFiip() {
  uint8_t dev[] = "1";

  fiip_init();
  fiip_setId(myId, myKey);
  startUsart(dev, 9600);

  fiip_connectCloud();

  stdp_start();
  stdp_addListener(0xFFFF, funListener0xFFFF);
  stdp_addListener(0xF011, funListener0xF011);
  stdp_addListener(0xF012, funListener0xF012);
  stdp_addListener(0xF016, funListener0xF016);
  stdp_addListener(0x7811, funListener0x7811);
  stdp_addListener(0x7812, funListener0x7812);
  stdp_addListener(0x7822, funListener0x7822);

  StdpStruct* txd = stdp_new();
  stdp_setVar(txd, stdp_field_body, dev, 12);
  fiip_send(txd->frame, myId, NULL);
}
