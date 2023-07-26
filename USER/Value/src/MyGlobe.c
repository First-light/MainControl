#include "MyGlobe.h"

/*******************************************************************************
															系统状态量
*******************************************************************************/
//volatile TestMotorTypeDef LaunchMotor;//elmo ec30

uint32_t CAN_feedDog =0; //CAN总线喂狗，防止主控跑飞

void GlobeVariableInit(void)
{
//	MOTOR_INVERSE_DIR=0;
//	Motor.State=PIDSPEED;

    //测试架初始化参数
//    LaunchMotor.Motor_Super = &Motor;
   //LaunchMotor.teststate = MOTOR_IDLE;
	 
//    LaunchMotor.Kick_Speed = 30;//rpm
//    LaunchMotor.Origin_Position = 0;
//    LaunchMotor.Armed_Position = 0;//
//    LaunchMotor.Kick_Position = 0;
//    LaunchMotor.Armed_Position = 0;
}


