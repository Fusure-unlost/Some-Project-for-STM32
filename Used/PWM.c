#include "stm32f10x.h"
#include "gpio common module.h"

/*
对于PWM：

RCC时钟

时基单元
-> PSC -> CNT <-> ARR
预分频器  计数器  自动重装器

输出比较单元
CNT <-> CCR -> PWM模式 -REF-> 极性选择、输出使能
计数器  捕获/比较器

GPIO
*/
void PWM_Init(void)
{
	// rcc时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	/*
	// 该部分为将TIM2的pa0输出重映射至pa15（固定引脚）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);// 开启AFIO（引脚重映射功能）时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);// 将pa0的输出重映射到pa15（固定引脚，还要配置pa15的GPIO）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);// 由于pa15为调试端口，所以需要先解除其调试功能
	// 注：接触调试端口具有一定风险，固该部分不使用，仅作为参考
	*/
	
	// 选择内部时钟
	TIM_InternalClockConfig(TIM2);
	// 配置tim2
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;  
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	// 清除初始中断标志位
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	// 使能
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	// 配置nvic
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	// 配置输出比较（oc）通道
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCStructInit(&TIM_OCInitStruct);// 为oc赋初始值，由于该结构体成员过多，且含有大量高级计数器的的成员，
										// 此处无用，但为防bug，先全部这顶初始值，在具体修改所需
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;// pwm模式1，计数器小于设定值时输出有效电平
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;// 配置有效电平为高电平
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;// 输出使能
	TIM_OCInitStruct.TIM_Pulse = 0;// ccr（捕获寄存器）的值
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	/*
	PWM相关计算
	频率：  Freq = CK_PSC / (PSC + 1)/(ARR + 1)
	占空比：Duty = CCR/(ARR + 1)
	分辨率：Reso = 1/(ARR + 1)
	*/
	
	
	// tim2计数器使能
	TIM_Cmd(TIM2,ENABLE);
	// 设置对应的GPIO输出，引脚固定
	G_Init(GPIOA,0,GPIO_Mode_AF_PP);
}

