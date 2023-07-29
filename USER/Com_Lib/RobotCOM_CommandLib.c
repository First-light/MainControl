/**
 ******************************************************************************
 * @file    RobotCOM_CommandLib.c
 * @author  Robocon
 * @brief   本代码提供了利用串口通信发送消息功能的封装:
 *           - 根据每年机器人的具体需求，自行定义相应的发送函数
 *  @verbatim
 *
 *  @endverbatim
 ******************************************************************************
 */
#include "RobotCOM_Basic.h"
#include "RobotCOM_proplist.h"

	/***************************************MYUSART1发送函数******************************************/
/*	
void Renew_Site_2Claw(uint8_t site_order)
{
	COMFrame SendFrame;
	SendFrame.Length = 1;
	SendFrame.Prop = RENEW_SITE_2CLAW;
	SendFrame.Data.uint8_ts[0] = site_order;
	Send_Frame_COM(&SendFrame, MYUSART4);
}
 */

	
//	void Crane_Get_Left_Circle(void)
//	{
//		COMFrame SendFrame;
//    SendFrame.Length = 0;
//    SendFrame.Prop = CRANE_GET_LEFT_CIRCLE;
//    Send_Frame_COM(&SendFrame, MYUSART1);
//	}
	/***************************************MYUSART4发送函数******************************************/

void UART_SendByte(USART_TypeDef* USARTx,uint8_t data)
{
	while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));//等上一次发完
	USART_SendData(USARTx,data);
	while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));//USART_GetFlagStatus在检测到有数据为0，无数据为1
	//这样编写存在问题，可以这样改进
}

void UART_SendString(USART_TypeDef* USARTx,char* string)
{
	 char* str = string;
	 while(*str)//当str指向的字符不为空，则继续
	 {
		 UART_SendByte(USARTx,*str);
		 str++;//指针
	 }
}

void Test_Send(void)
{
	COMFrame SendFrame;
	SendFrame.Length = 1;
	SendFrame.Prop = USART_TEST;
	SendFrame.Data.uint8_ts[0] = 'A';
	Send_Frame_COM(&SendFrame, MYUSART4);
}

void Task_Over_Send(void)
{
	UART_SendString(MY_USART4,"TASK_OVER\n");
}
