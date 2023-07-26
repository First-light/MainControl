#ifndef  _SWITCH_H
#define  _SWITCH_H

#include "stm32f4xx.h"
#include "includes.h"
#include "atomIO.h"
typedef  enum
{
	SW1 = 0,
	SW2 = 1	
}SW_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define SWn    										2
#define SW1_PIN   								GPIO_Pin_0
#define SW1_GPIO_PORT 						GPIOC
#define SW1_GPIO_CLK  						RCC_AHB1Periph_GPIOC

#define SW2_PIN   								GPIO_Pin_1
#define SW2_GPIO_PORT 						GPIOC
#define SW2_GPIO_CLK  						RCC_AHB1Periph_GPIOC


/* Exported functions --------------------------------------------------------*/
void SW_InitAll(void);
void SW_Init(SW_TypeDef  SW);
bool IsSWTouched(SW_TypeDef SW_N);

#define SW1_IN  PBin(0)
#define SW2_IN  PBin(1)

#endif 
