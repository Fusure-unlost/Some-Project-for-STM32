#include "stm32f10x.h"
#include "gpio common module.h"
#include "OLED.h"
#include "Count Sensor.h"
#include "Timer.h"

int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	
	LED_Init(GPIOC,13);
	KEY_Init(GPIOB,10);// 复位
	OLED_Init();
	OLED_Clear();
	Count_Time_Init();
	uint16_t secound = 0;
	uint16_t minute = 0;	
	
while(1)
	{
		//Count_Time_Get(&secound, &minute);
		
		while(GPIO_Input(GPIOB,10)==0)
		{
			Count_Time_Clear();
			//OLED_Clear();
		}
	}
}


