#ifndef _SERIAL_H
#define _SERIAL_H

void Serial_Init(void);
	
// 通过串口发送单个字节
void Serial_SendByte(uint16_t Byte);

// 发送数组，需传入具体数组及长度
void Serial_SendArray(uint8_t *Array, uint16_t Length);

// 发送字符串
void Serial_SendString(char *String);

// 发送十进制数字
void Serial_SendNumber(uint32_t Number, uint8_t Length);

// 返回Serial_RxFlag的状态（1为读取了数据）
uint8_t Serial_GetRxFlag(void);
	
// 返回Serial_RxData（如果读取到了数据）
uint8_t Serial_GetRxData(void);

void Serial_SendHex16(uint16_t HexData);

#endif
