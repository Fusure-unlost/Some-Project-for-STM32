#include "stm32f10x.h"
#include "MyGPIO_Module.h" // V1.1版本

uint16_t Serial_RxData;// 用于存放读取的数据
uint8_t Serial_RxFlag;// 用于读取完成的标志位

/*
sarial port 串口通信

            PCLK2/1
          波特率发生器
          v            v
    发送控制器        接受控制器
          v            v
    发送数据寄存器  数据移位寄存器
        TDR            
          V            v
    发送移位寄存器  接受数据寄存器
                    RDR
          v            v
        GPIO       GPIO

注：USART1_TX固定为pa9，USART1_RX固定为pa10
流控模式：为防止接受端处理数据过慢，由接收端主动发出接受数据请求的模式
奇偶校验：用所传输的“1”的数量进行校验，抗干扰（如奇校验，单数校验为置0，偶数置1）
*/

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    G_Init(GPIOA,9,GPIO_Mode_AF_PP);// pa9，数据输出（复用推挽输出模式）
    G_Init(GPIOA,10,GPIO_Mode_IPU);// pa10，数据输入（上拉输入）
    
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 921600;// 波特率（stm32为确保接受数据的准确性，实际采样率为该值的16倍）
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;// 不使用流控模式
    USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;// 发送模式与接受模式
    USART_InitStruct.USART_Parity = USART_Parity_No;// 不（奇偶）校验
    USART_InitStruct.USART_StopBits = USART_StopBits_1;// 一位停止位
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;// 由于不校验，数据长度为8（刚好一个字节）
    USART_Init(USART1,&USART_InitStruct);
    
    // 以下为中断部分（用于接受数据）
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);// 开启RXNE到NVIC的通道
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;// 中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//通道使能
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//响应优先级
    NVIC_Init(&NVIC_InitStruct);

    USART_Cmd(USART1,ENABLE);
}

// 通过串口发送单个字节
void Serial_SendByte(uint16_t Byte)
{
    USART_SendData(USART1,Byte);
    // 等待发送寄存器清空，不需要手动清零标志位
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

// 发送数组，需传入具体数组及长度
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    for(uint16_t i = 0; i < Length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}

// 发送字符串
void Serial_SendString(char *String)
{
    // 由于字符串结尾自带一个“NULL”（ASCII表为 0），固用其作为结束标志位
    for (uint8_t i = 0; String[i] != '\0'; i++)// \0表示转义为空字符，可直接写0
    {
        Serial_SendByte(String[i]);
    }
}

// 发送十进制数字
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint32_t divisor = 1;
    
    // 计算数据位数
    for (uint8_t i = 0; i < Length - 1; i++)
    {
        divisor *= 10;
    }
    // 逐位发送数据（由高到低）
    for(uint8_t i = 0; i < Length ; i++)
    {
        Serial_SendByte((Number / divisor) + 0x30);// 偏移至0（ASCII），确保正确表示数字（可用'0'替代）
        Number = Number % divisor;
        divisor /= 10;// 将位数减一，用于下次循环，避免重复计算
    }
}

/**
  * @brief  串口发送16位十六进制数（以4个字符形式，如0x1234发送为"1234"，0x00AB发送为"00AB"）
  * @param  HexData：要发送的16位十六进制数（范围0x0000~0xFFFF）
  * @note   8位数据（如0xCD）传入时，会自动按16位处理为"00CD"，兼容8位场景
  */
void Serial_SendHex16(uint16_t HexData)
{
    uint8_t nibbles[4]; // 存储4个十六进制位（高到低：bit15-12、bit11-8、bit7-4、bit3-0）
    
    // 拆分16位数据为4个4位半字节（nibble）
    nibbles[0] = (HexData >> 12) & 0x0F; // 高4位（bit15-12）
    nibbles[1] = (HexData >> 8) & 0x0F;  // 次高4位（bit11-8）
    nibbles[2] = (HexData >> 4) & 0x0F;  // 次低4位（bit7-4）
    nibbles[3] = HexData & 0x0F;         // 低4位（bit3-0）
    
    // 逐个转换为ASCII并发送
    for (uint8_t i = 0; i < 4; i++)
    {
        if (nibbles[i] < 10)
        {
            // 0-9转换为'0'-'9'
            Serial_SendByte(nibbles[i] + '0');
        }
        else
        {
            // 10-15转换为'A'-'F'
            Serial_SendByte(nibbles[i] + 'A' - 10);
        }
    }
}

/*
//以下为主动查询的方法，仅作展示
uint16_t RxData;

if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)// 查询输入寄存器标志位
{
    RxData = USART_ReceiveData(USART1);// 储存输入的数据
}
*/

// 返回Serial_RxFlag的状态（1为读取了数据）
uint8_t Serial_GetRxFlag(void)
{
    if (Serial_RxFlag == 1)
    {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

// 返回Serial_RxData（如果读取到了数据）
uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}

// 中断函数固定名，读取输入寄存器，如果有数据就保存到变量Serial_RxData
void USART1_IRQHandler(void)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)// 查询输入寄存器标志位
    {
        Serial_RxData = USART_ReceiveData(USART1);// 储存输入的数据
        Serial_RxFlag = 1;// 读取标志位置1
        USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);// 手动清除标志位，如果读取了DR会自动清除
    }
}




