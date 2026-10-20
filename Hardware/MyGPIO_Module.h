#ifndef __MYGPIO_MODULE_H
#define __MYGPIO_MODULE_H

void LED_Init(GPIO_TypeDef* GPIOx, uint16_t pin);
void KEY_Init(GPIO_TypeDef* GPIOx, uint16_t pin);
void G_Init(GPIO_TypeDef* GPIOx, uint16_t pin, GPIOMode_TypeDef G_Mode);
void GPIO_PinSwitch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction State);
void GPIO_PinSet(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_PinClr(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t GPIO_GetInput(GPIO_TypeDef* GPIOx, uint16_t pin);
uint8_t GPIO_GetOutput(GPIO_TypeDef* GPIOx, uint16_t pin);



#endif
