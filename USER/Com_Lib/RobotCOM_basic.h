/**
  ******************************************************************************
  * @file    RobotCOM_basic.h
  * @author  Robocon
  * @brief   �������ṩ�˶���ʹ�ô���ͨ��ʱ��������������Ͷ���:
  *           - �ŶӴ���Э���д���֡��ʽ�Ķ���
  *           - ��������Ӧ�ķ��ͺͽ���֡������
  *           - ���ڿ������õ��ķ��ͣ����պ�֡������������(���ͺ�������2�η�װ��
  *             CommandLib��)
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

/******************************��COMͨ��Э��Ķ���*********************************/
#define COM_FRAME_MAX_LENGTH        0XE0
#define COM_FRAME_MARK              0XEE            //֡ͷ
#define COM_FRAME_ESCAPE            0XFF            //֡β

/******************************��COM״̬�Ķ���*********************************/
#define HEAD_DETECT                 0
#define LENGTH_ACQUIRE              1
#define PROP_ACQUIRE                2
#define DATA_ACQUIRE                3
#define TAIL_CONFIRM                4

/******************************��COM֡�ڵ����ݸ�ʽ����*********************************/
typedef union {
    int8_t    int8_ts[128];
    int16_t   int16_ts[64];
    int32_t   int32_ts[32];
    uint8_t   uint8_ts[128];
    uint16_t  uint16_ts[64];
    uint32_t  uint32_ts[32];
    float     floats_ts[32];
} COMData;

/******************************��CAN֡�ڵ�����λ����*********************************/
typedef struct {
    uint8_t   Length;
    uint8_t   Prop;
    COMData   Data;
} COMFrame;

/******************************��COM״̬��������*********************************/
typedef struct {
    uint8_t RecStatus;
    uint8_t RecCounts;
    uint8_t preData;
    uint8_t RecLength;
} COMRecStatus;

/******************************��������ֵ�봦������Ӧ�ṹ*********************************/
typedef struct {
    uint16_t Prop;                                  //��������
    void (*Fun)(COMFrame* Frm);                     //�����Զ�Ӧ�Ĵ�����
} COMFunDict;

/******************************��Ϣ����*********************************/
extern COMFrame         g_My_USART1_COM_Rec;
extern COMRecStatus     g_My_USART1_COM_Rec_Status;
extern COMFrame         g_My_USART2_COM_Rec;
extern COMRecStatus     g_My_USART2_COM_Rec_Status;
//extern COMFrame         g_My_USART3_COM_Rec;
//extern COMRecStatus     g_My_USART3_COM_Rec_Status;
extern COMFrame         g_My_USART4_COM_Rec;
extern COMRecStatus     g_My_USART4_COM_Rec_Status;

/******************************������*********************************/
void Send_Frame_COM(COMFrame*, MyUSARTTypedef);
void Get_Frame_COM(uint8_t, MyUSARTTypedef);
void Process_Frame_COM(COMFrame*, MyUSARTTypedef);


#endif /*ROBOTCOM_BASIC_H_*/


