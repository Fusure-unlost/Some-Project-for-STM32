# STM32F103C8T6 - ILI9163 128LCD
Keil MDK5 裸机工程，驱动 ILI9163 128*128 SPI液晶屏幕，本身就一个显示不同颜色的功能

##  目录结构
- Hardware：外设驱动（LCD、SPI、GPIO、串口）
- Library：STM32F10x 标准外设库
- Start：启动文件、内核头文件
- System：系统延时
- Used：可复用模块（PWM、ADC、定时器、串口数据包、计数传感器）
- User：main主函数、中断服务函数

##  编译环境
- Keil MDK uVision5
- 芯片：STM32F103C8T6
- 下载器：ST-Link

##  硬件连接
- SPI驱动ILI9163屏幕


