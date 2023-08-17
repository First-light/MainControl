#include "stm32f4xx.h"

#ifndef _EASYSET_H_
#define _EASYSET_H_

#define true 1
#define false 0	
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

//tim1和tim8是高级定时器
//tim6和tim7是基本定时器

#define LED1_GPIO 		GPIOA
#define LED1_Pin        15
#define LED2_GPIO 		GPIOB
#define LED2_Pin        14
#define LED3_GPIO       GPIOB
#define LED3_Pin        15

#define ROB_GPIOx 	GPIOB
#define ROB_PINx    4    //enc_3

int32_t Pin_to_Int(uint16_t Input);
uint16_t Int_to_Pin(int32_t Input);

//TIM_SetCompare1（TIMX，xxx）使用这个调节占空比


void Pin_Up(GPIO_TypeDef * GPIOx ,int32_t pin);
void Pin_Down(GPIO_TypeDef * GPIOx ,int32_t pin);

void EasySet(void);

void UART_Open(USART_TypeDef * UARTx,uint32_t Baud);
void RXTX_Set(GPIO_TypeDef * GPIOx,uint16_t pinRX,uint16_t pinTX ,uint8_t PS_RX,uint8_t PS_TX,uint8_t AF);
void NVICMode(int ChannelIRQn,int Priority,int SubPriority);
void PinMode(GPIO_TypeDef * GPIOx ,int32_t pin ,int32_t MODE ,int32_t LEVEL);
void PWM_Set	(GPIO_TypeDef * GPIOx ,
				uint16_t pin,
				uint8_t GPIO_PinSourceX,
				uint8_t GPIO_AF_TIMx,
				TIM_TypeDef * TIMx);

void CHAR_INT_Change(char* ar2,int32_t b);
int32_t INT_CHAR_Change(char* ar);

#endif