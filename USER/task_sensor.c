#include "system_config.h"
#include "RobotCOM_proplist.h"

#include "task_init.h"


//master
RunningStruct MainControlRun = {AT_BRAKE,0};//

void TaskSensor (void *p_arg)//
{
  	OS_ERR err;
	if(FrontLine > 0)
	{
	
	
	}else{
	
	
	}	
	
	
	OSTimeDlyHMSM(0, 0, 0, 3, OS_OPT_TIME_HMSM_STRICT, &err);
}


