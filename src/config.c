#include "./config.h"
#include "flash.h"
Config config;

void config_init() {
  static uint8_t myTypeId[TypeIdLen] = {0x00, 0x00, 0x02, 0x01};  //智能模块
  static uint8_t myTypeKey[KeyLen] = {0x2A, 0x64, 0xE8, 0xDA};

  flash_read(FLASH_ADDR_START, &config, sizeof(config));  //读取设备信息
  memcpy(config.myTypeId, myTypeId, TypeIdLen);
  memcpy(config.myTypeKey, myTypeKey, KeyLen);
  if (config.myStatus[1] != 0x89) {
    uint8_t* uid = (uint8_t*)malloc(1);
    config.myId[0] = (((int)uid) >> 24) | 0x80;
    config.myId[1] = ((int)uid) >> 16;
    config.myId[2] = ((int)uid) >> 8;
    config.myId[3] = ((int)uid) >> 0;
    config.myId[4] = ((int)&uid) >> 24;
    config.myId[5] = ((int)&uid) >> 16;
    config.myId[6] = ((int)&uid) >> 8;
    config.myId[7] = ((int)&uid) >> 0;
    free(uid);
  }
}
void config_reset() {
  config_setMyStatus(0, 0x00);
  config_setMyStatus(1, 0x00);
  config_setMyStatus(0, 0x9A);
}
void config_setMyStatus(uint8_t index, uint8_t status) {
  config.myStatus[index] = status;

  flash_write(FLASH_ADDR_START, &config, sizeof(config));
}
void config_setMyId(uint8_t* id) {
  memcpy(config.myId, id, IdLen);
  flash_write(FLASH_ADDR_START, &config, sizeof(config));
}
void config_setMyKey(uint8_t* key) {
  memcpy(config.myKey, key, KeyLen);
  flash_write(FLASH_ADDR_START, &config, sizeof(config));
}
