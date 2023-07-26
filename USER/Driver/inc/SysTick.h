
#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f4xx.h"

/**	Definition for the System Clock	*****************************************/
#define Open_System_Timer()									SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;\
																						Init_System_Timer();
#define Close_System_Timer()								SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
#define Init_System_Timer()									System_Time.uSec = 0;\
																						System_Time.mSec = 0;\
																						System_Time.Sec = 0;
																						

/** 
  * @brief  时钟结构体 
  */
typedef struct
{
	uint16_t uSec;
	uint16_t mSec;
	uint16_t Sec;
	
}System_Clock_TypeDef;																					

void SysTick_Init(void);

#endif
