/**
 ******************************************************************************
 * @file    RobotCOM_proplist.h
 * @brief   串口发送及接收处理函数头文件，包含以下内容：
 *          - 各串口属性方法词典声明
 *          - 各串口属性值定义
 *          - 各串口方法函数声明
 * @verbatim
 *          添加新的处理函数后要对这里进行维护
 * @endverbatim
 * @edit date
 ******************************************************************************
 */
#ifndef ROBOTCOM_PROPLIST_H_
#define ROBOTCOM_PROPLIST_H_

#include "RobotCOM_Basic.h"


/* ************************************ 类型 **************************************** */
#define POINT_TYPE 4//点检测器的个数

typedef enum {
	LeftPoint,
	RightPoint,
	CenterPoint,
	FrontPoint,
} PointType;//点检测器的类型

/* ************************************ 全局声明 **************************************** */

extern uint32_t Echo_MM;//超声波检测的距离（mm）

extern int16_t FrontLine;//前轮偏移 0为无偏移//向右为正
extern int16_t BehindLine;//后轮偏移
extern uint8_t FrontCount;
extern uint8_t BehindCount;

extern uint8_t PointList[POINT_TYPE];//点检测

extern uint8_t JoystickLeftX;
extern uint8_t JoystickLeftY;

/* ************************************ 字典声明 **************************************** */

extern COMFunDict g_My_USART1_Prop_Array[];

extern COMFunDict g_My_USART2_Prop_Array[];

//extern COMFunDict g_My_USART3_Prop_Array[];

extern COMFunDict g_My_USART4_Prop_Array[];

extern const uint8_t g_My_USART1_Prop_Count;

extern const uint8_t g_My_USART2_Prop_Count;

//extern const uint8_t g_My_USART3_Prop_Count;

extern const uint8_t g_My_USART4_Prop_Count;

/* ************************************ 属性值 **************************************** */

#define USART_TEST 0x99

#define BLUETOOTH_GET_BUTTON_4CLAW 0x97
#define BLUETOOTH_GET_JOYSTICKL_4CLAW 0x98
#define BLUETOOTH_GET_JOYSTICKR_4CLAW 0x98

#define USART_SUBMAINECHO_4CLAW 0x51
#define USART_SUBMAINLINE_8CLAW 0x52
#define USART_SUBMAINPOINT_8CLAW 0x53

/* ************************************ 处理函数 **************************************** */

void Usart_Test(COMFrame *Frame);//test
void BlueTooth_Get_BUTTON_4Claw(COMFrame *Frame);
void BlueTooth_Get_JOYSTICK_LEFT_4Claw(COMFrame *Frame);
void BlueTooth_Get_JOYSTICK_RIGHT_4Claw(COMFrame *Frame);

void Usart_SubMainEcho_4Claw(COMFrame *Frame);
void Usart_SubMainLine_8Claw(COMFrame *Frame);
void Usart_SubMainPoint_8Claw(COMFrame *Frame);

/* ************************************ 发送函数 **************************************** */
//不封装的串口信息发送
void UART_SendByte(USART_TypeDef* USARTx,uint8_t data);
void UART_SendString(USART_TypeDef* USARTx,char* string);
void UART_SendNum_Short(USART_TypeDef* USARTx,int Num);
	//先将int转换为string，再输出，但是最大输出为64位int
void Task_Over_Send(void);//向蓝牙发送任务结束信息

void Test_Send(void);
	 
#endif
