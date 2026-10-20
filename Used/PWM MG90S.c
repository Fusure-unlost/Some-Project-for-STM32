#include "stm32f10x.h"
#include "gpio common module.h"
#include "OLED.h"
#include "Count Sensor.h"
#include "Timer.h"
#include "PWM.h"
#include "delay.h"
#include "PWM MG90S.h"

int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	
	LED_Init(GPIOC,13);
	KEY_Init(GPIOB,10);// 角度先自增，在自减（0-2.5-0ms）
	KEY_Init(GPIOB,0);// 每按一次增加0.1ms
	OLED_Init();
	OLED_Clear();
	
	PWM_MG90S_Init();
	
	// 直接使用变量定义crr的范围与每次改变值，便于后期修改
	uint16_t MAX_CRR = 2501;// 200
	uint16_t MIN_CRR = 500;// 25
	uint16_t MIN_CRR_CHANGE = 10;// 1
	uint16_t ccr = MIN_CRR;

while(1)
	{
	OLED_ShowNum(4,1,TIM_GetCounter(TIM2),4);
		
	if(GPIO_Input(GPIOB,10)==0)// 检测是否按下pb10
		{
		
		while(1)
			{
			Delay_ms(20);// 每100msa增加1ccr，增至25ms需要2.5s
			ccr += MIN_CRR_CHANGE;
			TIM_SetCompare1(TIM2, ccr);// 将（捕获寄存器）的值设置为ccr，1对应1ms
			OLED_ShowNum(3,5,ccr,4);
			OLED_ShowString(3,1,"ccr:");
				if (ccr >= MAX_CRR)// 对ccr复位
				{
					ccr = MIN_CRR;
					TIM_SetCompare1(TIM2, ccr); 
					break;
				}
			}
		}
	if(GPIO_Input(GPIOB,0)==0)
		{
		while(GPIO_Input(GPIOB,0)==0);// 阻塞进程，确保每次点击只执行一次
		ccr += MIN_CRR_CHANGE;
		if (ccr >= MAX_CRR)ccr = MIN_CRR;// 对ccr复位
		TIM_SetCompare1(TIM2, ccr);// 将（捕获寄存器）的值设置为ccr，1对应1ms
		OLED_ShowNum(3,5,ccr,4);
		OLED_ShowString(3,1,"ccr:");
		}
	}
}


