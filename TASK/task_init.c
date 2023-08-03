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
#include "task_init.h"


//extern float Yaw_PC_Angle;
//extern float Distance,Pitch_Position_Motor;
//extern volatile MotorTypeDef Motorleft, Motorright, Motorpitch;

void TaskIndicate(void *p_arg)
{
    OS_ERR err;
    while(1)
    {
		Pin_Up(LED2_GPIO,LED2_Pin);
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &err);
		Pin_Down(LED2_GPIO,LED2_Pin);
		OSTimeDlyHMSM(0, 0, 0, 450, OS_OPT_TIME_HMSM_STRICT, &err);	
	}
}

/*void TaskMonitor(void *p_arg)
{
    OS_ERR err;
    while(1)
    { 
    }
}
*/

/***********USART**********/
void TaskUSART(void *p_arg)
{
    OS_ERR err;
		while(1)
		{
					//MotorUpdate1(200,0,0,0);
			Test_Send();
			UART_SendString(MY_USART4,"FrontLine : ");
			UART_SendNum_Short(MY_USART4,FrontLine);
			UART_SendString(MY_USART4,"\n");
			UART_SendString(MY_USART4,"ARM_Position : ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MyCar.arm->PositionMeasure);
			UART_SendString(MY_USART4,"\n");
			UART_SendString(MY_USART4,"Task_Num : ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MainControlRun.Task_Num);
			UART_SendString(MY_USART4,"\n");
			OSTimeDlyHMSM(0, 0, 0,100, OS_OPT_TIME_HMSM_STRICT, &err);
		}
}
 

