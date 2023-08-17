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
	Pin_Down(LED1_GPIO,LED1_Pin);
	Pin_Down(LED3_GPIO,LED3_Pin);
    while(1)
    {
		if(MainControlRun.TestMode != TEST_ON)
		{
			for(int8_t i = 0;i<MainControlRun.Attitude + 1;i++)
			{
				Pin_Up(LED2_GPIO,LED2_Pin);
				OSTimeDlyHMSM(0, 0, 0, 30, OS_OPT_TIME_HMSM_STRICT, &err);
				Pin_Down(LED2_GPIO,LED2_Pin);
				OSTimeDlyHMSM(0, 0, 0, 70, OS_OPT_TIME_HMSM_STRICT, &err);
			}
		}
		else
		{
			Pin_Up(LED2_GPIO,LED2_Pin);//blue	
		}

		if(MainControlRun.Heavy_Error != HEAVYSAFE)
		{
			for(int8_t i = 0;i<MainControlRun.Heavy_Error;i++)
			{
				Pin_Up(LED1_GPIO,LED1_Pin);
				OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_HMSM_STRICT, &err);
				Pin_Down(LED1_GPIO,LED1_Pin);
				OSTimeDlyHMSM(0, 0, 0, 80, OS_OPT_TIME_HMSM_STRICT, &err);
			}
		}
		
		if(MainControlRun.Soft_Error != SOFTSAFE)
		{
			for(int8_t i = 0;i<MainControlRun.Soft_Error;i++)
			{
				Pin_Up(LED3_GPIO,LED3_Pin);
				OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_HMSM_STRICT, &err);
				Pin_Down(LED3_GPIO,LED3_Pin);
				OSTimeDlyHMSM(0, 0, 0, 80, OS_OPT_TIME_HMSM_STRICT, &err);
			}
		}

		OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);	
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
					
			//Test_Send();
			UART_SendString(MY_USART4,"@ ");
			UART_SendString(MY_USART4,"Task_Num : ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MainControlRun.Task_Num);
			UART_SendString(MY_USART4,"\n");
			
			UART_SendString(MY_USART4,"@ ");
			UART_SendString(MY_USART4,"Attitude : ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MainControlRun.Attitude);
			UART_SendString(MY_USART4,"\n");
			
			UART_SendString(MY_USART4,"FrontLine : ");
			UART_SendNum_Short(MY_USART4,FrontLine);
			UART_SendString(MY_USART4,"\n");
			
			UART_SendString(MY_USART4,"FrontCount: ");
			UART_SendNum_Short(MY_USART4,FrontCount);
			UART_SendString(MY_USART4,"\n");
			
			UART_SendString(MY_USART4,"ARM_Position : ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MyCar.arm->PositionMeasure);
			UART_SendString(MY_USART4,"\n");
			
			UART_SendString(MY_USART4,"Arm_Pos : ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MyCar.arm->PositionMeasure);
			UART_SendString(MY_USART4,"\n");	

			UART_SendString(MY_USART4,"ERRORS: ");
			UART_SendNum_Short(MY_USART4,(uint32_t)MainControlRun.Soft_Error);
			UART_SendString(MY_USART4,"\t");
			UART_SendNum_Short(MY_USART4,(uint32_t)MainControlRun.Heavy_Error);
			UART_SendString(MY_USART4,"\n");
			
			UART_SendString(MY_USART4,"\n");
			UART_SendString(MY_USART4,"\n");
			OSTimeDlyHMSM(0, 0, 0,100, OS_OPT_TIME_HMSM_STRICT, &err);
		}
}
 

