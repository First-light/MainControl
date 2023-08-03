/**
 ******************************************************************************
 * @file    RobotCAN_proplist.c
 * @author  Robocon
 * @brief   本代码提供了CAN消息处理函数词典的定义:
 *           - CAN1消息处理函数字典
 *           - CAN2消息处理函数字典
 *  @verbatim
 *          本字典用于ProcessFrame()中根据属性值查找对应的消息处理函数
 * 		     根据需求在ExecuteLib.c中添加相应的消息处理函数后，更新相应的proplist.c，
 * 		     在头文件中设置相应的属性值
 *  @endverbatim
 ******************************************************************************
 */
#include "RobotCOM_Basic.h"
#include "RobotCOM_proplist.h"
#include "stm32f4xx_can.h"
#include "hust_math_lib.h"
/*******************************属性和方法字典***********************************/

	COMFunDict g_My_USART1_Prop_Array[] = { //传感器
		{USART_SUBMAINECHO_4CLAW,Usart_SubMainEcho_4Claw},
		{USART_SUBMAINLINE_8CLAW,Usart_SubMainLine_8Claw},
		{USART_SUBMAINPOINT_8CLAW,Usart_SubMainPoint_8Claw},
	};
	COMFunDict g_My_USART2_Prop_Array[] = {
		{NULL,NULL},
	};
/*	COMFunDict g_My_USART3_Prop_Array[] = {
		{NULL,NULL},
	};  */
	COMFunDict g_My_USART4_Prop_Array[] = {	//蓝牙
		{USART_TEST,Usart_Test},
		{BLUETOOTH_GET_BUTTON_4CLAW,BlueTooth_Get_BUTTON_4Claw},
		{BLUETOOTH_GET_JOYSTICKL_4CLAW,BlueTooth_Get_JOYSTICK_LEFT_4Claw},
		{BLUETOOTH_GET_JOYSTICKR_4CLAW,BlueTooth_Get_JOYSTICK_RIGHT_4Claw},	
	};


const uint8_t g_My_USART1_Prop_Count = sizeof(g_My_USART1_Prop_Array) /
                                       sizeof(g_My_USART1_Prop_Array[0]);
const uint8_t g_My_USART2_Prop_Count = sizeof(g_My_USART2_Prop_Array) /
                                       sizeof(g_My_USART2_Prop_Array[0]);
/*const uint8_t g_My_USART3_Prop_Count = sizeof(g_My_USART3_Prop_Array) /
                                       sizeof(g_My_USART3_Prop_Array[0]); */
const uint8_t g_My_USART4_Prop_Count = sizeof(g_My_USART4_Prop_Array) /
                                       sizeof(g_My_USART4_Prop_Array[0]);
