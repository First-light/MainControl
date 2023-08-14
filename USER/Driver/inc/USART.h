#ifndef __USART_H
#define __USART_H

/************************* Includes *************************/

#include "stm32f4xx.h"
#include "stdio.h"
#include "stdbool.h"
#include "System_Config.h"

/************************* Defines *************************/

#define USARTn						3
#define BUFFERSIZE                  255

#define MY_USART1_BAUDRATE          115200
#define MY_USART2_BAUDRATE          115200
#define MY_USART3_BAUDRATE          115200//使用普通串口模式
#define MY_USART4_BAUDRATE          115200

/* Definition for USARTx resources */
#define MY_USART1                   USART1  //蓝牙                          
#define MY_USART1_CLK               RCC_APB2Periph_USART1
#define MY_USART1_CLK_INIT          RCC_APB2PeriphClockCmd
#define MY_USART1_IRQn              USART1_IRQn
#define MY_USART1_IRQHandler        USART1_IRQHandler

#define MY_USART1_GPIO_PORT         GPIOA    
#define MY_USART1_TX_PIN            GPIO_Pin_9  
#define MY_USART1_RX_PIN            GPIO_Pin_10  
#define MY_USART1_TX_SOURCE         GPIO_PinSource9
#define MY_USART1_RX_SOURCE         GPIO_PinSource10
#define MY_USART1_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define MY_USART1_AF                GPIO_AF_USART1

/* Definition for DMAx resources ********************************************/
#define MY_USART1_DMA               DMA1
#define MY_USART1_DMAx_CLK          RCC_AHB1Periph_DMA1
#define MY_USART1_DMAx_INIT         RCC_AHB1PeriphClockCmd
	 
#define MY_USART1_TX_DMA_CHANNEL    DMA_Channel_4   //DMA1,数据流4,通道4
#define MY_USART1_TX_DMA_STREAM     DMA1_Stream4
#define MY_USART1_TX_DMA_FLAG_FEIF  DMA_FLAG_FEIF4
#define MY_USART1_TX_DMA_FLAG_DMEIF DMA_FLAG_DMEIF4
#define MY_USART1_TX_DMA_FLAG_TEIF  DMA_FLAG_TEIF4
#define MY_USART1_TX_DMA_FLAG_HTIF  DMA_FLAG_HTIF4
#define MY_USART1_TX_DMA_FLAG_TCIF  DMA_FLAG_TCIF4

#define MY_USART1_TX_DMA_FLAG       DMA_FLAG_FEIF4 | DMA_FLAG_DMEIF4| \
									DMA_FLAG_TEIF4 | DMA_FLAG_HTIF4|  \
									DMA_FLAG_TCIF4
						
#define MY_USART1_RX_DMA_CHANNEL    DMA_Channel_4
#define MY_USART1_RX_DMA_STREAM     DMA1_Stream2    //DMA1,数据流2,通道4
#define MY_USART1_RX_DMA_FLAG_FEIF  DMA_FLAG_FEIF2
#define MY_USART1_RX_DMA_FLAG_DMEIF DMA_FLAG_DMEIF2
#define MY_USART1_RX_DMA_FLAG_TEIF  DMA_FLAG_TEIF2
#define MY_USART1_RX_DMA_FLAG_HTIF  DMA_FLAG_HTIF2
#define MY_USART1_RX_DMA_FLAG_TCIF  DMA_FLAG_TCIF2

#define MY_USART1_RX_DMA_FLAG       DMA_FLAG_FEIF2 | DMA_FLAG_DMEIF2 | \
                                    DMA_FLAG_TEIF2 | DMA_FLAG_HTIF2 |  \
                                    DMA_FLAG_TCIF2												
																						
/* Definition for USARTx resources */
#define MY_USART2                   USART2                            
#define MY_USART2_CLK               RCC_APB1Periph_USART2
#define MY_USART2_CLK_INIT          RCC_APB1PeriphClockCmd
#define MY_USART2_IRQn              USART2_IRQn
#define MY_USART2_IRQHandler        USART2_IRQHandler

#define MY_USART2_GPIO_PORT         GPIOA      
#define MY_USART2_TX_PIN            GPIO_Pin_2                
#define MY_USART2_RX_PIN            GPIO_Pin_3                 
#define MY_USART2_TX_SOURCE         GPIO_PinSource2
#define MY_USART2_RX_SOURCE         GPIO_PinSource3
#define MY_USART2_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define MY_USART2_AF                GPIO_AF_USART2

/* Definition for DMAx resources ********************************************/
#define MY_USART2_DMA               DMA1
#define MY_USART2_DMAx_CLK          RCC_AHB1Periph_DMA1
#define MY_USART2_DMAx_INIT         RCC_AHB1PeriphClockCmd
	 
#define MY_USART2_TX_DMA_CHANNEL    DMA_Channel_4   //DMA1,数据流6,通道4
#define MY_USART2_TX_DMA_STREAM     DMA1_Stream6
#define MY_USART2_TX_DMA_FLAG_FEIF  DMA_FLAG_FEIF6
#define MY_USART2_TX_DMA_FLAG_DMEIF DMA_FLAG_DMEIF6
#define MY_USART2_TX_DMA_FLAG_TEIF  DMA_FLAG_TEIF6
#define MY_USART2_TX_DMA_FLAG_HTIF  DMA_FLAG_HTIF6
#define MY_USART2_TX_DMA_FLAG_TCIF  DMA_FLAG_TCIF6

#define MY_USART2_TX_DMA_FLAG       DMA_FLAG_FEIF6 | DMA_FLAG_DMEIF6| \
									DMA_FLAG_TEIF6 | DMA_FLAG_HTIF6| \
									DMA_FLAG_TCIF6
						
#define MY_USART2_RX_DMA_CHANNEL    DMA_Channel_4
#define MY_USART2_RX_DMA_STREAM     DMA1_Stream5    //DMA1,数据流5,通道4
#define MY_USART2_RX_DMA_FLAG_FEIF  DMA_FLAG_FEIF5
#define MY_USART2_RX_DMA_FLAG_DMEIF DMA_FLAG_DMEIF5
#define MY_USART2_RX_DMA_FLAG_TEIF  DMA_FLAG_TEIF5
#define MY_USART2_RX_DMA_FLAG_HTIF  DMA_FLAG_HTIF5
#define MY_USART2_RX_DMA_FLAG_TCIF  DMA_FLAG_TCIF5

#define MY_USART2_RX_DMA_FLAG       DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | \
                                    DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5 | \
                                    DMA_FLAG_TCIF5

/* Definition for USARTx resources ******************************************/

#define MY_USART3                   UART4                            
#define MY_USART3_CLK               RCC_APB1Periph_UART4
#define MY_USART3_CLK_INIT          RCC_APB1PeriphClockCmd
#define MY_USART3_IRQn              UART4_IRQn
#define MY_USART3_IRQHandler        UART4_IRQHandler

#define MY_USART3_GPIO_PORT         GPIOA      
#define MY_USART3_TX_PIN            GPIO_Pin_0                
#define MY_USART3_RX_PIN            GPIO_Pin_1                 
#define MY_USART3_TX_SOURCE         GPIO_PinSource0
#define MY_USART3_RX_SOURCE         GPIO_PinSource1
#define MY_USART3_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define MY_USART3_AF                GPIO_AF_UART4

/* Definition for USARTx resources ******************************************/
#define MY_USART4                   USART6                            
#define MY_USART4_CLK               RCC_APB2Periph_USART6
#define MY_USART4_CLK_INIT          RCC_APB2PeriphClockCmd
#define MY_USART4_IRQn              USART6_IRQn
#define MY_USART4_IRQHandler        USART6_IRQHandler

#define MY_USART4_GPIO_PORT         GPIOC      
#define MY_USART4_TX_PIN            GPIO_Pin_6                
#define MY_USART4_RX_PIN            GPIO_Pin_7                 
#define MY_USART4_TX_SOURCE         GPIO_PinSource6
#define MY_USART4_RX_SOURCE         GPIO_PinSource7
#define MY_USART4_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define MY_USART4_AF                GPIO_AF_USART6

/************************* Exported types *************************/

typedef enum
{
	MYUSART1,
	MYUSART2,
//	MYUSART3,
	MYUSART4,
}MyUSARTTypedef;

/************************* Exported constants *************************/

extern u8 ReceiveBuffer1[BUFFERSIZE];   //DMA中断接收使用
extern u8 ReceiveBuffer2[BUFFERSIZE];
//extern u8 ReceiveBuffer3[BUFFERSIZE];
extern u8 ReceiveBuffer4[BUFFERSIZE];
extern USART_TypeDef * const USART_SOURCE[USARTn];


/************************* Exported Functions *************************/

void USART_Hard_Init(MyUSARTTypedef);
void COM_Write(uint8_t*,uint8_t,MyUSARTTypedef);

#endif 

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/






