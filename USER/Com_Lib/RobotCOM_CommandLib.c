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

void Test_Send(void)
{
	COMFrame SendFrame;
	SendFrame.Length = 1;
	SendFrame.Prop = USART_TEST;
	SendFrame.Data.uint8_ts[0] = 'A';
	Send_Frame_COM(&SendFrame, MYUSART4);
}
