#include "stm32f10x.h"
#include "gpio common module.h"
#include "gpio common module.h"
#include "OLED.h"
#include "Count Sensor.h"

int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	
	LED_Init(GPIOC,13);
	KEY_Init(GPIOB,10);
	OLED_Init();
	OLED_Clear();
	CountSensor_Init();
	
while(1)
	{
		OLED_ShowNum(1,1,CountSensor_Get(),4);
		while(GPIO_Input(GPIOB,10)==0)
		{
			CountSensor_Clear();
			OLED_Clear();
		}
	}
}

