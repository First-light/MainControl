/**
 ******************************************************************************
 * @file    RobotCOM_CommandLib.c
 * @author  Robocon
 * @brief   �������ṩ�����ô���ͨ�ŷ�����Ϣ���ܵķ�װ:
 *           - ����ÿ������˵ľ����������ж�����Ӧ�ķ��ͺ���
 *  @verbatim
 *
 *  @endverbatim
 ******************************************************************************
 */
#include "RobotCOM_Basic.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"

	/***************************************MYUSART1���ͺ���******************************************/
void Action_Send(void) //USART1��SubBoard
{
	COMFrame SendFrame;
	SendFrame.Length = 8;
	SendFrame.Prop = USART_MAINACTIONS_8CLAW;
	SendFrame.Data.uint8_ts[0] = (uint8_t)GasPushRod;
	Send_Frame_COM(&SendFrame, MYUSART1);
}//������Ϣ��SubBoard�������Ƹ�

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
	/***************************************MYUSART4���ͺ���******************************************/

void UART_SendByte(USART_TypeDef* USARTx,uint8_t data)
{
	while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));//����һ�η���
	USART_SendData(USARTx,data);
	while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));//USART_GetFlagStatus�ڼ�⵽������Ϊ0��������Ϊ1
	//������д�������⣬���������Ľ�
}

void UART_SendString(USART_TypeDef* USARTx,char* string)
{
	 char* str = string;
	 while(*str)//��strָ����ַ���Ϊ�գ������
	 {
		 UART_SendByte(USARTx,*str);
		 str++;//ָ��
	 }
}

void UART_SendNum_Short(USART_TypeDef* USARTx,int Num)//�Ƚ�intת��Ϊstring�������������������Ϊ64λint
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
