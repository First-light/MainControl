#ifndef _EXT_IO_H
#define _EXT_IO_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stdbool.h"
#include "atomIO.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
//	EXT_IO_POWER_ON = 0,
//	EXT_IO1 = 1,
//	EXT_IO2 = 2,
//	EXT_IO3 = 3,
	EXT_IO0 = 0,
	EXT_IO1 = 1,
	EXT_IO2 = 2,
	EXT_IO3 = 3,
	EXT_IO4 = 4,
	EXT_IO5 = 5,
	EXT_IO6 = 6,
	EXT_IO7 = 7,
}EXT_IO_TypeDef;

/* Exported constants --------------------------------------------------------*/

//#define EXT_IOn														4

//#define EXT_POWER_ON_PIN									GPIO_Pin_2
//#define EXT_POWER_ON_GPIO_PORT						GPIOB
//#define EXT_POWER_ON_GPIO_CLK							RCC_AHB1Periph_GPIOB
//#define EXT_POWER_ON_GPIO_MODE						GPIO_Mode_OUT

//#define EXT_IO1_PIN												GPIO_Pin_10
//#define EXT_IO1_GPIO_PORT									GPIOB
//#define EXT_IO1_GPIO_CLK									RCC_AHB1Periph_GPIOB 
//#define EXT_IO1_GPIO_MODE									GPIO_Mode_OUT

//#define EXT_IO2_PIN												GPIO_Pin_11
//#define EXT_IO2_GPIO_PORT									GPIOB
//#define EXT_IO2_GPIO_CLK									RCC_AHB1Periph_GPIOB
//#define EXT_IO2_GPIO_MODE									GPIO_Mode_OUT

//#define EXT_IO3_PIN												GPIO_Pin_12
//#define EXT_IO3_GPIO_PORT									GPIOB
//#define EXT_IO3_GPIO_CLK									RCC_AHB1Periph_GPIOB
//#define EXT_IO3_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IOn														8

#define EXT_IO0_PIN												GPIO_Pin_0
#define EXT_IO0_GPIO_PORT									GPIOB
#define EXT_IO0_GPIO_CLK									RCC_AHB1Periph_GPIOB
#define EXT_IO0_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO1_PIN												GPIO_Pin_1
#define EXT_IO1_GPIO_PORT									GPIOB
#define EXT_IO1_GPIO_CLK									RCC_AHB1Periph_GPIOB 
#define EXT_IO1_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO2_PIN												GPIO_Pin_2
#define EXT_IO2_GPIO_PORT									GPIOB
#define EXT_IO2_GPIO_CLK									RCC_AHB1Periph_GPIOB
#define EXT_IO2_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO3_PIN												GPIO_Pin_3
#define EXT_IO3_GPIO_PORT									GPIOB
#define EXT_IO3_GPIO_CLK									RCC_AHB1Periph_GPIOB
#define EXT_IO3_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO4_PIN												GPIO_Pin_4
#define EXT_IO4_GPIO_PORT									GPIOB
#define EXT_IO4_GPIO_CLK									RCC_AHB1Periph_GPIOB
#define EXT_IO4_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO5_PIN												GPIO_Pin_5
#define EXT_IO5_GPIO_PORT									GPIOB
#define EXT_IO5_GPIO_CLK									RCC_AHB1Periph_GPIOB
#define EXT_IO5_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO6_PIN												GPIO_Pin_2
#define EXT_IO6_GPIO_PORT									GPIOD
#define EXT_IO6_GPIO_CLK									RCC_AHB1Periph_GPIOD
#define EXT_IO6_GPIO_MODE									GPIO_Mode_OUT

#define EXT_IO7_PIN												GPIO_Pin_5
#define EXT_IO7_GPIO_PORT									GPIOC
#define EXT_IO7_GPIO_CLK									RCC_AHB1Periph_GPIOC
#define EXT_IO7_GPIO_MODE									GPIO_Mode_OUT


/* Exported functions --------------------------------------------------------*/
void ExtIo_Init(EXT_IO_TypeDef EXT_IO);

void ExtIo_InitAll(void);

#define EXT_IO_PowerOn  PBout(2)

#define Ext_IO1_In      PBin(10)

#define Ext_IO1_Out     PBout(10)

#define Ext_IO2_In      PBin(11)

#define Ext_IO2_Out     PBout(11)   

#define Ext_IO3_In      PBin(12)

#define Ext_IO3_Out     PBout(12)   

#endif