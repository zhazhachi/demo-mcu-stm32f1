# rise0chen/demo-mcu-stm32f1
### 基于[C++函数库](https://gitee.com/rise0chen/lib-mcu-stm32f1)的STM32F1系列mcu的MDK5工程示例
### RFID和WIFI控制的智能电子锁。

## 引脚定义
GPIO|GPIO_Name   |GPIO_Mode|备注
:---|:-----------|:--------|:----
A0  |HCSR_05     |下拉输入 |红外人体信号端
A1  |CH_PD       |推挽输出 |ESP电源控制端
A2  |WIFI_RXD    |推挽输出 |
A3  |WIFI_TXD    |浮空输入 |
A4  |BAT_Ctrl    |推挽输出 |电磁锁使能端
A5  |Key         |浮空输入 |WIFI唤醒按键
A6  |PWM         |推挽输出 |舵机信号端
A8  |RF_PST      |推挽输出 |RFID复位端
A9  |USART1_TX   |推挽输出 |
A10 |USART1_RX   |浮空输入 |
A11 |RFPOWER_CTL |推挽输出 |RFID电源控制端
B0  |BAT_AD      |模拟输入 |电池电量采集
B5  |PB5         |预留备用 |
B6  |PB6         |预留备用 |
B7  |PB7         |预留备用 |
B8  |PB8         |预留备用 |
B9  |PB9         |预留备用 |
B10 |SCL         |复用开漏 |
B11 |SDA         |复用输入 |
B12 |SPI2_CS     |推挽输出 |
B13 |SPI2_CLK    |复用推挽 |SPI2
B14 |SPI2_MISO   |复用推挽 |SPI2
B15 |SPI2_MOSI   |复用推挽 |SPI2
 A13|SWDIO       |默认方式 |SWD下载口
 A14|SWDCLK      |默认方式 |SWD下载口
 B2 |BOOT1       |默认方式 |恒为低电平
 C14|OSC32_IN    |默认方式 |32.768K晶振输入端
 C15|OSC32_OUT   |默认方式 |32.768K晶振输出端
 D0 |OSC_IN      |默认方式 |8M晶振输入端
 D1 |OSC_OUT     |默认方式 |8M晶振输出端


## 使用步骤
``` bash
git clone -b eg.SmartLock git@gitee.com:rise0chen/demo-mcu-stm32f1.git
cd ./demo-mcu-stm32f1
git submodule update --init --recursive
```

## 指令集


## 备注
\r\n
0x0D 0x0A
回车 换行
