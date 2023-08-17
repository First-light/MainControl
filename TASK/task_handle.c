#include "system_config.h"
#include "RobotCAN_Proplist.h"
#include "MyGlobe.h"
//#include "com_prop.h"
#include "motor_control.h"
#include "task_init.h"

bool StateSwitch = 0;
RobotCtrl_t RobotCtrl;

void SpeedLimit()
{
	if(
	Motor1.SpeedExpected > SPEEDLIMIT ||
	Motor2.SpeedExpected > SPEEDLIMIT ||
	Motor3.SpeedExpected > SPEEDLIMIT ||
	Motor4.SpeedExpected > SPEEDLIMIT ||
	Motor5.SpeedExpected > SPEEDLIMIT ||
	Motor6.SpeedExpected > SPEEDLIMIT ||
	Motor7.SpeedExpected > SPEEDLIMIT ||
	Motor8.SpeedExpected > SPEEDLIMIT )
	{
		MainControlRun.Soft_Error = ERROR_SPEEDLIMIT; //超速
		while(
		Motor1.SpeedExpected > SPEEDLIMIT ||
		Motor2.SpeedExpected > SPEEDLIMIT ||
		Motor3.SpeedExpected > SPEEDLIMIT ||
		Motor4.SpeedExpected > SPEEDLIMIT ||
		Motor5.SpeedExpected > SPEEDLIMIT ||
		Motor6.SpeedExpected > SPEEDLIMIT ||
		Motor7.SpeedExpected > SPEEDLIMIT ||
		Motor8.SpeedExpected > SPEEDLIMIT )
		{
			Motor1.SpeedExpected *= 0.9; 
			Motor2.SpeedExpected *= 0.9;
			Motor3.SpeedExpected *= 0.9;
			Motor4.SpeedExpected *= 0.9;
			Motor5.SpeedExpected *= 0.9;
			Motor6.SpeedExpected *= 0.9;
			Motor7.SpeedExpected *= 0.9;
			Motor8.SpeedExpected *= 0.9;			
		}
	}
	else
	{
		MainControlRun.Soft_Error = SOFTSAFE; 
	}
}

void TaskHandle(void *p_arg)
{
  	OS_ERR err;
  	uint8_t count;	
  	while (1) {
	
			SpeedLimit();

		 	switch(Motor1.State)
			{
					case PIDPOSITION:				
						Motor1.SpeedExpected =  ClassicPidRegulate(Motor1.PositionExpected,Motor1.PositionMeasure,&MotorPositionPid1);

					case PIDSPEED:						
						Motor1.CurrentExpected = ClassicPidRegulate(Motor1.SpeedExpected,Motor1.SpeedMeasure,&MotorSpeedPid1);
					
					case MOTOR_CURRENT: 					 
						Motor1.PWM = ClassicPidRegulate(Motor1.CurrentExpected,Motor1.CurrentMeasure,&MotorCurrentPid1);
						break; 
					case MOTOR_PWM:	
						
						break;
					
					default:
						Motor1.PWM = 0;
						break;		
			}
			
			switch(Motor2.State)
			{
					case PIDPOSITION:
						Motor2.SpeedExpected =  ClassicPidRegulate(Motor2.PositionExpected,Motor2.PositionMeasure,&MotorPositionPid2);
						/*
						if(Motor2.PositionExpected>200)
						{							
							Motor2.SpeedExpected =  ClassicPidRegulate(Motor2.PositionExpected,Motor2.PositionMeasure,&MotorPositionPid2b);
						}
						else if(Motor2.PositionExpected>=10)
						{
							Motor2.SpeedExpected =  ClassicPidRegulate(Motor2.PositionExpected,Motor2.PositionMeasure,&MotorPositionPid2);
						}
						else if(Motor2.PositionExpected<10&&Motor2.PositionExpected>-5)
						{
							Motor2.SpeedExpected =  ClassicPidRegulate(Motor2.PositionExpected,Motor2.PositionMeasure,&MotorPositionPid2r);
						}
						else if(Motor2.PositionExpected<-10)
						{
							Motor2.SpeedExpected =  ClassicPidRegulate(Motor2.PositionExpected,Motor2.PositionMeasure,&MotorPositionPid2t);
						}
						*/
				
					case PIDSPEED:						
					
						Motor2.CurrentExpected = ClassicPidRegulate(Motor2.SpeedExpected,Motor2.SpeedMeasure,&MotorSpeedPid2);
					
					case MOTOR_CURRENT:			  
						Motor2.PWM = ClassicPidRegulate(Motor2.CurrentExpected,Motor2.CurrentMeasure,&MotorCurrentPid2);
						
						break;

					case MOTOR_PWM:	
						
						break;
					
					default:
						Motor2.PWM = 0;
						break;
					
			}
			
			
			switch(Motor3.State)
			{
					case PIDPOSITION:
						Motor3.SpeedExpected =  ClassicPidRegulate(Motor3.PositionExpected,Motor3.PositionMeasure,&MotorPositionPid3);
				
					case PIDSPEED:						
					
						Motor3.CurrentExpected = ClassicPidRegulate(Motor3.SpeedExpected,Motor3.SpeedMeasure,&MotorSpeedPid3);
					
					case MOTOR_CURRENT:			  
						Motor3.PWM = ClassicPidRegulate(Motor3.CurrentExpected,Motor3.CurrentMeasure,&MotorCurrentPid3);
						break;
					case MOTOR_PWM:	
						break;
					
					default:
						Motor3.PWM = 0;
						break;
					
			}
			switch(Motor4.State)
			{
					case PIDPOSITION:
							Motor4.SpeedExpected =  ClassicPidRegulate(Motor4.PositionExpected,Motor4.PositionMeasure,&MotorPositionPid4);			
				
					case PIDSPEED:						
					
						Motor4.CurrentExpected = ClassicPidRegulate(Motor4.SpeedExpected,Motor4.SpeedMeasure,&MotorSpeedPid4);
					
					case MOTOR_CURRENT:			  
						Motor4.PWM = ClassicPidRegulate(Motor4.CurrentExpected,Motor4.CurrentMeasure,&MotorCurrentPid4);		
						break;
					case MOTOR_PWM:	
						break;		
					default:
						Motor4.PWM = 0;
						break;
					
			}
			switch(Motor5.State)
			{
					case PIDPOSITION:
						Motor5.SpeedExpected =  ClassicPidRegulate(Motor5.PositionExpected,Motor5.PositionMeasure,&MotorPositionPid5);

				
					case PIDSPEED:						
					
						Motor5.CurrentExpected = ClassicPidRegulate(Motor5.SpeedExpected,Motor5.SpeedMeasure,&MotorSpeedPid5);
					
					case MOTOR_CURRENT:			  
						Motor5.PWM = ClassicPidRegulate(Motor5.CurrentExpected,Motor5.CurrentMeasure,&MotorCurrentPid5);
						
						break;
					case MOTOR_PWM:	
						break;
					
					default:
						Motor5.PWM = 0;
						break;
					
			}
			switch(Motor6.State)
			{
				
					case PIDPOSITION:
						Motor6.SpeedExpected =  ClassicPidRegulate(Motor6.PositionExpected,Motor6.PositionMeasure,&MotorPositionPid6);
					case PIDSPEED:							
						Motor6.CurrentExpected = ClassicPidRegulate(Motor6.SpeedExpected,Motor6.SpeedMeasure,&MotorSpeedPid6);
					case MOTOR_CURRENT:			  
						Motor6.PWM = ClassicPidRegulate(Motor6.CurrentExpected,Motor6.CurrentMeasure,&MotorCurrentPid6);
						break;
					
					case MOTOR_PWM:	
						
						break;
					default:
						Motor6.PWM = 0;
						break;
					
			}
			switch(Motor7.State)
			{
					case PIDPOSITION:
					
						Motor7.SpeedExpected =  ClassicPidRegulate(Motor7.PositionExpected,Motor7.PositionMeasure,&MotorPositionPid7);
				
					case PIDSPEED:						
					
						Motor7.CurrentExpected = ClassicPidRegulate(Motor7.SpeedExpected,Motor7.SpeedMeasure,&MotorSpeedPid7);
					
					case MOTOR_CURRENT:			  
						Motor7.PWM = ClassicPidRegulate(Motor7.CurrentExpected,Motor7.CurrentMeasure,&MotorCurrentPid7);
						
					  break;
					case MOTOR_PWM:	
						break;
					
					default:
						Motor7.PWM = 0;
						break;
					
			}
			switch(Motor8.State)
			{
				case PIDPOSITION:
					
						Motor8.SpeedExpected =  ClassicPidRegulate(Motor8.PositionExpected,Motor8.PositionMeasure,&MotorPositionPid8);
				
				case PIDSPEED:						
					
						Motor8.CurrentExpected = ClassicPidRegulate(Motor8.SpeedExpected,Motor8.SpeedMeasure,&MotorSpeedPid8);
					
		    	case MOTOR_CURRENT:			  
						Motor8.PWM = ClassicPidRegulate(Motor8.CurrentExpected,Motor8.CurrentMeasure,&MotorCurrentPid8);
						
					  break;
				case MOTOR_PWM:	
						break;
					
				default:
					Motor8.PWM = 0;
						break;
					
			}
			

			
			if(MainControlRun.TestMode == TEST_OFF)
			{
				MotorUpdate(Motor1.PWM,Motor2.PWM,Motor3.PWM,Motor4.PWM);
				MotorUpdate1(Motor5.PWM,Motor6.PWM,Motor7.PWM,Motor8.PWM);
			}
			else
			{
				MotorUpdate(0,0,0,0);
				MotorUpdate1(0,0,0,0);			
			}//如果开启测试模式，电调不输出电流

    	OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
  	} 
}

