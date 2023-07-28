#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"



RunningStruct MainControlRun = {AT_BRAKE,0};//记录智能车状态量

void TaskSensor (void *p_arg)//接收各个传感器的量，进行指标确定和状态识别
{
  	OS_ERR err;
	if(FrontLine > 0)
	{
	
	
	}else{
	
	
	}	
	
	
	OSTimeDlyHMSM(0, 0, 0, 3, OS_OPT_TIME_HMSM_STRICT, &err);
}


