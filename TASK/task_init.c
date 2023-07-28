#include "system_config.h"
#include "RobotCAN_proplist.h"
#include "RobotCOM_proplist.h"
#include "elmo.h"
#include "MyType.h"
#include "motor_control.h"
#include "AS5047P.h"
#include "ADXRS453.h"

#include "TurnArrow.h"
#include "HoldGrip.h"
#include "Archery.h"



//extern float Yaw_PC_Angle;
//extern float Distance,Pitch_Position_Motor;
//extern volatile MotorTypeDef Motorleft, Motorright, Motorpitch;

void TaskIndicate(void *p_arg)
{
    OS_ERR err;
    while(1)
    {
        LED_Toggle(LED1);
        OSTimeDlyHMSM(0, 0, 0, 300, OS_OPT_TIME_HMSM_STRICT, &err);
        LED_Toggle(LED2);
        OSTimeDlyHMSM(0, 0, 0, 300, OS_OPT_TIME_HMSM_STRICT, &err);
        LED_Toggle(LED3);
        OSTimeDlyHMSM(0, 0, 0, 300, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

void TaskMonitor(void *p_arg)
{
    OS_ERR err;
    while(1)
    { 
		MotorUpdate1(200,0,0,0);
		Test_Send();
        OSTimeDlyHMSM(0, 0, 0, 900, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}


/***********USART**********/
void TaskUSART(void *p_arg)
{
    OS_ERR err;
		while(1)
		{
			//ZY_VisualScope_Send(Motorpitch.PositionMeasure,Pitch_Position_Motor,(Motorleft.SpeedMeasure)/100,(Motorleft.SpeedMeasure)/100);	
			OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);
		}
}
 

