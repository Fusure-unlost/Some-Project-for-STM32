#include "stm32f10x.h"
#include "gpio common module.h"
#include "OLED.h"
#include "Delay.h"
/*#include "Count Sensor.h"
#include "Timer.h"
#include "PWM.h"
#include "PWM MG90S.h"
#include "ADC ONE.h"
#include "DMA NUM.h"
#include "DMA ADC.h"*/
#include "Serial.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	
	LED_Init(GPIOC,13);
	KEY_Init(GPIOB,10);
	KEY_Init(GPIOB,0);
	KEY_Init(GPIOA,6);
	OLED_Init();
	OLED_Clear();
	
	Serial_Init();
	
	uint8_t byte = 0x00;
	char array[6] = {'F','u','s','u','r','e'};
	
while(1)
{
	if(GPIO_Input(GPIOB,10) == 0)
	{
		OLED_ShowHexNum(1,1,byte,4);
		Serial_SendByte(byte);
		byte++;
		Delay_ms(10);
	}
	
	if(GPIO_Input(GPIOB,0) == 0)
	{
		byte = 0x00;
	}
	
	if(GPIO_Input(GPIOA,6) == 0)
	{
		while((GPIO_Input(GPIOA,6) == 0));
		Serial_SendNumber(654321,6);
	}
	
	if(Serial_GetRxFlag() == 1)
	{
		uint8_t RxData = Serial_GetRxData();
		OLED_ShowHexNum(1,2,RxData,4);
		Serial_SendByte(RxData);
	}
	
}
}


