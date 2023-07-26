#include "RobotCAN_Basic.h"
#include "RobotCAN_IDconf.h"
#include "string.h"
#include "stdbool.h"

Frame   Frame1_rcv;  			//对应CAN1 接收
Frame   Frame2_rcv;  			//对应CAN2

extern FunDict CAN1_PROP_Array[];
extern FunDict CAN2_PROP_Array[];

extern const uint8_t CAN1_PROP_COUNT;
extern const uint8_t CAN2_PROP_COUNT;

void (*FindMethod(uint8_t prop,FunDict* PropsArray,uint8_t props_count))(Frame* frm);

/**************************************************

发送（SendFrame）和接受（GetFrame）的接口

**************************************************/
void SendFrame(Frame* Frame_send, CAN_TypeDef* CANx)
{
	  CanTxMsg TxMessage;
    uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;
    uint16_t i = 0;
	  uint16_t  time_out_count = 0;
	
    TxMessage.ExtId = Frame_send->id.all&0x0fffffff;
    TxMessage.IDE = CAN_ID_EXT;
    
		if(Frame_send->isRemote)
    {
        TxMessage.RTR = CAN_RTR_REMOTE;
        TxMessage.DLC = 0;
    }
    else
    {
        TxMessage.RTR = CAN_RTR_DATA;
        TxMessage.DLC = Frame_send->length;
        for(i = 0; i < 8; ++i)
        {
            TxMessage.Data[i] = Frame_send->data.chars[i];
        }
    }

    while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
    {
				TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
		}
}
/**
  * @brief  接收帧数据
  * @param  接收帧数据的指针，可以是 &Frame1_rcv，对应CAN1 ;也可以 是&Frame2_rcv，对应CAN2
  * @retval 无
*/
void GetFrame(Frame* Frame_get, CAN_TypeDef* CANx)
{
	  CanRxMsg RxMessage;
    if(CANx == CAN1)
		{
			CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
		}        
    else
		{
			CAN_Receive(CAN2, CAN_FIFO1, &RxMessage);
		}
        
    Frame_get->id.all = RxMessage.ExtId;
    Frame_get->isRemote = RxMessage.RTR == CAN_RTR_DATA ? 0 : 1;
    Frame_get->length = RxMessage.DLC;
    memcpy(Frame_get->data.chars,(char*)RxMessage.Data,Frame_get->length);
}




void ProcessFrame(Frame* Frame_Process, CAN_TypeDef* CANx)
{
    void(* fun)(Frame* frm);
	  FunDict* PropsArray;
	  uint8_t props_count;
	
	  EXT_ID_Typedef *Frame_ID = &(Frame_Process->id.ExtID);
	
		if(CANx == CAN1)
		{
			PropsArray = CAN1_PROP_Array;
			props_count = CAN1_PROP_COUNT;
		}
		else if(CANx == CAN2)
		{
			PropsArray = CAN2_PROP_Array;
			props_count = CAN2_PROP_COUNT;
		}
		else
		{
			return ;
		}			
	
		if((fun = FindMethod(Frame_ID->Property,PropsArray,props_count)) != 0)
		{					  
			fun(Frame_Process);
			if(Frame_Process->isRemote)
			{
				Frame_ID->DesDEVICE_ID   = Frame_ID->SrcDEVICE_ID;
				if(CANx == CAN1)
				{
					Frame_ID->SrcDEVICE_ID = DEVICE_ID;
				}
				else if(CANx == CAN2)
				{
					Frame_ID->SrcDEVICE_ID	=	DEVICE_SECOND_ID;
				}
				
				Frame_Process->isRemote = 0;				
				SendFrame(Frame_Process,CANx);
			}
		}		
}


void (*FindMethod(uint8_t Prop,FunDict* PropsArray,uint8_t props_count))(Frame* frm)
{
	uint8_t i;
	for(i = 0; i < props_count; ++i)
	{
		if(PropsArray[i].prop == Prop)
		{
			return PropsArray[i].fun;
		}
	}
	return 0;
}
/*********--------      end      --------*********/
