#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"


MoveStruct AutoMoveList[] ={
	{90,0,0},
	{100,0,0},
	{90,0,0},
	{0,10,0},
	{60,0,0},
};

AttitudeTypedef AutoTaskList[] ={
	AT_AUTO_TESTSTART,
	AT_AUTO_FOLLOWLINE_SHORT,
	AT_AUTO_FINDPOINT,
	AT_AUTO_SENSOR_MOVE,//左转90
	AT_AUTO_FINDCAN,
	AT_AUTO_CATCHCAN,
	AT_AUTO_BACKTOLINE,
	AT_AUTO_SENSOR_MOVE,//左转100
	AT_AUTO_FINDSTEP1,
	AT_AUTO_SENSOR_MOVE,//左转90
	AT_AUTO_PUTCAN,
	AT_AUTO_BACKTOLINE,
	AT_AUTO_SENSOR_MOVE,//前进10，
	AT_AUTO_SENSOR_MOVE,// 左转60
	AT_AUTO_FOLLOWLINE_SHORT,
	AT_MANUAL,
	AT_BRAKE,
};

void TaskTodoList (void *p_arg)
{
  	OS_ERR err;


	OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);
}

	