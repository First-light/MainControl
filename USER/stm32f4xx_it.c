/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h" 
#include "VESC_CAN.h"
#include "system_config.h"
//#include "com_prop.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)	  
  {
	 Pin_Up(LED1_GPIO,LED1_Pin); 
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/



/**
  * @brief  This function handles PC_USART interrupt request.
  * @param  None
  * @retval None
  */
	

//#include "Comlib.h"



void (MY_USART1_IRQHandler)(void)
{
	uint16_t temp = 0;

	if(USART_GetITStatus(MY_USART1, USART_IT_RXNE) == SET)
  {
    temp = USART_ReceiveData(MY_USART1);
	Get_Frame_COM(temp, MYUSART1);
  }	
}

void (MY_USART2_IRQHandler)(void)//pc与上层板子通信口
{
	uint16_t temp = 0;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
  {
    temp = USART_ReceiveData(USART2);
		Get_Frame_COM(temp, MYUSART2);
  }	
}

/*void (MY_USART3_IRQHandler)(void)
{
	uint16_t temp = 0;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET)
  {
    temp = USART_ReceiveData(UART4);
		Get_Frame_COM(temp, MYUSART3);
  }	
}
*/
int t;

void (MY_USART4_IRQHandler)(void)//上层控制板和底盘之间的通信
{
	uint16_t temp = 0;
	
	if(USART_GetITStatus(MY_USART4, USART_IT_RXNE) == SET)
  {
    temp = USART_ReceiveData(MY_USART4);
	  t = temp;
		Get_Frame_COM(temp, MYUSART4);
  }	
}

/**
  * @brief  This function handles CAN interrupt request.
  * @param  None
  * @retval None
  */
#include "RobotCAN_Basic.h"
#include "elmo.h"
#include "VESC_CAN.h"
/**
  * @}
  */ 

/**
  * @}
  */ 


float Get_RM2006_Distance(MotorTypeDef Motor)
{
		int Distance = Motor.PosNow - Motor.PosPre;
		if(abs(Distance) > 4000)
			Distance = Distance - Distance/abs(Distance) * 8192;
		return ((float)Distance*360.0f/36.0f/8192.0f);		
}


float Get_RM3508_Distance(MotorTypeDef Motor)
{
		int Distance = Motor.PosNow - Motor.PosPre;
		if(abs(Distance) > 4000)
			Distance = Distance - Distance/abs(Distance) * 8192;
		return ((float)Distance*360.0f/19.0f/8192.0f);		
}

void CAN1_RX_IRQHandler(void)
{
	CanRxMsg RxMessage;
	Frame Frame_rcv;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
  if (RxMessage.IDE == CAN_ID_EXT) {
    Frame_rcv.id.all = RxMessage.ExtId;
    Frame_rcv.isRemote = RxMessage.RTR == CAN_RTR_DATA ? 0 : 1;
    Frame_rcv.length = RxMessage.DLC;
    memset(Frame_rcv.data.chars, 0, 8);  //先清空再copy
    memcpy(Frame_rcv.data.chars, (char*)RxMessage.Data, Frame_rcv.length);
		ProcessVESCFrame(&Frame_rcv);
  }
}

void CAN2_RX_IRQHandler(void) 
{
  CanRxMsg RxMessage;
	CAN_Receive(CAN2, CAN_FIFO1, &RxMessage);

	if(RxMessage.StdId == Motor_1_ID)
	{ 
		Motor1.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor1.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591; 19.0f用于3508，36.0f用于2006
		if(Motor1.PosPre == 0 && Motor1.PosNow == 0 )
			Motor1.PosPre = Motor1.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor1.PosPre = Motor1.PosNow;
			Motor1.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor1.PositionMeasure += Get_RM3508_Distance(Motor1);
	}
	
	else if(RxMessage.StdId == Motor_2_ID)
	{
		Motor2.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor2.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor2.PosPre == 0 && Motor2.PosNow == 0 )
			Motor2.PosPre = Motor2.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor2.PosPre = Motor2.PosNow;
			Motor2.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor2.PositionMeasure += Get_RM3508_Distance(Motor2);
	}
	
	else if(RxMessage.StdId == Motor_3_ID)
	{
		Motor3.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor3.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor3.PosPre == 0 && Motor3.PosNow == 0 )
			Motor3.PosPre = Motor3.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor3.PosPre = Motor3.PosNow;
			Motor3.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor3.PositionMeasure += Get_RM2006_Distance(Motor3);
	}
	else if(RxMessage.StdId == Motor_4_ID)
	{
		Motor4.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor4.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor4.PosPre == 0 && Motor4.PosNow == 0 )
			Motor4.PosPre = Motor4.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor4.PosPre = Motor4.PosNow;
			Motor4.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor4.PositionMeasure += Get_RM2006_Distance(Motor4);
	}
	else if(RxMessage.StdId == Motor_5_ID)
	{
		Motor5.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor5.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor5.PosPre == 0 && Motor5.PosNow == 0 )
			Motor5.PosPre = Motor5.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor5.PosPre = Motor5.PosNow;
			Motor5.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor5.PositionMeasure += Get_RM2006_Distance(Motor5);
	}
	else if(RxMessage.StdId == Motor_6_ID)
	{
		Motor6.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor6.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor6.PosPre == 0 && Motor6.PosNow == 0 )
			Motor6.PosPre = Motor6.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor6.PosPre = Motor6.PosNow;
			Motor6.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor6.PositionMeasure += Get_RM2006_Distance(Motor6);
	}
	else if(RxMessage.StdId == Motor_7_ID)
	{
		Motor7.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor7.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor7.PosPre == 0 && Motor7.PosNow == 0 )
			Motor7.PosPre = Motor7.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor7.PosPre = Motor7.PosNow;
			Motor7.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor7.PositionMeasure += Get_RM2006_Distance(Motor7);
	}
	else if(RxMessage.StdId == Motor_8_ID)
	{
		Motor8.CurrentMeasure=(float)(short)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
		Motor8.SpeedMeasure =((float)(short)(RxMessage.Data[2]<<8 | RxMessage.Data[3]))/19.0f;//*187.0/3591;   
		if(Motor8.PosPre == 0 && Motor8.PosNow == 0 )
			Motor8.PosPre = Motor8.PosNow = (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		else
		{
			Motor8.PosPre = Motor8.PosNow;
			Motor8.PosNow =  (short)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
		}
		Motor8.PositionMeasure += Get_RM2006_Distance(Motor8);
	}
}
	

extern u8 Yaw_Start_Angle_Flag;
extern float Yaw_PC_Angle;
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断//1ms进一次中断
	{
//		if(Yaw_Start_Angle_Flag==0)
//		{
//			Send_To_PC_Yaw_Angle();
//		}
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

