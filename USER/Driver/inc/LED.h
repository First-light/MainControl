// Author:
// Date:  
// File brief: LED计数顺序 1-2-3 ，分别对应红、绿、蓝,外部调用时 LED_Toggle(RED_LED);

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	LED1 ,
	LED2 ,
	LED3  
	
}LED_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define LEDn												    		3
//                                                         
#define LED1_PIN												    GPIO_Pin_15                //红色
#define LED1_GPIO_PORT									GPIOA
#define LED1_GPIO_CLK										RCC_AHB1Periph_GPIOA

#define LED2_PIN											    	GPIO_Pin_15                  //绿色
#define LED2_GPIO_PORT									GPIOB
#define LED2_GPIO_CLK										RCC_AHB1Periph_GPIOB

#define LED3_PIN												    GPIO_Pin_14                  //蓝色
#define LED3_GPIO_PORT									GPIOB
#define LED3_GPIO_CLK										RCC_AHB1Periph_GPIOB

#define RED_LED      LED1 
#define GREEN_LED    LED2 
#define BLUE_LED     LED3 


/* Exported functions --------------------------------------------------------*/
void LED_Init(LED_TypeDef LED);
void LED_On(LED_TypeDef LED);
void LED_Off(LED_TypeDef LED);
void LED_Toggle(LED_TypeDef LED);
void LED_InitAll(void);


#endif 

/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/

