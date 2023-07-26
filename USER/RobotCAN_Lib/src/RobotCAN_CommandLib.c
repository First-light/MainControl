#include "RobotCAN_Proplist.h"
#include "RobotCAN_Basic.h"
#include "RobotCAN_IDconf.h"
#include "MyType.h"
#include "MyGlobe.h"

//void SendSingleMotorPara()
//{
//    Frame   Frame_tsm;
//	  CAN_Data* data = &(Frame_tsm.data);
//	  EXT_ID_Typedef* ExtID = &(Frame_tsm.id.ExtID);
//    
//	  ExtID->Priority    =  GET_SINGLE_MOTOR_PARA_PRIO;
//	  ExtID->DesDEVICE_ID =  LOCATE_ID;
//	
//    ExtID->SrcDEVICE_ID =  DEVICE_ID;
//    ExtID->Property    =  GET_SINGLE_MOTOR_PARA;

//    Frame_tsm.isRemote = 0;
//    Frame_tsm.length = 4;

//		
//		data->shorts[0] = (s16)(Motor.SpeedMeasure);
//	  data->shorts[1] = (s16)(Motor.SpeedExpected);


//    SendFrame(&Frame_tsm,CAN1);
//}


