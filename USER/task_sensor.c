#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"



void TaskSensor (void *p_arg)//
{
  	OS_ERR err;
	//Ñ²Ïß×´Ì¬
	if((FrontLine > 0 && BehindLine < 0)||(FrontLine < 0 && BehindLine > 0))
	{MainControlRun.LineMode = LINE_FB_O;}
	else if((FrontLine > 0 && BehindLine > 0)||(FrontLine < 0 && BehindLine < 0))
	{MainControlRun.LineMode = LINE_FB_S;}
	else if((FrontLine != 0 && BehindLine == 0))
	{MainControlRun.LineMode = LINE_F;}
	else if((FrontLine == 0 && BehindLine != 0))
	{MainControlRun.LineMode = LINE_B;}
	else if((FrontLine == 0 && BehindLine == 0))
	{MainControlRun.LineMode = LINE_CC;}
	//¶ªÏß×´Ì¬	
	if(FrontCount == 0 && BehindCount == 0)
	{MainControlRun.LineMode = LINE_XX;}
	else if(FrontCount == 0)
	{MainControlRun.LineMode = LINE_FX;}
	else if(BehindCount == 0) 
	{MainControlRun.LineMode = LINE_BX;}
	
	
	OSTimeDlyHMSM(0, 0, 0, 3, OS_OPT_TIME_HMSM_STRICT, &err);
}


