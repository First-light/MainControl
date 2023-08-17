#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"

float SideNeed 	= 0.0;
float ForthNeed	= 0.0;
float AngleNeed	= 0.0;

float SideNeed_History;
float ForthNeed_History;
float AngleNeed_History;

float SideP		=	1.0;
float ForthP	=	1.0;//调节偏移量大小与速度大小的参数
float AngleP	=	0.5;

uint32_t LostLineTime = 0; //ms

void TaskSensor (void *p_arg)//
{
  	OS_ERR err;
	while(1)
	{
		if(MainControlRun.AutoLineMode == USE_LINE)
		{
			SideNeed 	=	 AUTOLINESPEED * ((float)FrontLine / MAXLINE) * SideP;
			AngleNeed   =	-AUTOLINESPEED * ((float)FrontLine / MAXLINE) * AngleP;
			ForthNeed   =	 AUTOLINESPEED * (MAXLINE - abs(FrontLine) * ForthP/ MAXLINE);	
			
			if(FrontCount == 0 || BehindCount == 0)
			{
				AutoSpeedExpected.Angle = AngleNeed_History * 1.5;
				AutoSpeedExpected.Forth = AUTOLINESPEED / 2.0;
				AutoSpeedExpected.Side  = SideNeed_History  * 1.5;	
				LostLineTime++;
				if(LostLineTime > MAX_LOSTLINE_TIME)
				{
					MainControlRun.Heavy_Error  = ERROR_LOSTLINE;
					MainControlRun.AutoLineMode = UNUSE_LINE;
					MainControlRun.TestMode     = TEST_ON;
				}
			}
			else
			{	
				SideNeed_History 	= SideNeed;
				ForthNeed_History	= ForthNeed;
				AngleNeed_History	= AngleNeed;	
				
				AutoSpeedExpected.Angle = AngleNeed;
				AutoSpeedExpected.Forth = ForthNeed;
				AutoSpeedExpected.Side  = SideNeed;	
				LostLineTime = 0;				
			}	
		}
		else
		{
			SideNeed 	= 0.0;
			ForthNeed	= 0.0;
			AngleNeed	= 0.0;		
			SideNeed_History 	= 0.0;
			ForthNeed_History	= 0.0;
			AngleNeed_History	= 0.0;		
		}	
		
		if(
		Motor1.SpeedMeasure > SPEEDLIMIT ||
		Motor2.SpeedMeasure > SPEEDLIMIT ||
		Motor3.SpeedMeasure > SPEEDLIMIT ||
		Motor4.SpeedMeasure > SPEEDLIMIT ||
		Motor5.SpeedMeasure > SPEEDLIMIT ||
		Motor6.SpeedMeasure > SPEEDLIMIT ||
		Motor7.SpeedMeasure > SPEEDLIMIT ||
		Motor8.SpeedMeasure > SPEEDLIMIT )
		{
			MainControlRun.TestMode = TEST_ON ;
			MainControlRun.Heavy_Error = ERROR_TOO_FAST; //超速
		}
		
	OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}


