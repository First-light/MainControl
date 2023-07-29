#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"

//小车状态信息结构体
RunningStruct MainControlRun = 
{AT_BRAKE,LINE_CC,TEST_ON,MANUAL_OFF};

MoveStruct AutoMoveList[] ={
	{90,0,0},
	{100,0,0},
	{90,0,0},
	{0,10,0},
	{60,0,0},
};

AttitudeTypedef AutoTaskList[] ={
	AT_MANUAL,
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
};



void TaskTodoList (void *p_arg)
{
  	OS_ERR err;
	AttitudeTypedef* list;
	list = AutoTaskList;
	uint8_t TodoListCount = sizeof(list)/sizeof(list[0]);
	uint8_t TodoListNum = 0;

	while(TodoListNum < TodoListCount && list != 0)
	{
		MainControlRun.Attitude = list[TodoListNum];
		switch (list[TodoListNum])
		{
			case AT_MANUAL:
				MainControlRun.TestMode = TEST_OFF;
				MainControlRun.ManualMode = MANUAL_ON;
				while(MainControlRun.ManualMode == MANUAL_ON)
				OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &err);
				break;
			case AT_MANUAL_TEST:
				MainControlRun.TestMode = TEST_ON;
				MainControlRun.ManualMode = MANUAL_ON;
				while(MainControlRun.ManualMode == MANUAL_ON)
				OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &err);
				break;
			default :
				continue;
		}		
		TodoListNum++;
	}
	while(true)
	{
		Task_Over_Send();
		OSTimeDlyHMSM(0, 0, 0,999, OS_OPT_TIME_HMSM_STRICT, &err);
	}
	OSTimeDlyHMSM(0, 0, 0, 999, OS_OPT_TIME_HMSM_STRICT, &err);
}



	