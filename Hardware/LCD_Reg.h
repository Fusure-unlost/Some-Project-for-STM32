#ifndef __LCD_REG_H
#define __LCD_REG_H

/* ILI9163C 指令集宏定义 */
#define NOP                             0x00    // 空命令，可用于终止寄存器读写
#define SOFTWARE_RESET                  0x01    // 软件重置
#define READ_DISPLAY_ID_INFO            0x04    // 读取显示器标识（系统）信息
#define READ_DISPLAY_STATUS             0x09    // 读取显示状态
#define READ_DISPLAY_POWER_MODE         0x0A    // 读取显示器电源模式
#define READ_DISPLAY_MADCTL             0x0B    // 读取显示控制相关的状态信息
#define READ_DISPLAY_PIXEL_FORMAT       0x0C    // 读取显示像素格式
#define READ_DISPLAY_IMAGE_MODE         0x0D    // 读取图片输出模式
#define READ_DISPLAY_SIGNAL_MODE        0x0E    // 读取显示信号模式
#define READ_DISPLAY_SIGNAL_MODE2       0x0F    // 读取显示信号模式
#define SLEEP_IN                        0x10    // 进入睡眠模式
#define SLEEP_OUT                       0x11    // 退出睡眠模式
#define PARTIAL_MODE_ON                 0x12    // 局部模式开启
#define NORMAL_DISPLAY_MODE_ON          0x13    // 正常显示模式开启
#define DISPLAY_INVERSION_OFF           0x14    // 从显示反转模式恢复
#define DISPLAY_INVERSION_ON            0x21    // 开启反转
#define GAMMA_SET                       0x26    // 伽马设置
#define DISPLAY_OFF                     0x28    // 显示关闭
#define DISPLAY_ON                      0x29    // 显示开启
#define COLUMN_ADDRESS_SET              0x2A    // 列地址设置（屏幕分辨率设置）
#define PAGE_ADDRESS_SET                0x2B    // 页地址设置（屏幕分辨率设置）
#define MEMORY_WRITE                    0x2C    // 帧存储器写入
#define COLOR_SETTING                   0x2D    // 4K、65K 和 262K 色彩设置
#define MEMORY_READ                     0x2E    // 存储器读取
#define PARTIAL_AREA                    0x30    // 局部区域设置
#define VERTICAL_SCROLLING_DEFINITION   0x33    // 垂直滚动定义
#define TEARING_EFFECT_LINE_OFF         0x34    // 撕裂效果线关闭
#define TEARING_EFFECT_LINE_ON          0x35    // 撕裂效果线开启
#define MEMORY_ACCESS_CONTROL           0x36    // 内存访问控制
#define VERTICAL_SCROLLING_START_ADDR   0x37    // 垂直滚动起始地址
#define IDLE_MODE_OFF                   0x38    // 空闲模式关闭
#define IDLE_MODE_ON                    0x39    // 空闲模式开启
#define INTERFACE_PIXEL_FORMAT          0x3A    // 接口像素格式

#define FRAME_RATE_CONTROL_NORMAL       0xB1    // 帧率控制（正常模式 / 全色彩下使用）
#define FRAME_RATE_CONTROL_IDLE         0xB2    // 帧率控制（空闲模式 / 8色下使用）
#define FRAME_RATE_CONTROL_PARTIAL      0xB3    // 帧率控制（部分模式 / 全色彩下使用）
#define DISPLAY_INVERSION_CONTROL       0xB4    // 显示反转控制
#define RGB_BLANKING_PORCH_SETTING      0xB5    // RGB 接口消隐区间设置
#define DISPLAY_FUNCTION_SET5           0xB6    // 显示功能设置 5
#define SOURCE_DRIVER_DIRECTION_CTRL    0xB7    // 源极驱动方向控制
#define GATE_DRIVER_DIRECTION_CTRL      0xB8    // 栅极驱动方向控制

#define POWER_CONTROL1                  0xC0    // 电源控制 1
#define POWER_CONTROL2                  0xC1    // 电源控制 2
#define POWER_CONTROL3                  0xC2    // 电源控制 3
#define POWER_CONTROL4                  0xC3    // 电源控制 4
#define POWER_CONTROL5                  0xC4    // 电源控制 5
#define VCOM_CONTROL1                   0xC5    // VCOM 控制 1
#define VCOM_CONTROL2                   0xC6    // VCOM 控制 2
#define VCOM_OFFSET_CONTROL             0xC7    // VCOM 偏移控制

#define WRITE_ID4_VALUE                 0xD3    // 写入 ID4 值
#define NV_MEMORY_FUNCTION_CTRL1        0xD5    // 非易失性存储器功能控制器 1	注：该指令的文档中，二进制值位0xDA，但16进制值为0xD5，谨慎使用
#define NV_MEMORY_FUNCTION_CTRL2        0xD6    // 非易失性存储器功能控制器 2	注：该指令的文档中，二进制值位0xDA，但16进制值为0xD6，谨慎使用
#define NV_MEMORY_FUNCTION_CTRL3        0xD7    // 非易失性存储器功能控制器 3	注：该指令的文档中，二进制值位0xDA，但16进制值为0xD7，谨慎使用
#define READ_ID1                        0xDA    // 读取ID1
#define READ_ID2                        0xDB    // 读取ID2
#define READ_ID3                        0xDC    // 读取ID3

#define POSITIVE_GAMMA_CORRECTION       0xE0    // 正向伽马校正设置
#define NEGATIVE_GAMMA_CORRECTION       0xE1    // 负向伽马校正设置
#define DEEP_STANDBY_CONTROL            0xE6    // 深度待机控制

#define GAM_R_SEL                       0xF2    // 伽马选择

/* 常用参数配置 */
#define DUMMMY_8B						0x00	// 无效数据

// 128x128分辨率参数
#define COLUMN_START_128                0x00
#define COLUMN_END_128                  0x7F    // 127
#define PAGE_START_128                  0x00
#define PAGE_END_128                    0x7F    // 127

// 128x160分辨率参数  
#define COLUMN_START_128x160            0x00
#define COLUMN_END_128x160              0x7F    // 127
#define PAGE_START_128x160              0x00
#define PAGE_END_128x160                0x9F    // 159

// 颜色格式
#define PIXEL_FORMAT_16BIT             0x05    // 16位RGB格式
#define PIXEL_FORMAT_18BIT             0x06    // 18位RGB格式

// 帧率控制参数
#define FRAME_RATE_PARAM1              0x11
#define FRAME_RATE_PARAM2              0x14

// 电源控制推荐参数
#define POWER_CTRL1_VRH                0x0C
#define POWER_CTRL1_VC                 0x05
#define POWER_CTRL2_BT                 0x02
#define VCOM_VMH                       0x29    // 3.6V
#define VCOM_VML                       0x43    // -1.0V



#endif
