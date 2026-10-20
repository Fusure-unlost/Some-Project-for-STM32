#include "stm32f10x.h" // Device header

//用于led开关状态
#define Bit_RESET 0	
#define Bit_SET 1
//简化GPIO的输入

/*
V1.1
该库统一不做向下兼容
*/

/**
 * @brief LED初始化函数（开楼输出）,该函数用于初始化指定GPIO引脚为开漏输出模式，速度50MHz
 *        适用于驱动LED等简单外设
 * @param GPIOx  GPIO端口指针（如GPIOA、GPIOB等）
 * @param pin    引脚编号（0-15）
 * @note  
 */
void LED_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct; 				// GPIO初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;  	// 开漏输出模式（适合LED驱动，置0点亮）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;           	// 设置目标引脚
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  // 高速模式（确保信号质量）
    
    GPIO_Init(GPIOx, &GPIO_InitStruct);  			// GPIO初始化 应用配置到指定GPIO端口
	GPIO_WriteBit(GPIOx,GPIO_Pin,(BitAction)Bit_SET);
}
	
/**
 * @brief 同上面的led函数，但用的是上拉输入，用于按钮输入
 * @param GPIOx  GPIO端口指针（如GPIOA、GPIOB等）
 * @param pin    引脚编号（0-15）
 * @note  
 */
void KEY_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_InitStruct);
}

/**
 * @brief 简化GPIO_Init函数
 * @param GPIOx  GPIO端口指针（如GPIOA、GPIOB等）
 * @param pin    引脚编号（0-15）
 * @param G_Mode 具体的GPIO模式
 * @note  
 */
void G_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef G_Mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = G_Mode;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_InitStruct);
}

/**
 * @brief GPIO电平切换函数
 * @param GPIOx 	 GPIO端口指针（如GPIOA、GPIOB等）
 * @param pin    	 引脚编号（0-15）
 * @param LED_State  要切换的电平
 * @note  
 */
void GPIO_PinSwitch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction State)
{
	GPIO_WriteBit(GPIOx,GPIO_Pin,(BitAction)State);
}

/**
 * @brief 设置指定GPIO脚的电平状态（置1）
 * @param GPIOx 	 GPIO端口指针（如GPIOA、GPIOB等）
 * @param pin    	 引脚编号（0-15）
 */
void GPIO_PinSet(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRR = GPIO_Pin;// 置高电平：操作BSRR的低16位（设置位）
}

/**
 * @brief 清除指定GPIO脚的电平状态（置0）
 * @param GPIOx 	 GPIO端口指针（如GPIOA、GPIOB等）
 * @param pin    	 引脚编号（0-15）
 */
void GPIO_PinClr(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BRR = GPIO_Pin;// 置低电平：操作BSRR的高16位（清除位），将引脚编号左移16位
}

// 返回指定pin的输入状态，返回2表示输入不合法
uint8_t GPIO_GetInput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);
}

// 返回指定pin的输出状态，返回2表示输入不合法
uint8_t GPIO_GetOutput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin);
}

