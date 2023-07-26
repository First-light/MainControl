#ifndef GLOBAL_TIMER_H
#define GLOBAL_TIMER_H
#define GLOBAL_TIMER				TIM6
#define GLOBAL_TIMER_CLK		RCC_APB1Periph_TIM6

#define DT_US_COUNT ((uint16_t)(GLOBAL_TIMER->CNT)) //65msÄÚÓĞĞ§  
void globalTimInit(void);
#endif