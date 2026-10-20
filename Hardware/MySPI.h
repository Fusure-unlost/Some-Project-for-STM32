#ifndef __MYSPI_H
#define __MYSPI_H

/*		GPIO引脚初始化		*/
/*
#define SPI1_SS_PORT			GPIOA		// CS	芯片片选（1失能，0使能）
#define SPI1_SS_PIN				GPIO_Pin_4	// 类似I2C的通过地址选中从机
*/
#define SPI1_SS_PORT			GPIOB		// CS	芯片片选（1失能，0使能）
#define SPI1_SS_PIN				GPIO_Pin_8	// 类似I2C的通过地址选中从机

#define SPI1_MISO_PORT		GPIOA		// DO	数据接受
#define SPI1_MISO_PIN			GPIO_Pin_6
#define SPI1_MOSI_PORT		GPIOA		// DI	数据发送
#define SPI1_MOSI_PIN			GPIO_Pin_7
#define SPI1_SCK_PORT			GPIOA		// CLK	时钟
#define SPI1_SCK_PIN			GPIO_Pin_5

/*		用宏定义简化部分函数调用		*/
#define SPI1_SS_SET 		(SPI1_SS_PORT->BSRR = SPI1_SS_PIN)			// 写片选引脚	pb8
#define SPI1_SS_CLR 		(SPI1_SS_PORT->BRR = SPI1_SS_PIN)
#define SPI1_SCK_SET 		(SPI1_SCK_PORT->BSRR = SPI1_SCK_PIN)  		// 写时钟引脚	pa5
#define SPI1_SCK_CLR 		(SPI1_SCK_PORT->BRR = SPI1_SCK_PIN)
#define SPI1_SDA_SET 		(SPI1_MISO_PORT->BSRR = SPI1_MISO_PIN) 		// 写发数据引脚	pa6
#define SPI1_SDA_CLR 		(SPI1_MISO_PORT->BRR = SPI1_MISO_PIN)
#define SPI1_RST_SET		(SPI1_MOSI_PORT->BSRR = SPI1_MOSI_PIN); 	// 写收数据（屏幕重置）引脚 pa7
#define SPI1_RST_CLR		(SPI1_MOSI_PORT->BRR = SPI1_MOSI_PIN);


void MySPI_Init(void);
void MySPI_W_SS(uint8_t BitValue);
void MySPI_W_SCK(uint8_t BitValue);
void MySPI_W_MISO(uint8_t BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
void MySPI_Start(void);
void MySPI_Stop(void);
void MySPI_SwapByte(uint8_t ByteSend);
void LCD_WriteComm(uint8_t Data);
void LCD_WriteData(uint8_t Data);

#endif
