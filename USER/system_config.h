#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H
#include "stm32f4xx.h"
#include "ZY_VisualScope.h"
#include "stdbool.h"
#include "TIM.h"
#include "delay.h"
#include "IIC.h"
#include "hust_math_lib.h"

//用户在这里进行配置资源
#define SYSTEM_SUPPORT_UCOS       1
#define MOTOR_ID_1           0x201//偏航电机ID
#define MOTOR_ID_2           0x202//调距电机ID
#define MOTOR_ID_3           0x203//圆弧电机ID

#define _USE_LED
#define _USE_SWITCH
#define _USE_CAN1
#define _USE_EXT_IO
#define _USE_LOCATE_USART
#define _USE_PC_USART
#define _USE_EXT_USART
#define _USE_BLUETEETH_USART
//#define _USE_MOTOR
#define _USE_ENCODER
#define _USE_PID
#define _USE_Cylinder
#define _USE_SPI
#define _USE_TIM_FOR_VISUAL
#define _USE_LED_WS2815b
#define _USE_EASYSET

#ifdef _USE_LED
#include "Led.h"
#endif

#ifdef _USE_CAN1
#include "Can.h"
#endif

#ifdef _USE_PC_USART
#include "usart.h"
#endif

#ifdef _USE_KEY
#include "Key.h"
#endif

#ifdef _USE_SWITCH
#include "Switch.h"
#endif

#ifdef _USE_EXT_IO
#include "EXT_IO.h"
#endif

#ifdef _USE_MOTOR
#include "motor.h"
#endif

#ifdef _USE_ENCODER
#include "Encoder.h"
#endif

#ifdef _USE_PID
#include "motor_control.h"
#endif

#ifdef _USE_SPI
#include "spi.h"
#endif

#ifdef _USE_LED_WS2815b
#include "LED_WS2815b.h"
#endif

#ifdef _USE_EASYSET
#include "easyset.h"
#endif

void System_Init(void);
#endif
