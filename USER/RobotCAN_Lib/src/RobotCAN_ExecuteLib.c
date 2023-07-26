#include "RobotCAN_IDconf.h"
#include "RobotCAN_Basic.h"
#include "MyGlobe.h"

/**************************************************
							 各属性对应的执行程序
**************************************************/
//Locate-->drivers
//void SetMotorsPara(Frame* frm)
//{	
//	CAN_Data* data = &(frm->data);
//	Motor.State = PIDSPEED;

//	Motor.SpeedExpected = (float)frm->data.shorts[DEVICE_ID - CHASSIS_MOTOR1_ID]*0.1f;

//  CAN_feedDog	= 0;
//}



//void SetMotorsCtrl(Frame* frm)  
//{
//	CAN_Data* data = &(frm->data);	
//	if(data->uchars[0] & (0x01 << (DEVICE_ID - BROADCAST_ID - 1)))
//	{
//		
//		Motor.State = PIDSPEED;
//	}
//	else
//	{
//		Motor.State = MOTOR_ERROR;
//	}
//}

