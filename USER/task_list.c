#include "system_config.h"
#include "RobotCOM_proplist.h"
#include "task_init.h"
#include <stdio.h>

//小车状态信息结构体
RunningStruct MainControlRun = 
{
	AT_BRAKE,
	LINE_CC,
	TEST_OFF,
	MANUAL_OFF,
	0,
	MOVE_OFF,
	UNUSE_LINE,
	SOFTSAFE,
	HEAVYSAFE
};

#define CIRCLE_ON 1
#define CIRCLE_OFF 0

uint32_t AutoMoveTime = 0;

float AutoAngle_P = 13.5;
float AutoForth_P = 4.9;
float AutoSide_P = 1.0;

float AutoFastAngle_P = 13.5;
float AutoFastForth_P = 4.9;
float AutoFastSide_P = 1.0;

MoveStruct AutoSlowMoveList[] ={ //单位为度和毫米
	{500,0,0},
	{0,0,90},
	{760,0,0},
	{0,0,110},
	
	{70,0,110},
	{0,0,90},
	{-190,0,0},
	{190,0,0},
	{0,0,90},
	
	{0,0,-90},
	{760,0,0},
	{0,0,-110},
	
	{70,0,0},
	{0,0,-90},
	{-190,0,0},
	{190,0,0},
	{0,0,-90},
};


MoveStruct AutoFastMoveList[] ={ //单位为度和毫米
	{1200,0,0},
	{1200,0,0},
	{1200,0,0},
};

uint32_t AutoLineTimeList[] ={ //单位为毫秒
	300,
	500,
	500,
	300
};

AttitudeTypedef AutoTaskList[] ={
	AT_BRAKE,
	AT_MANUAL,
	AT_AUTO_SLOW_MOVE,//500出发
	AT_AUTO_FINDPOINT,
	AT_AUTO_SLOW_MOVE,//+90
	AT_AUTO_HAND_OPEN,
	AT_AUTO_SLOW_MOVE,//760
	AT_AUTO_HAND_CLOSE,
	AT_AUTO_SLOW_MOVE,//+110
	AT_AUTO_FAST_MOVE,//1200
	AT_AUTO_FINDPOINT,
	AT_AUTO_FOLLOWLINE,//300ms	
	AT_AUTO_FINDPOINT,
	AT_AUTO_SLOW_MOVE,//qian70
	AT_AUTO_SLOW_MOVE,//+90
	AT_AUTO_SLOW_MOVE,//退190
	AT_AUTO_ARM_UP,
	AT_AUTO_HAND_OPEN,
	AT_AUTO_SLOW_MOVE,//qian190
	AT_AUTO_ARM_DOWN,
	AT_AUTO_HAND_CLOSE,
	AT_AUTO_SLOW_MOVE,//+90
	AT_AUTO_FOLLOWLINE,//巡线半秒
	AT_AUTO_FAST_MOVE,//1200
	AT_AUTO_FOLLOWLINE,//一次巡线多少秒看数组
	AT_AUTO_FINDPOINT,
	AT_AUTO_SLOW_MOVE,//-90
	AT_AUTO_HAND_OPEN,
	AT_AUTO_SLOW_MOVE,//760
	AT_AUTO_HAND_CLOSE,
	AT_AUTO_SLOW_MOVE,//-110
	AT_AUTO_FAST_MOVE,//1200
	AT_AUTO_FINDPOINT,
	AT_AUTO_FOLLOWLINE,//300ms
	AT_AUTO_FINDPOINT,
	AT_AUTO_SLOW_MOVE,//qian70
	AT_AUTO_SLOW_MOVE,//-90
	AT_AUTO_SLOW_MOVE,//退190
	AT_AUTO_ARM_UP,
	AT_AUTO_HAND_OPEN,	
	AT_AUTO_SLOW_MOVE,//qian190
	AT_AUTO_ARM_DOWN,
	AT_AUTO_HAND_CLOSE,
	AT_AUTO_SLOW_MOVE,//-90
	AT_MANUAL,
};

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
		case AT_AUTO_FINDPOINT:
			if(FrontCount >= POINTCOUNT)circle = CIRCLE_OFF;
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
	uint8_t TodoListCount = sizeof(AutoTaskList)/sizeof(AutoTaskList[0]);
	MoveStruct* SlowMove = &AutoSlowMoveList[0];
	MoveStruct* FastMove = &AutoFastMoveList[0];
	uint32_t* 	LineTime = &AutoLineTimeList[0];
	uint8_t TodoListNum = 0;

	while(TodoListNum < TodoListCount && list != 0)
	{
		MainControlRun.Task_Num = TodoListNum;
		MainControlRun.Attitude = list[TodoListNum];
		switch (list[TodoListNum])
		{
			case AT_MANUAL:
				MainControlRun.ManualMode = MANUAL_ON;
				while(TaskTarget(list[TodoListNum]))
					OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);				
				break;
			case AT_MANUAL_TEST:
				MainControlRun.ManualMode = MANUAL_ON;
				while(TaskTarget(list[TodoListNum]))
					OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);
				break;
			case AT_AUTO_SLOW_MOVE:
				if(SlowMove != 0)
				{
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					MainControlRun.AutoMoveMode = MOVE_ON;
					AutoSpeedExpected = AutoBlank;//清零
					int32_t F = (int32_t)(SlowMove->Forth 	* 	AutoForth_P);
					int32_t S = (int32_t)(SlowMove->Side 	* 	AutoSide_P);
					int32_t A = (int32_t)(SlowMove->Angle 	* 	AutoAngle_P);
			
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
					SlowMove++;
				}
				break;
		case AT_AUTO_FAST_MOVE:
				if(FastMove != 0)
				{
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					MainControlRun.AutoMoveMode = MOVE_ON;
					AutoSpeedExpected = AutoBlank;//清零
					int32_t F = (int32_t)(FastMove->Forth 	* 	AutoFastForth_P);
					int32_t S = (int32_t)(FastMove->Side 	* 	AutoFastSide_P);
					int32_t A = (int32_t)(FastMove->Angle 	* 	AutoFastAngle_P);	
					
					if(A){
					AutoSpeedExpected.Angle = AUTOFASTSPEED * (A/abs(A));//确定正反转
					OSTimeDlyHMSM(0, 0, 0,A, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					AutoSpeedExpected = AutoBlank;//清零
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					}
					
					if(F){
					AutoSpeedExpected.Forth = AUTOFASTSPEED * (F/abs(F));
					OSTimeDlyHMSM(0, 0, 0,F, OS_OPT_TIME_HMSM_NON_STRICT, &err);
					AutoSpeedExpected = AutoBlank;//清零
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					}
					
					if(S){
					AutoSpeedExpected.Side = AUTOFASTSPEED * (S/abs(S));
					OSTimeDlyHMSM(0, 0, 0,S, OS_OPT_TIME_HMSM_NON_STRICT, &err);
					AutoSpeedExpected = AutoBlank;//清零
					}
					
					MainControlRun.AutoMoveMode = MOVE_OFF;
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					FastMove++;
				}
				break;
		case AT_AUTO_FOLLOWLINE:
				if(LineTime != 0)
				{
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					MainControlRun.AutoMoveMode = MOVE_ON;
					MainControlRun.AutoLineMode = USE_LINE;
					OSTimeDlyHMSM(0, 0, 0,*LineTime, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					MainControlRun.AutoMoveMode = MOVE_OFF;
					MainControlRun.AutoLineMode = UNUSE_LINE;
					OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
					LineTime++;
				}
				break;
		case AT_AUTO_FINDPOINT:
			OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			MainControlRun.AutoMoveMode = MOVE_ON;
			MainControlRun.AutoLineMode = USE_LINE;
		
			while(TaskTarget(list[TodoListNum]))
			OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
					
			MainControlRun.AutoMoveMode = MOVE_OFF;
			MainControlRun.AutoLineMode = UNUSE_LINE;
			OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			break;
		case AT_AUTO_ARM_UP:
			MainControlRun.AutoMoveMode = MOVE_ON;
			ArmPos = POS_ON;
			OSTimeDlyHMSM(0, 0, 0,1000, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			MainControlRun.AutoMoveMode = MOVE_OFF;
			OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			break;
		case AT_AUTO_ARM_DOWN:
			MainControlRun.AutoMoveMode = MOVE_ON;
			ArmPos = POS_OFF;
			OSTimeDlyHMSM(0, 0, 0,1000, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			MainControlRun.AutoMoveMode = MOVE_OFF;
			OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			break;
		case AT_AUTO_HAND_OPEN:
			MainControlRun.AutoMoveMode = MOVE_ON;
			GasPushRod = ROD_PUSH;
			OSTimeDlyHMSM(0, 0, 0,100, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			MainControlRun.AutoMoveMode = MOVE_OFF;
			OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			break;
		case AT_AUTO_HAND_CLOSE:
			MainControlRun.AutoMoveMode = MOVE_ON;
			GasPushRod = ROD_PULL;
			OSTimeDlyHMSM(0, 0, 0,100, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
			MainControlRun.AutoMoveMode = MOVE_OFF;
			OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_NON_STRICT, &err); //延时ms
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



	