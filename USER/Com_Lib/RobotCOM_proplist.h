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


/* ************************************ ���� **************************************** */
#define POINT_TYPE 4//�������ĸ���

typedef enum {
	LeftPoint,
	RightPoint,
	CenterPoint,
	FrontPoint,
} PointType;//������������

/* ************************************ ȫ������ **************************************** */

extern uint32_t Echo_MM;//���������ľ��루mm��

extern int16_t FrontLine;//ǰ��ƫ�� 0Ϊ��ƫ��//����Ϊ��
extern int16_t BehindLine;//����ƫ��
extern uint8_t FrontCount;
extern uint8_t BehindCount;

extern uint8_t PointList[POINT_TYPE];//����

extern uint8_t JoystickLeftX;
extern uint8_t JoystickLeftY;

/* ************************************ �ֵ����� **************************************** */

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

#define BLUETOOTH_GET_BUTTON_4CLAW 0x97
#define BLUETOOTH_GET_JOYSTICKL_4CLAW 0x98
#define BLUETOOTH_GET_JOYSTICKR_4CLAW 0x98

#define USART_SUBMAINECHO_4CLAW 0x51
#define USART_SUBMAINLINE_8CLAW 0x52
#define USART_SUBMAINPOINT_8CLAW 0x53

/* ************************************ ������ **************************************** */

void Usart_Test(COMFrame *Frame);//test
void BlueTooth_Get_BUTTON_4Claw(COMFrame *Frame);
void BlueTooth_Get_JOYSTICK_LEFT_4Claw(COMFrame *Frame);
void BlueTooth_Get_JOYSTICK_RIGHT_4Claw(COMFrame *Frame);

void Usart_SubMainEcho_4Claw(COMFrame *Frame);
void Usart_SubMainLine_8Claw(COMFrame *Frame);
void Usart_SubMainPoint_8Claw(COMFrame *Frame);

/* ************************************ ���ͺ��� **************************************** */
//����װ�Ĵ�����Ϣ����
void UART_SendByte(USART_TypeDef* USARTx,uint8_t data);
void UART_SendString(USART_TypeDef* USARTx,char* string);
void UART_SendNum_Short(USART_TypeDef* USARTx,int Num);
	//�Ƚ�intת��Ϊstring�������������������Ϊ64λint
void Task_Over_Send(void);//�������������������Ϣ

void Test_Send(void);
	 
#endif
