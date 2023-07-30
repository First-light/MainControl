#include "system_config.h"
#include "task_init.h"

#define SIDE_BALANCE_P 0.433

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
}

void TaskMove(void *p_arg)//负责手动模式
{
  	OS_ERR err;
	if(MainControlRun.ManualMode == MANUAL_ON)
	{
		

		
	}



	OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
}