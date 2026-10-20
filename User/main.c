#include "stm32f10x.h"
#include "MyGPIO_Module.h" // V1.1版本
#include "LCD.h"
#include "Delay.h"
#include "LCD_Reg.h"
#include "MySPI.h"
#include "Serial.h"



int main(void) 
{
	RCC_APB2PeriphClockCmd(
		RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,
		ENABLE);
	
	Serial_Init();
	LCD_Init();
	Delay_ms(100);
	
    LCD_WriteComm(COLUMN_ADDRESS_SET);
	LCD_WriteData(COLUMN_START >> 8);
	LCD_WriteData(COLUMN_START);
	LCD_WriteData(COLUMN_END >> 8);
	LCD_WriteData(COLUMN_END);
	
    LCD_WriteComm(PAGE_ADDRESS_SET);
	LCD_WriteData(PAGE_START >> 8);
	LCD_WriteData(PAGE_START);
	LCD_WriteData(PAGE_END >> 8);
	LCD_WriteData(PAGE_END);
	SPI1_SDA_CLR;

	LCD_WriteComm(MEMORY_WRITE);

	uint16_t color = 0x0000;
	uint8_t times = 0;
	
	LCD_ShowColor(0xffff);
	Delay_ms(2000);

	while(1) 
	{
		switch(times)
		{
        // 黑 -> 蓝 渐变（增加蓝色分量）
        case 0:  color = 0x0000; LCD_ShowColor(color); times++; break;  // 黑色
        case 1:  color = 0x0001; LCD_ShowColor(color); times++; break;
        case 2:  color = 0x0003; LCD_ShowColor(color); times++; break;
        case 3:  color = 0x0007; LCD_ShowColor(color); times++; break;
        case 4:  color = 0x000F; LCD_ShowColor(color); times++; break;
        case 5:  color = 0x001F; LCD_ShowColor(color); times++; break;  // 蓝色
        
        // 蓝 -> 青 渐变（增加绿色分量）
        case 6:  color = 0x003F; LCD_ShowColor(color); times++; break;
        case 7:  color = 0x007F; LCD_ShowColor(color); times++; break;
        case 8:  color = 0x00FF; LCD_ShowColor(color); times++; break;
        case 9:  color = 0x01FF; LCD_ShowColor(color); times++; break;
        case 10: color = 0x03FF; LCD_ShowColor(color); times++; break;
        case 11: color = 0x07FF; LCD_ShowColor(color); times++; break;  // 青色
        
        // 青 -> 绿 渐变（减少蓝色分量）
        case 12: color = 0x07FE; LCD_ShowColor(color); times++; break;
        case 13: color = 0x07FC; LCD_ShowColor(color); times++; break;
        case 14: color = 0x07F8; LCD_ShowColor(color); times++; break;
        case 15: color = 0x07F0; LCD_ShowColor(color); times++; break;
        case 16: color = 0x07E0; LCD_ShowColor(color); times++; break;  // 绿色
        
        // 绿 -> 黄 渐变（增加红色分量）
        case 17: color = 0x0FE0; LCD_ShowColor(color); times++; break;  // 0x0F E0
        case 18: color = 0x1FE0; LCD_ShowColor(color); times++; break;
        case 19: color = 0x3FE0; LCD_ShowColor(color); times++; break;
        case 20: color = 0x5FE0; LCD_ShowColor(color); times++; break;
        case 21: color = 0x7FE0; LCD_ShowColor(color); times++; break;
        case 22: color = 0x9FE0; LCD_ShowColor(color); times++; break;
        case 23: color = 0xBFE0; LCD_ShowColor(color); times++; break;
        case 24: color = 0xDFE0; LCD_ShowColor(color); times++; break;
        case 25: color = 0xFFE0; LCD_ShowColor(color); times++; break;  // 黄色
        
        // 黄 -> 红 渐变（减少绿色分量）
        case 26: color = 0xFFC0; LCD_ShowColor(color); times++; break;
        case 27: color = 0xFF80; LCD_ShowColor(color); times++; break;
        case 28: color = 0xFF00; LCD_ShowColor(color); times++; break;
        case 29: color = 0xFE00; LCD_ShowColor(color); times++; break;
        case 30: color = 0xFC00; LCD_ShowColor(color); times++; break;
        case 31: color = 0xF800; LCD_ShowColor(color); times++; break;  // 红色
        
        // 红 -> 品红 渐变（增加蓝色分量）
        case 32: color = 0xF801; LCD_ShowColor(color); times++; break;
        case 33: color = 0xF803; LCD_ShowColor(color); times++; break;
        case 34: color = 0xF807; LCD_ShowColor(color); times++; break;
        case 35: color = 0xF80F; LCD_ShowColor(color); times++; break;
        case 36: color = 0xF81F; LCD_ShowColor(color); times++; break;  // 品红
        
        // 品红 -> 黑 渐变（减少红和蓝分量）
        case 37: color = 0xE01E; LCD_ShowColor(color); times++; break;
        case 38: color = 0xC01C; LCD_ShowColor(color); times++; break;
        case 39: color = 0xA01A; LCD_ShowColor(color); times++; break;
        case 40: color = 0x8018; LCD_ShowColor(color); times++; break;
        case 41: color = 0x6016; LCD_ShowColor(color); times++; break;
        case 42: color = 0x4014; LCD_ShowColor(color); times++; break;
        case 43: color = 0x2012; LCD_ShowColor(color); times++; break;
        case 44: color = 0x0010; LCD_ShowColor(color); times++; break;
        case 45: color = 0x0000; LCD_ShowColor(color); times++; break;  // 回到黑色
        
        default: times = 0; break;  // 循环渐变
    }
        
		Delay_ms(100);
		Serial_SendByte(1);
		
    }
}
