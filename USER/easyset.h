#include "stm32f4xx.h"

#ifndef _EASYSET_H_
#define _EASYSET_H_

#define true 1
#define false 0	
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

#define LED2_GPIO 		GPIOA
#define LED2_Pin        6
#define LED3_GPIO       GPIOA
#define LED3_Pin        7

#define FRONTLINE_LEFT1_Pin 			1
#define FRONTLINE_LEFT1_GPIOPin 		GPIO_Pin_1
#define FRONTLINE_LEFT1_GPIO 			GPIOD

#define FRONTLINE_CENTER_Pin 			0
#define FRONTLINE_CENTER_GPIOPin 		GPIO_Pin_0
#define FRONTLINE_CENTER_GPIO 			GPIOD

#define FRONTLINE_RIGHT1_Pin 			12
#define FRONTLINE_RIGHT1_GPIOPin 		GPIO_Pin_12
#define FRONTLINE_RIGHT1_GPIO 			GPIOC

int32_t Pin_to_Int(uint16_t Input);
uint16_t Int_to_Pin(int32_t Input);

//TIM_SetCompare1（TIMX，xxx）使用这个调节占空比
void PWM_Set	(GPIO_TypeDef * GPIOx ,
				uint16_t pin,
				uint8_t GPIO_PinSourceX,
				uint8_t GPIO_AF_TIMx,
				TIM_TypeDef * TIMx);
void PinMode(GPIO_TypeDef * GPIOx ,int32_t pin ,int32_t MODE ,int32_t LEVEL);
void Pin_Up(GPIO_TypeDef * GPIOx ,int32_t pin);
void Pin_Down(GPIO_TypeDef * GPIOx ,int32_t pin);
void NVICMode(int ChannelIRQn,int Priority,int SubPriority);
void EasySet(void);

void CHAR_INT_Change(char* ar2,int32_t b);
int32_t INT_CHAR_Change(char* ar);

#endif