# rise0chen/demo-mcu-stm32f1
### 基于[C++函数库](https://gitee.com/rise0chen/lib-mcu-stm32f1)的STM32F1系列mcu的MDK5工程示例
### 通过独立按键或wifi控制继电器开关。

## 引脚定义
GPIO|GPIO_Name   |GPIO_Mode|备注
:---|:-----------|:--------|:----
A1  |CH_PD       |推挽输出 |ESP8266电源
A4  |WIFI_RST    |推挽输出 |ESP8266复位
A9  |USATRT1_TX  |开漏输出 |USATRT1_TX
A10 |USATRT1_RX  |浮空输入 |USATRT1_RX
B6  |K1          |下拉输入 |独立按键开关1
B7  |K2          |下拉输入 |独立按键开关2
B8  |K3          |下拉输入 |独立按键开关3
B12 |O4          |推挽输出 |继电器4
B13 |O3          |推挽输出 |继电器3
B14 |O1          |推挽输出 |继电器1
B15 |O2          |推挽输出 |继电器2
 A13|SWDIO       |默认方式 |SWD下载口
 A14|SWDCLK      |默认方式 |SWD下载口
 B2 |BOOT1       |默认方式 |恒为低电平
 C14|OSC32_IN    |默认方式 |32.768K晶振输入端
 C15|OSC32_OUT   |默认方式 |32.768K晶振输出端
 D0 |OSC_IN      |默认方式 |8M晶振输入端
 D1 |OSC_OUT     |默认方式 |8M晶振输出端


## 使用步骤
``` bash
git clone -b eg.SmartPlug git@gitee.com:rise0chen/demo-mcu-stm32f1.git
cd ./demo-mcu-stm32f1
git submodule update --init --recursive
```

## 指令集


## 备注
\r\n
0x0D 0x0A
回车 换行
