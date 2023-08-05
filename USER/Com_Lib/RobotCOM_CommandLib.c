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
#include "task_init.h"

	/***************************************MYUSART1发送函数******************************************/
void Action_Send(void) //USART1是SubBoard
{
	COMFrame SendFrame;
	SendFrame.Length = 8;
	SendFrame.Prop = USART_MAINACTIONS_8CLAW;
	SendFrame.Data.uint8_ts[0] = (uint8_t)GasPushRod;
	Send_Frame_COM(&SendFrame, MYUSART1);
}//发送信息到SubBoard控制气推杆

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

void UART_SendNum_Short(USART_TypeDef* USARTx,int Num)//先将int转换为string，再输出，但是最大输出为64位int
{
	char temp[64] = {'\0'};
	if ( Num < 0 )
	{
		Num = -Num;
		temp[0] = '-';
		CHAR_INT_Change(&temp[1],Num);
	}
	else
	{
		CHAR_INT_Change(temp,Num);
	} 
	UART_SendString(USARTx,temp);
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
