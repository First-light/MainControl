#include "elmo.h"
#include "delay.h"

void ProcessElmoFrame(Frame* Frame_Process)
{
  STD_ID_Typedef	StdId;
  StdId.all = Frame_Process->id.StdID;
  if(StdId.ID.COB_ID == COB_TPDO3)
	{
		if(StdId.ID.DeviceId == 1)
		{
			EC22_Motor.SpeedMeasure=(float)(Frame_Process->data.ints[0])/SPEED_PARA;
      EC22_Motor.PositionMeasure=(float)(Frame_Process->data.ints[1])/POSITION_PARA;//接收速度信息
		}
	} 
}

void StopTPDO(uint8_t TPDONum, uint8_t DevId,CAN_TypeDef* CANx)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x1a;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
	}
}


void Set_Yaw_EC22_VCT_FeedBack(uint8_t TPDONum, uint8_t DevId)//PCT:Position,Velocity,Current,Torque,use CAN1
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	
  /*velocity*/
  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
  TxMessage.Data[1] = TPDONum / 2 - 1;
  TxMessage.Data[2] = 0x1a;
  TxMessage.Data[3] = 0x01;
  TxMessage.Data[4] = 0x20;  // 0x20=32 means 32 bits
  TxMessage.Data[5] = 0;
  TxMessage.Data[6] = 0x69;
  TxMessage.Data[7] = 0x60;
	

	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

	TransmitMailbox = CAN_TxStatus_NoMailBox;
	time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	
	/*position*/
  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
  TxMessage.Data[1] = TPDONum / 2 - 1;
  TxMessage.Data[2] = 0x1a;
  TxMessage.Data[3] = 0x02;
  TxMessage.Data[4] = 0x20;
  TxMessage.Data[5] = 0;
  TxMessage.Data[6] = 0x64;
  TxMessage.Data[7] = 0x60;
	
//  /*Current*/
//  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
//  TxMessage.Data[1] = TPDONum / 2 - 1;
//  TxMessage.Data[2] = 0x1a;
//  TxMessage.Data[3] = 0x02;
//  TxMessage.Data[4] = 0x10;  // 0x10=16,means 16 bits
//  TxMessage.Data[5] = 0;
//  TxMessage.Data[6] = 0x78;
//  TxMessage.Data[7] = 0x60;


	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	
//	TransmitMailbox = CAN_TxStatus_NoMailBox;
//  time_out_count = 0;
//  TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
//  TxMessage.IDE = CAN_ID_STD;
//  TxMessage.RTR = CAN_RTR_DATA;
//  TxMessage.DLC = 8;
//	
//  /*Torque*/
//  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
//  TxMessage.Data[1] = TPDONum / 2 - 1;
//  TxMessage.Data[2] = 0x1a;
//  TxMessage.Data[3] = 0x03;
//  TxMessage.Data[4] = 0x10;
//  TxMessage.Data[5] = 0;
//  TxMessage.Data[6] = 0x77;
//  TxMessage.Data[7] = 0x60;

//  while ((TransmitMailbox == CAN_TxStatus_NoMailBox) &&
//         (time_out_count++ != 0xFF)) {
//    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
//  }
}

void Set_Yaw_EC22_PCT_FeedBack(uint8_t TPDONum, uint8_t DevId)
{
  CanTxMsg TxMessage;
  uint16_t i = 0;
  uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;
  uint16_t time_out_count = 0;
  TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.DLC = 8;

  /*position*/
  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
  TxMessage.Data[1] = TPDONum / 2 - 1;
  TxMessage.Data[2] = 0x1a;
  TxMessage.Data[3] = 0x01;
  TxMessage.Data[4] = 0x20;
  TxMessage.Data[5] = 0;
  TxMessage.Data[6] = 0x64;
  TxMessage.Data[7] = 0x60;

  while ((TransmitMailbox == CAN_TxStatus_NoMailBox) &&
         (time_out_count++ != 0xFF)) {
    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
  }

  TransmitMailbox = CAN_TxStatus_NoMailBox;
  time_out_count = 0;
  TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.DLC = 8;

  /*Current*/
  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
  TxMessage.Data[1] = TPDONum / 2 - 1;
  TxMessage.Data[2] = 0x1a;
  TxMessage.Data[3] = 0x02;
  TxMessage.Data[4] = 0x10;
  TxMessage.Data[5] = 0;
  TxMessage.Data[6] = 0x78;
  TxMessage.Data[7] = 0x60;

  while ((TransmitMailbox == CAN_TxStatus_NoMailBox) &&
         (time_out_count++ != 0xFF)) {
    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
  }

  TransmitMailbox = CAN_TxStatus_NoMailBox;
  time_out_count = 0;
  TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.DLC = 8;

  /*Torque*/
  TxMessage.Data[0] = 0x23;  // DSP 301  4-2  P22
  TxMessage.Data[1] = TPDONum / 2 - 1;
  TxMessage.Data[2] = 0x1a;
  TxMessage.Data[3] = 0x03;
  TxMessage.Data[4] = 0x10;
  TxMessage.Data[5] = 0;
  TxMessage.Data[6] = 0x77;
  TxMessage.Data[7] = 0x60;

  while ((TransmitMailbox == CAN_TxStatus_NoMailBox) &&
         (time_out_count++ != 0xFF)) {
    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
  }

}

void SetEventTimer(uint8_t TPDONum, uint8_t DevId, uint8_t Time ,CAN_TypeDef* CANx)//set PDO trigger time
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;

	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC =8;

	/*Event Timer*/
	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x18;
	TxMessage.Data[3] = 0x05;
	TxMessage.Data[4] = Time;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
	}

	
	TransmitMailbox = CAN_TxStatus_NoMailBox;
	time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

		/*Transmit PDO communication parameter 0xfe*/
	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x18;
	TxMessage.Data[3] = 0x02;
	TxMessage.Data[4] = 0xfe;//if use time trigger not sync,set 0xfe or oxff
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
	}
}

void ActivateTPDO(uint8_t TPDONum, uint8_t DevId, CAN_TypeDef* CANx)//set numbers of mapped objects
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 5;

	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x1a;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 2;				//active 3 mapped objects
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
	}
}

void NMT_StartNode(CAN_TypeDef* CANx)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = 0;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 2;

	TxMessage.Data[0] = 1;			//DSP 301  4-2  P22
	TxMessage.Data[1] = 0;
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
	}
}

void MotorOn(CAN_TypeDef* CANx)
{
	CanTxMsg TxMessage;
	uint8_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = 0;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'M';
	TxMessage.Data[1] = 'O';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 1;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;

	for(i = 1; i <5; i++)
		{
			TxMessage.StdId = BUILD_COB(COB_RPDO2, i);
			time_out_count = 0;
			TransmitMailbox = CAN_TxStatus_NoMailBox;	
			while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
			{
				TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
			}
			MyDelayus(20);
		}
}

void MotorOff(CAN_TypeDef* CANx)
{
	CanTxMsg TxMessage;
	uint8_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = 0;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'M';
	TxMessage.Data[1] = 'O';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
//ec22 ID为1
	for(i = 1; i < 5; i++)
		{
			TxMessage.StdId = BUILD_COB(COB_RPDO2, i);
			time_out_count = 0;
			TransmitMailbox = CAN_TxStatus_NoMailBox;	
			while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
			{
				TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
			}
			MyDelayus(20);
		}
}

void Change_To_PositionMode(void)
{
	MotorOff(CAN1);
	MyDelayms(1);
	
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RPDO2, 1);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'U';			//DSP 301  4-2  P22
	TxMessage.Data[1] = 'M';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 5;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
  MyDelayms(1);
	MotorOn(CAN1);
	MyDelayms(1);

}
void Change_To_VelocityMode(void)
{
	MotorOff(CAN1);
	MyDelayms(1);
	
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RPDO2, 1);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'U';			//DSP 301  4-2  P22
	TxMessage.Data[1] = 'M';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 2;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
  MyDelayms(1);
	MotorOn(CAN1);
	MyDelayms(1);
}
void Set_Yaw_EC22_MotorSpeed(int32_t Speed, int32_t DevId)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;	
	TxMessage.StdId = BUILD_COB(COB_RPDO2, DevId);
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'J';			//DSP 301  4-2  P22
	TxMessage.Data[1] = 'V';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = Speed & 0xff;
	TxMessage.Data[5] = (Speed >> 8) & 0xff;
	TxMessage.Data[6] = (Speed >> 16) & 0xff;
	TxMessage.Data[7] = (Speed >> 24) & 0xff;
	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(20);

	TxMessage.StdId = BUILD_COB(COB_RPDO2, DevId);
	TxMessage.DLC = 4;
	TxMessage.Data[0] = 'B';
	TxMessage.Data[1] = 'G';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(20);
}

void Yaw_EC22_SpeedUpdate(float Speed1)
{
	Set_Yaw_EC22_MotorSpeed((int32_t)(LaunchMotor_DIR*Speed1*SPEED_PARA), 1);
}

void Set_Yaw_EC22_MotorPosition(int32_t Position, int32_t MaxSpeed, int32_t DevId)//use CAN1
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;	
	TxMessage.StdId = BUILD_COB(COB_RPDO2, DevId);
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'S';			//set max speed
	TxMessage.Data[1] = 'P';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = MaxSpeed & 0xff;
	TxMessage.Data[5] = (MaxSpeed >> 8) & 0xff;
	TxMessage.Data[6] = (MaxSpeed >> 16) & 0xff;
	TxMessage.Data[7] = (MaxSpeed >> 24) & 0xff;
	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(20);

	TxMessage.DLC = 8;
	TxMessage.Data[0] = 'P';			//ptp position control
	TxMessage.Data[1] = 'A';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = Position & 0xff;
	TxMessage.Data[5] = (Position >> 8) & 0xff;
	TxMessage.Data[6] = (Position >> 16) & 0xff;
	TxMessage.Data[7] = (Position >> 24) & 0xff;
	
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(20);

	TxMessage.DLC = 4;
	TxMessage.Data[0] = 'B';
	TxMessage.Data[1] = 'G';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(20);
}

void Yaw_EC22_PositionUpdate(float Position1,int32_t MaxSpeed)
{
	Set_Yaw_EC22_MotorPosition(LaunchMotor_DIR*Position1*POSITION_PARA,MaxSpeed*SPEED_PARA,1);
}


void SetLaunchMotorDeceleration(int32_t Position1, int32_t MaxSpeed1, int32_t Decel, int32_t DevId)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;	
	TxMessage.StdId = BUILD_COB(COB_RPDO2, DevId);
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'S';			//set max speed
	TxMessage.Data[1] = 'P';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = MaxSpeed1 & 0xff;
	TxMessage.Data[5] = (MaxSpeed1 >> 8) & 0xff;
	TxMessage.Data[6] = (MaxSpeed1 >> 16) & 0xff;
	TxMessage.Data[7] = (MaxSpeed1 >> 24) & 0xff;
	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(10);

	TxMessage.DLC = 8;
	TxMessage.Data[0] = 'P';			//ptp position control
	TxMessage.Data[1] = 'A';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = Position1 & 0xff;
	TxMessage.Data[5] = (Position1 >> 8) & 0xff;
	TxMessage.Data[6] = (Position1 >> 16) & 0xff;
	TxMessage.Data[7] = (Position1 >> 24) & 0xff;
	
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(10);
	
	TxMessage.DLC = 8;
	TxMessage.Data[0] = 'D';			//ptp position control
	TxMessage.Data[1] = 'C';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = Decel & 0xff;
	TxMessage.Data[5] = (Decel >> 8) & 0xff;
	TxMessage.Data[6] = (Decel >> 16) & 0xff;
	TxMessage.Data[7] = (Decel >> 24) & 0xff;
	
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(10);

	TxMessage.DLC = 4;
	TxMessage.Data[0] = 'B';
	TxMessage.Data[1] = 'G';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	MyDelayus(10);
}


void Yaw_EC22_MotorInit(int32_t DevId)
{
	StopTPDO(COB_TPDO3,DevId,CAN1);
		MyDelayms(1);
	Set_Yaw_EC22_VCT_FeedBack(COB_TPDO3,DevId);
//	Set_Yaw_EC22_PCT_FeedBack(COB_TPDO3, DevId);
		MyDelayms(1);
	SetEventTimer(COB_TPDO3, DevId, 10,CAN1); 
		MyDelayms(1);
	ActivateTPDO(COB_TPDO3, DevId,CAN1);
		MyDelayms(1);
}

void ElmoInit(void)
{
	Yaw_EC22_MotorInit(1);//击球电机初始化
  
	NMT_StartNode(CAN1);
	MyDelayms(10);
	MotorOn(CAN1);	
  MyDelayms(10);
//  MotorOn(CAN1);
//  MyDelayms(10);
//	MotorOn(CAN1);
}

