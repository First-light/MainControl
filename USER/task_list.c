#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"
#include <stdio.h>

//小车状态信息结构体
RunningStruct MainControlRun = 
{
	AT_BRAKE,
	LINE_CC,
	TEST_ON,
	MANUAL_OFF,
	0,
	MOVE_OFF
};

#define CIRCLE_ON 1
#define CIRCLE_OFF 0


MoveStruct AutoMoveList[] ={ //单位为度和毫米
	{500,0,0},
	{90,0,0},
	{100,0,0},
	{90,0,0},
	{0,10,0},
	{60,0,0},
};

AttitudeTypedef AutoTaskList[] ={
	AT_BRAKE,
	AT_MANUAL,
	//AT_AUTO_TESTSTART,
	//AT_AUTO_FOLLOWLINE_SHORT,
	//AT_AUTO_FINDPOINT,
	AT_AUTO_SENSOR_MOVE,//左转90
	//AT_AUTO_FINDCAN,
	//AT_AUTO_CATCHCAN,
	//AT_AUTO_BACKTOLINE,
	//AT_AUTO_SENSOR_MOVE,//左转100
	//AT_AUTO_FINDSTEP1,
	//AT_AUTO_SENSOR_MOVE,//左转90
	//AT_AUTO_PUTCAN,
	//AT_AUTO_BACKTOLINE,
	//AT_AUTO_SENSOR_MOVE,//前进10，
	//AT_AUTO_SENSOR_MOVE,// 左转60
	//AT_AUTO_FOLLOWLINE_SHORT,
	AT_MANUAL,
};

uint32_t AutoMoveTime = 0;
float AutoAngle_P = 13.5;
float AutoForth_P = 4.9;
float AutoSide_P = 1.0;

uint8_t TaskTarget(AttitudeTypedef task)
{
	uint8_t circle = CIRCLE_ON;
	switch (task)
	{
		case AT_MANUAL:
			if(MainControlRun.ManualMode == MANUAL_OFF)circle = CIRCLE_OFF;
			break;
		case AT_MANUAL_TEST:
			if(MainControlRun.ManualMode == MANUAL_OFF)circle = CIRCLE_OFF;
			break;
		default:circle = CIRCLE_OFF;
	}		
	return circle;
}



void TaskTodoList(void *p_arg)
{
  	OS_ERR err;
	
	AttitudeTypedef* list;
	list = AutoTaskList;
	uint8_t TodoListCount = sizeof(list)/sizeof(list[0]);
	MoveStruct* NowMove = &AutoMoveList[0];
	uint8_t TodoListNum = 0;

	while(TodoListNum < TodoListCount && list != 0)
	{
		MainControlRun.Task_Num = TodoListNum;
		MainControlRun.Attitude = list[TodoListNum];
		switch (list[TodoListNum])
		{
			case AT_MANUAL:
				MainControlRun.TestMode = TEST_OFF;
				MainControlRun.ManualMode = MANUAL_ON;
				while(TaskTarget(list[TodoListNum]))
					OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &err);				
				break;
			case AT_MANUAL_TEST:
				MainControlRun.TestMode = TEST_ON;
				MainControlRun.ManualMode = MANUAL_ON;
				while(TaskTarget(list[TodoListNum]))
					OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &err);
				break;
			case AT_AUTO_SENSOR_MOVE:
				if(NowMove != 0)
				{
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					MainControlRun.AutoMoveMode = MOVE_ON;
					AutoSpeedExpected = AutoBlank;//清零
					int32_t F = (int32_t)(NowMove->Forth 	* 	AutoForth_P);
					int32_t S = (int32_t)(NowMove->Side 	* 	AutoSide_P);
					int32_t A = (int32_t)(NowMove->Angle 	* 	AutoAngle_P);
			
					if(A){
					AutoSpeedExpected.Angle = AUTOSPEED * (A/abs(A));//确定正反转
					OSTimeDlyHMSM(0, 0, 0,A, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					AutoSpeedExpected = AutoBlank;//清零
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					}
					if(F){
					AutoSpeedExpected.Forth = AUTOSPEED * (F/abs(F));
					OSTimeDlyHMSM(0, 0, 0,F, OS_OPT_TIME_HMSM_NON_STRICT, &err);
					AutoSpeedExpected = AutoBlank;//清零
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					}
					if(S){
					AutoSpeedExpected.Side = AUTOSPEED * (S/abs(S));
					OSTimeDlyHMSM(0, 0, 0,S, OS_OPT_TIME_HMSM_NON_STRICT, &err);
					AutoSpeedExpected = AutoBlank;//清零
					}
					MainControlRun.AutoMoveMode = MOVE_OFF;
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					NowMove++;
				}
				else
				{
					
				}
				break;
			default :
				break;
		}		
		TodoListNum++;
	}
	
	while(true)
	{
		Task_Over_Send();
		MainControlRun.TestMode = TEST_ON;
		OSTimeDlyHMSM(0, 0, 0,999, OS_OPT_TIME_HMSM_STRICT, &err);
	}
	
}



	