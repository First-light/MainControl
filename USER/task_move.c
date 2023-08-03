#include "system_config.h"
#include "task_init.h"

#define SIDE_BALANCE_P 0.433
#define SPEEDLIMIT_MAX 400.0

//定义左轮为motor1，右轮为motor2，后轮为motor3 ，顺时针为正？
MoveStruct ManualExpected;//调整速度

ThreeWheel_Classic My3Moter;

ThreeWheel_MoveDeliver Forth; //前后
ThreeWheel_MoveDeliver Side;//左右
ThreeWheel_MoveDeliver Spin;//旋转



ThreeWheel_MoveParameter Manual_P = {
	2.0,//前后
	1.0,//左右
	1.0,//旋转
};

void ManualMoveDeliver(MoveStruct Expected)
{
	Forth.Left = -Expected.Forth * Manual_P.Forth;
	Forth.Right = Expected.Forth * Manual_P.Forth;
	Forth.Behind = 0.0;
	
	Side.Left = Expected.Side * Manual_P.Side;
	Side.Right = Expected.Side * Manual_P.Side;
	Side.Behind = -SIDE_BALANCE_P * Manual_P.Side;
	
	Spin.Left = -Expected.Angle * Manual_P.Spin;
	Spin.Right = -Expected.Angle * Manual_P.Spin;
	Spin.Behind = -Expected.Angle * Manual_P.Spin;
	
	float LeftSpeed		=	Forth.Left 	+ 	Side.Left 	+ 	Spin.Left;
	float RightSpeed 	=	Forth.Right	+ 	Side.Right	+   Spin.Right;
	float BehindSpeed   =	Forth.Behind+	Side.Behind +   Spin.Behind;
	
	My3Moter.Motor_Left->State = PIDSPEED;
	My3Moter.Motor_Right->State = PIDSPEED;
	My3Moter.Motor_Behind->State = PIDSPEED;
	
	My3Moter.Motor_Left->SpeedExpected = LeftSpeed;
	My3Moter.Motor_Right->SpeedExpected = RightSpeed;
	My3Moter.Motor_Behind->SpeedExpected = BehindSpeed;
}

void TaskMoveAnalyse(void *p_arg)
{
  	OS_ERR err;
	while(1){
		if(MainControlRun.ManualMode == MANUAL_ON)//负责手动模式
		{
			ManualMoveDeliver(ManualExpected);	
		}
		else if(0)
		{
			
		}
		OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}