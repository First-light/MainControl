/**
 ******************************************************************************
 * @file    RobotCOM_proplist.h
 * @brief   ���ڷ��ͼ����մ�����ͷ�ļ��������������ݣ�
 *          - ���������Է����ʵ�����
 *          - ����������ֵ����
 *          - �����ڷ�����������
 * @verbatim
 *          ����µĴ�������Ҫ���������ά��
 * @endverbatim
 * @edit date
 ******************************************************************************
 */
#ifndef ROBOTCOM_PROPLIST_H_
#define ROBOTCOM_PROPLIST_H_

#include "RobotCOM_Basic.h"

/*
#define GUN_FOR_CIRCLE_ON          1
#define GUN_POS_SHOOT_READY        2
#define SWING_ON                   3
#define SHOOTING_SPEED_ON          4
#define SHOOTING_OUT               5
#define SHOOT_OVER_CHECKING        6
#define GUN_SHOOT_OVER_RESET_1     7
#define GUN_SHOOT_OVER_RESET_2     8
#define GUN_RESET_1                9
#define GUN_RESET_2                10
#define GUN_STOP_SHOOTING          11

#define GUN_ON_PLACE_FINE_TUNING 12
#define GUN_SINGLE_SHOOT_FINE_TUNING 13
#define GUN_IN_ADVANCE 14

#define GUN_SPEED_DELTA_UNIT 50
#define GUN_ANGLE_DELTA_UNIT 1
*/

extern COMFunDict g_My_USART1_Prop_Array[];

extern COMFunDict g_My_USART2_Prop_Array[];

//extern COMFunDict g_My_USART3_Prop_Array[];

extern COMFunDict g_My_USART4_Prop_Array[];

extern const uint8_t g_My_USART1_Prop_Count;

extern const uint8_t g_My_USART2_Prop_Count;

//extern const uint8_t g_My_USART3_Prop_Count;

extern const uint8_t g_My_USART4_Prop_Count;

/* ************************************ ����ֵ **************************************** */
#define USART_TEST 0x99
#define BLUETOOTH_GET_4CLAW 0x41
/*
#define GUN_FOR_SHOOT_8CLAW  0x21
#define GUN_SHOOT_8CLAW  0x22
#define GUN_FOR_CIRCLE_8CLAW  0x23
#define GUN_RESET_8CLAW  0x24
#define GUN_ANGLE_GET_8CLAW  0x25
#define GUN_STOP_8CLAW  0x2B
#define GUN_ON_PLACE_8CLAW 0x4B
#define GUN_SINGLE_SHOOT_8CLAW 0x4E

#define GUN_IN_ADVANCE_8CLAW 0x13

#define SITE_CHOOESE_8CLAW 0x1A
#define RENEW_SITE_8CLAW 0x35

#define RENEW_SITE_2CLAW 0x1B
*/
/* ************************************ ������ **************************************** */
void Usart_Test(COMFrame *Frame);//test
void BlueTooth_Get_4Claw(COMFrame *Frame);//���������źţ���ת��Ϊ��������
/*
void Gun_For_Shoot_8Claw(COMFrame *Frame);
void Gun_Shoot_8Claw(COMFrame *Frame);
void Gun_For_Circle_8Claw(COMFrame *Frame);
void Gun_Reset_8Claw(COMFrame *Frame);
void Gun_Angle_Get_8Claw(COMFrame *Frame);
void Gun_Stop_8Claw(COMFrame *Frame);
void Gun_On_Place_8Claw(COMFrame *Frame);
void Gun_Single_Shoot_8Claw(COMFrame *Frame);

void Gun_In_Advance_8Claw(COMFrame *Frame);


void Site_Chooese_8Claw(COMFrame *Frame);
void Renew_Site_8Claw(COMFrame *Frame);

void Renew_Site_2Claw(uint8_t site_order);
*/
/* ************************************ ���ͺ��� **************************************** */
 void Test_Send(void);
	 
#endif
