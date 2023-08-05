#include "system_config.h"
#include "task_init.h"
#include "motor_control.h"
#include "RobotCOM_proplist.h"

MoveStruct ManualExpected	= {0,0,0};//调整速度
MoveStruct AutoExpected 	= {0,0,0};//调整速度

RodTypedef GasPushRod = ROD_PULL;

PosTypedef ArmPos = POS_OFF;

W3Classic My3Moter = {
	(MotorTypeDef*)&MOTOR_LEFT,
	(MotorTypeDef*)&MOTOR_RIGHT,
	(MotorTypeDef*)&MOTOR_BEHIND	
};

W3D1ClampCar MyCar = {
	&My3Moter,
	(MotorTypeDef*)&MOTOR_ARM,
	&GasPushRod
};

ThreeWheel_MoveDeliver Forth; //前后
ThreeWheel_MoveDeliver Side;//左右
ThreeWheel_MoveDeliver Spin;//旋转

ThreeWheel_MoveParameter Manual_P = {
	2.0,//前后
	1.0,//左右
	1.0,//旋转
};

void Actions()
{
	if(ArmPos == POS_ON) 	MyCar.arm->PositionExpected = ARM_POS_UP;//float	
	else 					MyCar.arm->PositionExpected = ARM_POS_DOWN;
	
	Action_Send();
}

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
	while(1)
	{
		if(MainControlRun.ManualMode == MANUAL_ON)//负责手动模式
		{   
			ManualMoveDeliver(ManualExpected);	
			Actions();
			
		}
		else if(0)
		{
			
		}  
		OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}