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

	COMFunDict g_My_USART1_Prop_Array[] = {
		{NULL,NULL},
	};
	COMFunDict g_My_USART2_Prop_Array[] = {
		{NULL,NULL},
	};
/*	COMFunDict g_My_USART3_Prop_Array[] = {
		{NULL,NULL},
	};  */
	COMFunDict g_My_USART4_Prop_Array[] = {
		{USART_TEST,Usart_Test},
		{BLUETOOTH_GET_4CLAW,BlueTooth_Get_4Claw},
	/*	{GUN_FOR_SHOOT_8CLAW,Gun_For_Shoot_8Claw},
		{GUN_SHOOT_8CLAW,Gun_Shoot_8Claw},
		{GUN_FOR_CIRCLE_8CLAW,Gun_For_Circle_8Claw},
		{GUN_RESET_8CLAW,Gun_Reset_8Claw},
		{GUN_ANGLE_GET_8CLAW,Gun_Angle_Get_8Claw},
		{GUN_STOP_8CLAW,Gun_Stop_8Claw},
		{GUN_ON_PLACE_8CLAW,Gun_On_Place_8Claw},
		{GUN_SINGLE_SHOOT_8CLAW,Gun_Single_Shoot_8Claw},
		
		{GUN_IN_ADVANCE_8CLAW,Gun_In_Advance_8Claw},
		
		{SITE_CHOOESE_8CLAW,Site_Chooese_8Claw},
		{RENEW_SITE_8CLAW,Renew_Site_8Claw},
	*/
	};


const uint8_t g_My_USART1_Prop_Count = sizeof(g_My_USART1_Prop_Array) /
                                       sizeof(g_My_USART1_Prop_Array[0]);
const uint8_t g_My_USART2_Prop_Count = sizeof(g_My_USART2_Prop_Array) /
                                       sizeof(g_My_USART2_Prop_Array[0]);
/*const uint8_t g_My_USART3_Prop_Count = sizeof(g_My_USART3_Prop_Array) /
                                       sizeof(g_My_USART3_Prop_Array[0]); */
const uint8_t g_My_USART4_Prop_Count = sizeof(g_My_USART4_Prop_Array) /
                                       sizeof(g_My_USART4_Prop_Array[0]);
