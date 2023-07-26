#include "stm32f4xx.h"
#include "globalTime.h"
void globalTimInit()   //systick 不能满足要求
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* Remote Control Timer clock enable */
	RCC_APB1PeriphClockCmd(GLOBAL_TIMER_CLK,ENABLE);
	//if APBx presc =1 x1 else x2
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;//1M 
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(GLOBAL_TIMER, &TIM_TimeBaseStructure);
	TIM_Cmd(GLOBAL_TIMER, ENABLE);
}
