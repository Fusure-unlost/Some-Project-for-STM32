#include "stm32f10x.h"
#include "gpio common module.h"
#include "OLED.h"
#include "Count Sensor.h"
#include "Timer.h"
#include "PWM.h"
#include "delay.h"
#include "PWM MG90S.h"
#include "ADC ONE.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	
	/*LED_Init(GPIOC,13);
	KEY_Init(GPIOB,10);// 角度先自增，在自减（0-2.5-0ms）
	KEY_Init(GPIOB,0);// 每按一次增加0.1ms*/
	OLED_Init();
	OLED_Clear();
	
	ADC_ONE_Init();
	
	OLED_ShowString(1,1,"AD:");
	OLED_ShowString(2,1,"V:0.00v");
	
	uint16_t AD_Value;
	float Voltage;// 用于存储电压
	
while(1)
{
	AD_Value = ADC_ONE_GetValue();
	Voltage = (float)AD_Value / 4095 * 3.3;// 计算AD_Value对应的电压值

	OLED_ShowNum(1,4,AD_Value,4);
	OLED_ShowNum(2,3,Voltage,1);
	OLED_ShowNum(2,5,(uint16_t)(Voltage*100) % 100,2);// 计算电压的小数部分，无法直接显示小数
	
}
}


