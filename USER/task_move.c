#include "system_config.h"
#include "task_init.h"

//定义左轮为motor1，右轮为motor2，后轮为motor3 ，顺时针为正？

MoveStruct ManualExpected;//调整速度
ThreeWheel_Classic My3Moter; 

void TaskMove(void *p_arg)//负责手动模式
{
  	OS_ERR err;
	if(MainControlRun.ManualMode == MANUAL_ON)
	{
		
	}



	OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
}