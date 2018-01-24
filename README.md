# rise0chen/demo-mcu-stm32f1
### 基于[C++函数库](https://gitee.com/rise0chen/lib-mcu-stm32f1)的STM32F1系列mcu的MDK5工程示例
### 每秒超声波测距一次，按键后，通过PWM控制机械臂的舵机转动。

## 引脚定义
GPIO|GPIO_Name   |GPIO_Mode|备注
:---|:-----------|:--------|:----
B8  |TRIG        |推挽输出 |
B9  |ECHO        |上拉输入 |
A11 |K1          |下拉输入 |
A15 |K2          |下拉输入 |
B12 |O1          |推挽输出 |
B15 |O2          |推挽输出 |
A0  |PWM0        |复用开漏 |
A1  |PWM1        |复用开漏 |
A6  |PWM2        |复用开漏 |
A7  |PWM3        |复用开漏 |
B0  |PWM4        |复用开漏 |
B1  |PWM5        |复用开漏 |
 A13|SWDIO       |默认方式 |SWD下载口
 A14|SWDCLK      |默认方式 |SWD下载口
 B2 |BOOT1       |默认方式 |恒为低电平
 C14|OSC32_IN    |默认方式 |32.768K晶振输入端
 C15|OSC32_OUT   |默认方式 |32.768K晶振输出端
 D0 |OSC_IN      |默认方式 |8M晶振输入端
 D1 |OSC_OUT     |默认方式 |8M晶振输出端


## 使用步骤
``` bash
git clone -b eg.ultrasonic git@gitee.com:rise0chen/demo-mcu-stm32f1.git
cd ./demo-mcu-stm32f1
git submodule update --init --recursive
```

## 指令集


## 备注
\r\n
0x0D 0x0A
回车 换行
