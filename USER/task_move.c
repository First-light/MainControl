#include "system_config.h"
#include "task_init.h"
#include "motor_control.h"
#include "RobotCOM_proplist.h"

MoveStruct ManualExpected	= {0,0,0};//调整速度

MoveStruct AutoSpeedExpected 	= {0,0,0};//调整速度

const MoveStruct AutoBlank = {0,0,0};

MoveStruct AutoPositionExpected 	= {0,0,0};

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
	0.6,//左右
	1.0,//旋转
};

ThreeWheel_MoveParameter Auto_P = {
	1.0,//前后
	1.0,//左右
	1.0,//旋转
};

ThreeWheel_MoveDeliver MotorBalance = {
	1.0,
	1.0,
	1.0,
};

void Actions()
{
	if(ArmPos == POS_ON) 	MyCar.arm->PositionExpected = ARM_POS_PLUS ;//float	
	else 					MyCar.arm->PositionExpected = 0 ;
	
	Action_Send();
}

void SpeedDeliver(MoveStruct Expected,ThreeWheel_MoveParameter P)
{
	Forth.Left = Expected.Forth * P.Forth;
	Forth.Right = -Expected.Forth * P.Forth;
	Forth.Behind = 0.0;
	
	Side.Left = Expected.Side * Manual_P.Side;
	Side.Right = Expected.Side * Manual_P.Side;
	Side.Behind = -SIDE_BALANCE_P * Expected.Side * Manual_P.Side;
	
	Spin.Left = -Expected.Angle * Manual_P.Spin;
	Spin.Right = -Expected.Angle * Manual_P.Spin;
	Spin.Behind = -Expected.Angle * Manual_P.Spin;
	
	float LeftSpeed		=	Forth.Left 	+ 	Side.Left 	+ 	Spin.Left;
	float RightSpeed 	=	Forth.Right	+ 	Side.Right	+   Spin.Right;
	float BehindSpeed   =	Forth.Behind+	Side.Behind +   Spin.Behind;
	
	My3Moter.Motor_Left->State = PIDSPEED;
	My3Moter.Motor_Right->State = PIDSPEED;
	My3Moter.Motor_Behind->State = PIDSPEED;	

	My3Moter.Motor_Left->SpeedExpected = LeftSpeed * MotorBalance.Left;
	My3Moter.Motor_Right->SpeedExpected = RightSpeed * MotorBalance.Right;
	My3Moter.Motor_Behind->SpeedExpected = BehindSpeed * MotorBalance.Behind;
}

void PositionDeliver(MoveStruct Expected,ThreeWheel_MoveParameter P)
{
	Forth.Left = Expected.Forth * P.Forth;
	Forth.Right = -Expected.Forth * P.Forth;
	Forth.Behind = 0.0;
	
	Side.Left = Expected.Side * Manual_P.Side;
	Side.Right = Expected.Side * Manual_P.Side;
	Side.Behind = -SIDE_BALANCE_P * Expected.Side * Manual_P.Side;
	
	Spin.Left = -Expected.Angle * Manual_P.Spin;
	Spin.Right = -Expected.Angle * Manual_P.Spin;
	Spin.Behind = -Expected.Angle * Manual_P.Spin;
	
	float LeftSpeed		=	Forth.Left 	+ 	Side.Left 	+ 	Spin.Left;
	float RightSpeed 	=	Forth.Right	+ 	Side.Right	+   Spin.Right;
	float BehindSpeed   =	Forth.Behind+	Side.Behind +   Spin.Behind;
	
	My3Moter.Motor_Left->State = PIDPOSITION;
	My3Moter.Motor_Right->State = PIDPOSITION;
	My3Moter.Motor_Behind->State = PIDPOSITION;	

	My3Moter.Motor_Left->SpeedExpected = LeftSpeed * MotorBalance.Left;
	My3Moter.Motor_Right->SpeedExpected = RightSpeed * MotorBalance.Right;
	My3Moter.Motor_Behind->SpeedExpected = BehindSpeed * MotorBalance.Behind;
}

void TaskMoveAnalyse(void *p_arg)
{
  	OS_ERR err;
	
	My3Moter.Motor_Left->State = PIDSPEED;
	My3Moter.Motor_Right->State = PIDSPEED;
	My3Moter.Motor_Behind->State = PIDSPEED;
	My3Moter.Motor_Left->SpeedExpected = 0;
	My3Moter.Motor_Right->SpeedExpected = 0;
	My3Moter.Motor_Behind->SpeedExpected = 0;
	
	OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
	while(1)
	{
		MyCar.arm->State = PIDPOSITION;
		if(MainControlRun.ManualMode == MANUAL_ON)//负责手动模式
		{   
			SpeedDeliver(ManualExpected,Manual_P);	
			Actions();
		}
		else if(MainControlRun.Attitude == AT_AUTO_SENSOR_MOVE && MainControlRun.AutoMoveMode == MOVE_ON)
		{
			SpeedDeliver(AutoSpeedExpected,Auto_P);
		}  
		OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}