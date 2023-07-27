/**
 ******************************************************************************
 * @file    RobotCAN_proplist.c
 * @author  Robocon
 * @brief   �������ṩ��CAN��Ϣ�������ʵ�Ķ���:
 *           - CAN1��Ϣ�������ֵ�
 *           - CAN2��Ϣ�������ֵ�
 *  @verbatim
 *          ���ֵ�����ProcessFrame()�и�������ֵ���Ҷ�Ӧ����Ϣ������
 * 		     ����������ExecuteLib.c�������Ӧ����Ϣ�������󣬸�����Ӧ��proplist.c��
 * 		     ��ͷ�ļ���������Ӧ������ֵ
 *  @endverbatim
 ******************************************************************************
 */
#include "RobotCOM_Basic.h"
#include "RobotCOM_proplist.h"
#include "stm32f4xx_can.h"
#include "hust_math_lib.h"
/*******************************���Ժͷ����ֵ�***********************************/

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
