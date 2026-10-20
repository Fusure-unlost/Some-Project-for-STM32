#include "stm32f10x.h"
#include "MyGPIO_Module.h"
#include "MySPI.h"

/*
这是适配于 ILI9361 128*128 LCD 彩屏的软件模拟三线SPI，非常规SPI
*/

/********** 硬件控制 **********/

/**
  * @brief  SPI初始化函数
  * @note 	如果要修改SPI的具体配置，请修改具体的宏定义
  */
void MySPI_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	G_Init(SPI1_SS_PORT, SPI1_SS_PIN, GPIO_Mode_Out_PP);		// 推挽输出，CS
	G_Init(SPI1_MISO_PORT, SPI1_MISO_PIN, GPIO_Mode_Out_PP);	// 推挽输出，DO、SCK
	G_Init(SPI1_MOSI_PORT, SPI1_MOSI_PIN, GPIO_Mode_Out_PP);	// 推挽输出，DI、RES
	G_Init(SPI1_SCK_PORT, SPI1_SCK_PIN, GPIO_Mode_Out_PP);		// 推挽输出，SCK
	
	MySPI_W_SS(1);											// 给片选默认高电平
	MySPI_W_SCK(1);
}

void MySPI_W_SS(uint8_t BitValue);
void MySPI_W_SCK(uint8_t BitValue);
void MySPI_W_MISO(uint8_t BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
/**
  * @brief  写SPI软件片选
  * @param  SS脚输出的电平，置0使能芯片
  * @note 	
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_PinSwitch(SPI1_SS_PORT, SPI1_SS_PIN, (BitAction)BitValue);
}

/**
  * @brief  写SPI软件时钟
  * @param  时钟脚输出的电平
  * @note 	
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_PinSwitch(SPI1_SCK_PORT, SPI1_SCK_PIN, (BitAction)BitValue);
}

/**
  * @brief  写SPI软件输出
  * @param  DO脚输出的电平
  * @note 	
  */
void MySPI_W_MISO(uint8_t BitValue)
{
	GPIO_PinSwitch(SPI1_MISO_PORT, SPI1_MISO_PIN, (BitAction)BitValue);
}

/**
  * @brief  写SPI软件输入
  * @param  DI脚输出的电平，置0使能芯片
  * @note 	
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_PinSwitch(SPI1_MOSI_PORT, SPI1_MOSI_PIN, (BitAction)BitValue);
}


/********** 功能函数 ***********/
/**
  * @brief  SPI起始信号
  * @note   SS脚输出的电平，置0启用芯片
  */
void MySPI_Start()
{
	SPI1_SS_CLR;
}

/**
  * @brief  SPI终止信号
  * @note   SS脚输出的电平，置1禁用芯片
  */
void MySPI_Stop()
{
	SPI1_SS_SET;
}

/**
  * @brief  交换字节，高位先行（别问我为什么不用循环，这个发送完整一帧要0.07s，循环要0.2s）
  * @param  需要交换的字节
  * @note   SPI的数据收发是通过字节交换实现的
  */
void MySPI_SwapByte(uint8_t ByteSend)
{
    SPI1_SCK_CLR; if(ByteSend & 0x80) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x40) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x20) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x10) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x08) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x04) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x02) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
    SPI1_SCK_CLR; if(ByteSend & 0x01) SPI1_SDA_SET; else SPI1_SDA_CLR; SPI1_SCK_SET;
}

/**
  * @brief  写指令，在发送8位指令前需要向数据脚发送D/C位（此处置0）
  * @param  需要交换的字节
  * @note   SPI的数据收发是通过字节交换实现的
  */
void LCD_WriteComm(uint8_t Data)
{
	SPI1_SS_CLR;
	SPI1_SDA_CLR;
	SPI1_SCK_CLR;
	SPI1_SCK_SET;
	MySPI_SwapByte(Data);
	SPI1_SS_SET;
}

  /**
  * @brief  写数据，在发送8位数据前需要向数据脚发送D/C位（此处置1）
  * @param  需要交换的字节
  * @note   SPI的数据收发是通过字节交换实现的
  */
void LCD_WriteData(uint8_t Data)
{
	SPI1_SS_CLR;
	SPI1_SDA_SET;
	SPI1_SCK_CLR;
	SPI1_SCK_SET;
	MySPI_SwapByte(Data);
	SPI1_SS_SET;
}






