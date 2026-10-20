#include "stm32f10x.h"
#include "MySPI.h"
#include "LCD.h"
#include "LCD_Reg.h"
#include "Delay.h"


/**
  * @brief  LCD初始换，GPIO配置->LCD_IC配置
  */
void LCD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	MySPI_Init();								// GPIO引脚已在这里初始化了
	
	SPI1_RST_SET;
	Delay_ms(50);
	SPI1_RST_CLR;
	Delay_ms(200);
	SPI1_RST_SET;
	Delay_ms(200);
	
	LCD_WriteComm(SLEEP_OUT);        			// 退出睡眠模式
    Delay_ms(50);                     		  	// 等待显示屏唤醒
    
    LCD_WriteComm(GAMMA_SET);        			// 设置默认伽马曲线
    LCD_WriteData(0x08);						// 共有01h，02h，04h，08h4种选择
    
    LCD_WriteComm(FRAME_RATE_CONTROL_NORMAL);	// 设置帧率
    LCD_WriteData(0x11);
    LCD_WriteData(0x14);
    
    LCD_WriteComm(POWER_CONTROL1); 			 	// 设置VRH和VC参数
    LCD_WriteData(0x1D);
    LCD_WriteData(0x03);
    
    LCD_WriteComm(POWER_CONTROL2);   			// 设置BT参数
    LCD_WriteData(0x04);            			// 0x04
    
    LCD_WriteComm(VCOM_CONTROL1);    			// 设置VMH和VML参数
    LCD_WriteData(0x48);         			
    LCD_WriteData(0x3C);             			
    
    LCD_WriteComm(VCOM_OFFSET_CONTROL);  		// VCOM偏移控制
    LCD_WriteData(0x00);
    
    LCD_WriteComm(INTERFACE_PIXEL_FORMAT);  	// 设置色彩格式
    LCD_WriteData(0x55);            			// 16位色(RGB565)
    
    LCD_WriteComm(COLUMN_ADDRESS_SET);  		// 设置列地址范围
    LCD_WriteData(0x00);             			// 起始列高8位
    LCD_WriteData(0x00);             			// 起始列低8位
    LCD_WriteData(0x00);             			// 结束列高8位
    LCD_WriteData(0x7F);             			// 结束列低8位(127)
    
    LCD_WriteComm(PAGE_ADDRESS_SET);    		// 设置页地址范围
    LCD_WriteData(0x00);						// 起始页高8位
    LCD_WriteData(0x00);             			// 起始页低8位
    LCD_WriteData(0x00);             			// 结束页高8位
    LCD_WriteData(0x7F);             			// 结束页低8位(127)
    
    LCD_WriteComm(MEMORY_ACCESS_CONTROL); 		// 设置扫描方向
    LCD_WriteData(0x08);          				// 0xC8表示特定的扫描方向配置
    
    LCD_WriteComm(SOURCE_DRIVER_DIRECTION_CTRL);// 设置源极驱动方向
    LCD_WriteData(0x00);
	
    LCD_WriteComm(GAM_R_SEL);        			// 启用伽马校正
    LCD_WriteData(0x01);
    
    LCD_WriteComm(POSITIVE_GAMMA_CORRECTION);  // 正向伽马校正参数
    LCD_WriteData(0x36); // p1
    LCD_WriteData(0x29); // p2
    LCD_WriteData(0x12); // p3
    LCD_WriteData(0x22); // p4
    LCD_WriteData(0x1C); // p5
    LCD_WriteData(0x15); // p6
    LCD_WriteData(0x42); // p7
    LCD_WriteData(0xB7); // p8
    LCD_WriteData(0x2F); // p9
    LCD_WriteData(0x13); // p10
    LCD_WriteData(0x12); // p11
    LCD_WriteData(0x0A); // p12
    LCD_WriteData(0x11); // p13
    LCD_WriteData(0x0B); // p14
    LCD_WriteData(0x06); // p15
    
    LCD_WriteComm(NEGATIVE_GAMMA_CORRECTION);  // 负向伽马校正参数
    LCD_WriteData(0x09); // p1
    LCD_WriteData(0x16); // p2
    LCD_WriteData(0x2D); // p3
    LCD_WriteData(0x0D); // p4
    LCD_WriteData(0x13); // p5
    LCD_WriteData(0x15); // p6
    LCD_WriteData(0x40); // p7
    LCD_WriteData(0x48); // p8
    LCD_WriteData(0x53); // p9
    LCD_WriteData(0x0C); // p10
    LCD_WriteData(0x1D); // p11
    LCD_WriteData(0x25); // p12
    LCD_WriteData(0x2E); // p13
    LCD_WriteData(0x34); // p14
    LCD_WriteData(0x39); // p15

    LCD_WriteComm(DISPLAY_ON);       			// 开启显示
    LCD_WriteComm(MEMORY_WRITE);    			// 准备写入显示数据
}

/**
  * @brief  向屏幕填纯色
  * @param  16位颜色数据
  * @note   数据格式位 16bits 5-6-5 RGB
  */
void LCD_ShowColor(uint16_t color)
{
	SPI1_SS_CLR;
	SPI1_SDA_SET;
	for(uint8_t i = 0 ; i < 128; i++)
	{
		for(uint8_t j = 0; j < 128; j++)
		{
			LCD_WriteData(color >> 8);
			LCD_WriteData(color);
		}
	}
	SPI1_SS_SET;
}
