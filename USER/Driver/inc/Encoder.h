/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ENCODERA_H
#define _ENCODERA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* Exported types ------------------------------------------------------------*/
typedef struct _EncoderTypeDef
{
	uint16_t encoder;
	uint16_t old_encoder;
	int32_t distance;
} EncoderTypeDef;
/* Exported constants --------------------------------------------------------*/

                         
#define	ENC_TIMER 							 					TIM2
#define ENC_TIMER_IRQn			        			TIM2_IRQn
#define ENC_TIMER_IRQnHandler			  		  TIM2_IRQHandler                  //中断
#define ENC_TIMER_CLK						 				  RCC_APB1Periph_TIM2           
#define ENC_GPIO_A_PORT						 				GPIOA      
#define ENC_GPIO_B_PORT						 				GPIOA    
#define ENC_GPIO_A_CLK						 				RCC_AHB1Periph_GPIOA
#define ENC_GPIO_B_CLK                    RCC_AHB1Periph_GPIOA
#define ENC_GPIO_PIN_A					 					GPIO_Pin_0                       //CH 1    
#define ENC_GPIO_PIN_B					 					GPIO_Pin_1 		                   //CH 2
#define ENC_GPIO_AF_TIM          					GPIO_AF_TIM2
#define ENC_GPIO_Pinsource_A     					GPIO_PinSource0          
#define ENC_GPIO_Pinsource_B     					GPIO_PinSource1
#define ENC_RCC_APBxPeriphClockCmd(ENC_TIMER_CLK,ENABLE)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE) 

#define ENCODER_TIM_PERIOD               (0xffff)      //兼容16位,不可修改
/* Exported functions --------------------------------------------------------*/
void  ENC_Init(void);
float Enc_GetPosition(void);
float Enc_GetSpeed(void);
float Enc_GetAcceleration(void);
void  Encoder_Read();
void ENC_Light_Switch_Init(void);

/* Exported 全局变量 --------------------------------------------------------*/


#endif 

/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/
