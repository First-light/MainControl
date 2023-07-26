/**
  ******************************************************************************
  * @file    RobotCOM_basic.c
  * @author  Robocon
  * @brief   �������ṩ��ʹ��CANͨ�����躯���Ķ���:
  *           - ����CAN��Ϣ����
  *           - ����CAN��Ϣ����
  *           - ����CAN��Ϣ����
  *  @verbatim
  *          CANͨ�ŷ�����Ϣ����CommandLib.c�е���Ӧ����
  *          CANͨ�Ž�����Ϣ�ȵ���GetFrame()�������ݣ��ٵ���ProcessFrame()��������
  *  @endverbatim
  ******************************************************************************  
  */ 
#include "RobotCOM_Basic.h"
#include "RobotCOM_proplist.h"
#include "hust_math_lib.h"
COMFrame        g_My_USART1_COM_Rec;
COMRecStatus    g_My_USART1_COM_Rec_Status;
COMFrame        g_My_USART2_COM_Rec;
COMRecStatus    g_My_USART2_COM_Rec_Status;
//COMFrame        g_My_USART3_COM_Rec;
//COMRecStatus    g_My_USART3_COM_Rec_Status;
COMFrame        g_My_USART4_COM_Rec;
COMRecStatus    g_My_USART4_COM_Rec_Status;

void (*Find_Method_COM(uint8_t Prop, COMFunDict* Props_Array, 
    uint8_t Props_Count))(COMFrame* Frm);

/*************************
 * ���ͣ�SendFrame���ͽ��ܣ�GetFrame���Ľӿ�
 * *************************/
/**
 * @brief  ����֡����
 * @param  ��
 * @retval ��
 */
void Send_Frame_COM(COMFrame* Send_Frame, MyUSARTTypedef USARTx) 
{
    uint8_t *Send_Buf_Temp;
    uint8_t Send_Buf[COM_FRAME_MAX_LENGTH];
    uint8_t Length = Send_Frame->Length;
    uint8_t LengthTemp = Length;

    Send_Buf_Temp = &Send_Buf[0];

    *Send_Buf_Temp++ = COM_FRAME_MARK;
    *Send_Buf_Temp++ = Length;
    *Send_Buf_Temp++ = Send_Frame->Prop;

    for (int i = 0; i < Length; i++) 
    {
        uint8_t Temp = Send_Frame->Data.uint8_ts[i];
        if (Temp == COM_FRAME_MARK) 
        {
            *Send_Buf_Temp++ = COM_FRAME_ESCAPE;
            LengthTemp++;
        }
        *Send_Buf_Temp++ = Temp;
    }
    *Send_Buf_Temp++  = COM_FRAME_MARK;
    LengthTemp       += 4;
    Send_Buf[1]       = LengthTemp;

    #if USARTn >= 1
    if (USARTx == MYUSART1) 
        COM_Write(Send_Buf, LengthTemp, MYUSART1);
    #endif

    #if USARTn >= 2
    if (USARTx == MYUSART2) 
        COM_Write(Send_Buf, LengthTemp, MYUSART2);
    #endif

    /*#if USARTn >= 3
    if (USARTx == MYUSART3) 
        COM_Write(Send_Buf, LengthTemp, MYUSART3);
    #endif */

    #if USARTn >= 3//4
    if (USARTx == MYUSART4) 
        COM_Write(Send_Buf, LengthTemp, MYUSART4);
    #endif
}

/**
 * @brief  ����֡����
 * @param  ����֡���ݵ�ָ�룬������ &Frame1_rcv����ӦCAN1 ;Ҳ������&Frame2_rcv����ӦCAN2
 * @retval ��
 */
void Get_Frame_COM(uint8_t Data, MyUSARTTypedef USARTx) {
    COMRecStatus* pRecInfo;
    COMFrame* pFrame;
    uint8_t Rec_Status, pre_Data;

    if (USARTx == MYUSART1) 
    {
        pRecInfo       = &g_My_USART1_COM_Rec_Status;
        pFrame         = &g_My_USART1_COM_Rec;
    } 
    else if (USARTx == MYUSART2) 
    {
        pRecInfo       = &g_My_USART2_COM_Rec_Status;
        pFrame         = &g_My_USART2_COM_Rec;
    }
  /*  else if (USARTx == MYUSART3) 
    {
        pRecInfo       = &g_My_USART3_COM_Rec_Status;
        pFrame         = &g_My_USART3_COM_Rec;
    }  */
    else if (USARTx == MYUSART4) 
    {
        pRecInfo       = &g_My_USART4_COM_Rec_Status;
        pFrame         = &g_My_USART4_COM_Rec;
    }
    pre_Data   = pRecInfo->preData;
    Rec_Status = pRecInfo->RecStatus;

    if (Data == COM_FRAME_MARK && Rec_Status != TAIL_CONFIRM) 
    {
        if (pre_Data != COM_FRAME_ESCAPE) 
        {
            pRecInfo->RecStatus = HEAD_DETECT;
            Rec_Status = HEAD_DETECT;
        } 
        else 
        {
            if (pFrame->Length > 0)
                pFrame->Length--;
        }
    }

    switch (Rec_Status) 
    {
        case HEAD_DETECT:
            pRecInfo->RecStatus = LENGTH_ACQUIRE;
            break;

        case LENGTH_ACQUIRE:
            if (Data < 4) 
                pRecInfo->RecStatus = HEAD_DETECT;
            else 
            {
                pRecInfo->RecLength = Data;
                pFrame->Length = 0;
                pRecInfo->RecStatus = PROP_ACQUIRE;
            }
            break;

        case PROP_ACQUIRE:
            pFrame->Prop = Data;
            if (pRecInfo->RecLength == 4)
                pRecInfo->RecStatus = TAIL_CONFIRM;
            else 
                pRecInfo->RecStatus = DATA_ACQUIRE;
            break;

        case DATA_ACQUIRE:
            pRecInfo->RecLength--;
            pFrame->Data.uint8_ts[pFrame->Length++] = Data;
            if (pRecInfo->RecLength == 4) 
                pRecInfo->RecStatus = TAIL_CONFIRM;
            break;

        case TAIL_CONFIRM:
            if (COM_FRAME_MARK == Data)
                Process_Frame_COM(pFrame,USARTx);
            pRecInfo->RecStatus = HEAD_DETECT;
            break;
        
        default:
            break;
    }
    pRecInfo->preData = Data;
}

void Process_Frame_COM(COMFrame* Rec_Frame, MyUSARTTypedef USARTx) 
{
    void (*Fun)(COMFrame * Frm);
    COMFunDict* Props_Array;
    uint8_t Props_Count;

    if (USARTx == MYUSART1) 
    {
        Props_Array = g_My_USART1_Prop_Array;
        Props_Count = g_My_USART1_Prop_Count;
    } 
    else if (USARTx == MYUSART2) 
    {
        Props_Array = g_My_USART2_Prop_Array;
        Props_Count = g_My_USART2_Prop_Count;
    }
   /* else if (USARTx == MYUSART3) 
    {
        Props_Array = g_My_USART3_Prop_Array;
        Props_Count = g_My_USART3_Prop_Count;
    } */
    else if (USARTx == MYUSART4) 
    {
        Props_Array = g_My_USART4_Prop_Array;
        Props_Count = g_My_USART4_Prop_Count;
    } 
    else 
        return;

    if ((Fun = Find_Method_COM(Rec_Frame->Prop, Props_Array, Props_Count)) != 0) 
        Fun(Rec_Frame);
}

void (*Find_Method_COM(uint8_t Prop, COMFunDict* Props_Array, 
    uint8_t Props_Count))(COMFrame* Frm) 
{
    uint8_t i;

    for (i = 0; i < Props_Count; ++i) {
        if (Props_Array[i].Prop == Prop) 
            return Props_Array[i].Fun;
    }
    return 0;
}
/*********--------      end      --------*********/
