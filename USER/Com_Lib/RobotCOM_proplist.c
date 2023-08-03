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

	COMFunDict g_My_USART1_Prop_Array[] = { //������
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
	COMFunDict g_My_USART4_Prop_Array[] = {	//����
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
