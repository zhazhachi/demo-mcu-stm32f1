#include "./fiipTask.h"
#include "../config.h"
#include "./function.hpp"
#include "fiip-base/fiip.h"
#include "fiip-link/linkUsart.h"
#include "fiip-protocol/stdp.h"
#include "pwr.hpp"

static StdpStruct* txd;
static uint8_t cmd_body[64];

void funListener0xFFFF(Stdp_FieldStruct* msg) {
  if (msg->cmd[0] & 0x80) {
    if (msg->body[2] != 0x00) {
      printf("stdp error code: %02X.\n", msg->body[2]);
      msg->cmd[0] = 0x00;
      msg->cmd[1] = 0x00;
    }
  }
}
void funListener0xF011(Stdp_FieldStruct* msg) {
  config_setMyId(&msg->body[3]);
  config_setMyKey(&msg->body[11]);
  config_setMyStatus(1, 0x89);
  pwr::reset();
}
void funListener0xF012(Stdp_FieldStruct* msg) {
  printf("login success.\n");
}
void funListener0xF016(Stdp_FieldStruct* msg) {
  printf("binding code is: %02X%02X%02X%02X.\n", msg->body[3], msg->body[4],
         msg->body[5], msg->body[6]);
}
void funListener0x7811(Stdp_FieldStruct* msg) {
  printf("be bound: %02X%02X%02X%02X%02X%02X%02X%02X.\n", msg->body[0],
         msg->body[1], msg->body[2], msg->body[3], msg->body[4], msg->body[5],
         msg->body[6], msg->body[7]);
  msg->cmd[0] = 0xF8;
  stdp_setVar(txd, stdp_field_cmd, msg->cmd, 2);
  memcpy(&cmd_body[0], msg->index, 2);
  cmd_body[2] = 0x00;
  stdp_setVar(txd, stdp_field_body, cmd_body, 3);
  fiip_send(txd->frame, msg->srcAddr, NULL);
}
void funListener0x7812(Stdp_FieldStruct* msg) {
  printf("be unbound: %02X%02X%02X%02X%02X%02X%02X%02X.\n", msg->body[3],
         msg->body[4], msg->body[5], msg->body[6], msg->body[7], msg->body[8],
         msg->body[9], msg->body[10]);
  msg->cmd[0] = 0xF8;
  stdp_setVar(txd, stdp_field_cmd, msg->cmd, 2);
  memcpy(&cmd_body[0], msg->index, 2);
  cmd_body[2] = 0x00;
  stdp_setVar(txd, stdp_field_body, cmd_body, 3);
  fiip_send(txd->frame, msg->srcAddr, NULL);
}
void funListener0x7822(Stdp_FieldStruct* msg) {
  if (msg->body[1] == 0x01) {
    setVar(0x01, msg->body[3]);

    msg->cmd[0] = 0xF8;
    stdp_setVar(txd, stdp_field_cmd, msg->cmd, 2);
    memcpy(&cmd_body[0], msg->index, 2);
    cmd_body[2] = 0x00;
    stdp_setVar(txd, stdp_field_body, cmd_body, 3);
    fiip_send(txd->frame, msg->srcAddr, NULL);
  }
}

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
  uint8_t dev[] = "2";

  fiip_init();
  fiip_setId(config.myId);

  stdp_start();
  stdp_addListener(0xFFFF, funListener0xFFFF);
  stdp_addListener(0xF011, funListener0xF011);
  stdp_addListener(0xF012, funListener0xF012);
  stdp_addListener(0xF016, funListener0xF016);
  stdp_addListener(0x7811, funListener0x7811);
  stdp_addListener(0x7812, funListener0x7812);
  stdp_addListener(0x7822, funListener0x7822);
  
  startUsart(dev, 9600);
  fiip_connectCloud();
  fiipCloud_init(config.myId, config.myKey);
}
