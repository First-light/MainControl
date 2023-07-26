// #ifndef __MOTOR_H
// #define __MOTOR_H
// #include "stm32f4xx.h"
// #include "stdbool.h"
// #include "atomIO.h"
// #define PWM_MOTOR_FREQ 				40000// 通过此设置 PWM频率————> 40K
// #define MAX_MOTOR_PWM 				2100// 通过此设置 PWM最大值————>2100
// #define MAX_MOTOR_PWM_LIMIT 	2050//限制最大占空比

// /**************************电机驱动端口选择设定**************************/
// #define MOTOR_CONTROL_RESET_PORT					GPIOB
// #define MOTOR_CONTROL_RESET_PORT_CLK			RCC_AHB1Periph_GPIOB
// #define MOTOR_CONTROL_RESET_PIN					  GPIO_Pin_14

// #define MOTOR_CONTROL_EN_PORT							GPIOB
// #define MOTOR_CONTROL_EN_PORT_CLK					RCC_AHB1Periph_GPIOB
// #define MOTOR_CONTROL_EN_PIN							GPIO_Pin_13

// /**/
// #define	MOTOR_PWM_OUT_PORT					  GPIOC              
// #define MOTOR_PWM_OUT_PORT_CLK			  RCC_AHB1Periph_GPIOC
// #define MOTOR_PWM_OUT_AF_TIM          GPIO_AF_TIM8

// #define MOTOR_PWM_HA_PIN							GPIO_Pin_9
// #define MOTOR_PWM_HA_Pinsource        GPIO_PinSource9

// #define MOTOR_PWM_NLA_PIN							GPIO_Pin_8
// #define MOTOR_PWM_NLA_Pinsource       GPIO_PinSource8

// #define MOTOR_PWM_NHB_PIN							GPIO_Pin_7
// #define MOTOR_PWM_NHB_Pinsource       GPIO_PinSource7

// #define MOTOR_PWM_LB_PIN							GPIO_Pin_6
// #define MOTOR_PWM_LB_Pinsource        GPIO_PinSource6

// /**************************PWM产生定时器选择**************************/
// #define PWM_TIMER1							TIM8
// #define PWM_TIMER1_CLK					RCC_APB2Periph_TIM8
// #define PWM_TIMER1_CLK_INIT			RCC_APB2PeriphClockCmd
// /*******************************************************************/

// #define MOTOR_COM_SDI_PORT        				GPIOB
// #define MOTOR_COM_SDI_PORT_CLK       			RCC_AHB1Periph_GPIOB
// #define MOTOR_COM_SDI_PIN        					GPIO_Pin_15

// #define MOTOR_COM_NSTR_PORT        				GPIOB
// #define MOTOR_COM_NSTR_PORT_CLK       		RCC_AHB1Periph_GPIOB
// #define MOTOR_COM_NSTR_PIN        				GPIO_Pin_14

// #define MOTOR_COM_SDO_PORT        				GPIOB
// #define MOTOR_COM_SDO_PORT_CLK       			RCC_AHB1Periph_GPIOB
// #define MOTOR_COM_SDO_PIN        					GPIO_Pin_13

// #define MOTOR_COM_SCK_PORT        				GPIOB
// #define MOTOR_COM_SCK_PORT_CLK       			RCC_AHB1Periph_GPIOB
// #define MOTOR_COM_SCK_PIN        					GPIO_Pin_12

// #define MOTOR_COM_SDI_OUT                 PBout(15)
// #define MOTOR_COM_NSTR_OUT                PBout(14)
// #define MOTOR_COM_SDO_IN                  PBin(13)
// #define MOTOR_COM_SCK_OUT                 PBout(12)

// typedef enum
// {
// 	DIODE_RECTIFY = 0,
// 	SYNC_RECTIFY = 1,
// 	FAST_DIODE_RECTIFY = 2,
// 	FAST_SYNC_RECTIFY = 3
// }DRIVER_MODE_TypeDef;


// void TIM_MOTOR_PWM_Init(void);
// void TIM_MOTOR_ADC_Init(void);
// void CURRENT_ADC_EXTIX_Init(void);
// void Motor_Init(void);
// void MotorDisable(void);
// void MotorEnable(void);
// void MotorBrk(void);
// void Motor_PWM_Update(s32 PWM_Value);

// bool A3922Config();

// extern DRIVER_MODE_TypeDef DriverMode;
// extern u8 MOTOR_INVERSE_DIR;

// bool A3922RegRW(uint8_t RegID,uint16_t RegVal,uint16_t* ReadValue,bool IsWrite);

// #endif
