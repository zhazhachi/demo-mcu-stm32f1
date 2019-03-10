/*************************************************
Copyright (C), 2018-2028, Crise Tech. Co., Ltd.
File name: config.h
Author: rise0chen
Version: 1.0
Date: 2018.4.26
Description: 用户配置文件
History:
        rise0chen   2018.4.26   创建用户配置文件
*************************************************/
#ifndef __CONFIG_H
#define __CONFIG_H
#include <stdint.h>

#define I2C_ADDR_MPU6050 0x68

typedef struct {
#define myStatusLen 2
#define TypeIdLen 4
#define IdLen 8
#define KeyLen 4
  uint8_t myStatus[myStatusLen];
  uint8_t myTypeId[TypeIdLen];
  uint8_t myTypeKey[KeyLen];
  uint8_t myId[IdLen];
  uint8_t myKey[KeyLen];
} Config;

extern Config config;

void config_init(void);
void config_reset(void);
void config_setMyStatus(uint8_t index, uint8_t status);
void config_setMyId(uint8_t* id);
void config_setMyKey(uint8_t* key);

#endif  //__CONFIG_H
