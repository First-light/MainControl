/**
  ******************************************************************************
  * @file    RobotCOM_basic.h
  * @author  Robocon
  * @brief   本代码提供了对于使用串口通信时所需的所有声明和定义:
  *           - 团队串口协议中串口帧格式的定义
  *           - 各串口相应的发送和接收帧的声明
  *           - 串口口所需用到的发送，接收和帧处理函数的声明(发送函数经过2次封装到
  *             CommandLib中)
  *  @verbatim
  *  @endverbatim
  ******************************************************************************  
  */ 
#ifndef ROBOTCOM_BASIC_H_
#define ROBOTCOM_BASIC_H_

#include "Includes.h"
#include "USART.h"
#include "string.h"
#include "motor_control.h"

/******************************对COM通信协议的定义*********************************/
#define COM_FRAME_MAX_LENGTH        0XE0
#define COM_FRAME_MARK              0XEE            //帧头
#define COM_FRAME_ESCAPE            0XFF            //帧尾

/******************************对COM状态的定义*********************************/
#define HEAD_DETECT                 0
#define LENGTH_ACQUIRE              1
#define PROP_ACQUIRE                2
#define DATA_ACQUIRE                3
#define TAIL_CONFIRM                4

/******************************对COM帧内的数据格式定义*********************************/
typedef union {
    int8_t    int8_ts[128];
    int16_t   int16_ts[64];
    int32_t   int32_ts[32];
    uint8_t   uint8_ts[128];
    uint16_t  uint16_ts[64];
    uint32_t  uint32_ts[32];
    float     floats_ts[32];
} COMData;

/******************************对CAN帧内的特殊位定义*********************************/
typedef struct {
    uint8_t   Length;
    uint8_t   Prop;
    COMData   Data;
} COMFrame;

/******************************对COM状态描述定义*********************************/
typedef struct {
    uint8_t RecStatus;
    uint8_t RecCounts;
    uint8_t preData;
    uint8_t RecLength;
} COMRecStatus;

/******************************建立属性值与处理函数对应结构*********************************/
typedef struct {
    uint16_t Prop;                                  //属性名称
    void (*Fun)(COMFrame* Frm);                     //此属性对应的处理函数
} COMFunDict;

/******************************消息声明*********************************/
extern COMFrame         g_My_USART1_COM_Rec;
extern COMRecStatus     g_My_USART1_COM_Rec_Status;
extern COMFrame         g_My_USART2_COM_Rec;
extern COMRecStatus     g_My_USART2_COM_Rec_Status;
//extern COMFrame         g_My_USART3_COM_Rec;
//extern COMRecStatus     g_My_USART3_COM_Rec_Status;
extern COMFrame         g_My_USART4_COM_Rec;
extern COMRecStatus     g_My_USART4_COM_Rec_Status;

/******************************处理函数*********************************/
void Send_Frame_COM(COMFrame*, MyUSARTTypedef);
void Get_Frame_COM(uint8_t, MyUSARTTypedef);
void Process_Frame_COM(COMFrame*, MyUSARTTypedef);


#endif /*ROBOTCOM_BASIC_H_*/


