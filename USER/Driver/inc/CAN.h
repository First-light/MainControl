#ifndef CAN_H_
#define CAN_H_

/************************* Includes *************************/

#include "stm32f4xx.h"
#include "RobotCAN_IDconf.h"

/************************* Defines *************************/

#define CANn                        2

#define CAN1_CLK                    RCC_APB1Periph_CAN1
#define CAN1_RX_PIN                 GPIO_Pin_11
#define CAN1_TX_PIN                 GPIO_Pin_12
#define CAN1_GPIO_PORT              GPIOA
#define CAN1_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define CAN1_AF_PORT                GPIO_AF_CAN1
#define CAN1_RX_SOURCE              GPIO_PinSource11
#define CAN1_TX_SOURCE              GPIO_PinSource12
#define CAN1_RX_IRQn				CAN1_RX0_IRQn
#define CAN1_RX_IRQHandler			CAN1_RX0_IRQHandler

#define CAN1_FILTER_NUMBER			0               //CAN2 用 14，CAN1 用的是0
#define CAN1_Filter_FIFO            0
#define CAN1_IT_FMP                 CAN_IT_FMP0
#define CAN1_Protocol               0               //0代表采用团队协议，1代表不采用团队协议

#define CAN2_CLK                    RCC_APB1Periph_CAN2 | RCC_APB1Periph_CAN1
#define CAN2_RX_PIN                 GPIO_Pin_12
#define CAN2_TX_PIN                 GPIO_Pin_13
#define CAN2_GPIO_PORT              GPIOB
#define CAN2_GPIO_CLK               RCC_AHB1Periph_GPIOB 
#define CAN2_AF_PORT                GPIO_AF_CAN2
#define CAN2_RX_SOURCE              GPIO_PinSource12
#define CAN2_TX_SOURCE              GPIO_PinSource13
#define CAN2_RX_IRQn				CAN2_RX1_IRQn
#define CAN2_RX_IRQHandler			CAN2_RX1_IRQHandler

#define CAN2_FILTER_NUMBER			14              //CAN2 用 14，CAN1 用的是0
#define CAN2_Filter_FIFO            1
#define CAN2_IT_FMP                 CAN_IT_FMP1
#define CAN2_Protocol               0               //0代表采用团队协议，1代表不采用团队协议

/************************* Exported types *************************/

typedef enum {
  MYCAN1 = 0,
	MYCAN2 = 1,
}MyCANTypedef;

/************************* Exported constants *************************/

extern CAN_TypeDef * const CAN_SOURCE[CANn];

/************************* Exported Functions *************************/

void CAN_Hard_Init(MyCANTypedef);

#endif

