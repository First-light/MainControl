#ifndef __MY_TYPE_H
#define __MY_TYPE_H
#include "stm32f4xx.h"
#include "motor_control.h"

#define WHEELS_NUM 3

//#define JOINT_RUNNING_
/*******************************************************************************
															系统结构体定义
*******************************************************************************/



typedef struct {
  float X;
  float Y;
  float Alpha;
  float theta;
  float Vx_robot;
  float Vy_robot;
  float Vx_global;
  float Vy_global;
  float w;
  float wheel_rpm[3];
  float helm_angle[3];
} ChassisStateTypedef;

typedef enum {
  WAITTING,
  STALL,
  PARKING,
  LOCKED,
  NAVIGATE,
  NAVIGATE_PRE,
  CHASSIS_DISABLE,
  ON_LINE,
  MANUAL
} ChassisModeTypedef;

typedef struct {
  ChassisStateTypedef CurrentState;
  ChassisStateTypedef AimState;
  ChassisModeTypedef Mode;
  float OriginX, OriginY, OriginAlpha;
  float x_diviation, y_diviation;
  uint8_t NavigatePathNum;
} ChassisInfoTypedef;

extern ChassisInfoTypedef ChassisInfo;



typedef struct
{
  uint16_t Parking : 1;
  uint16_t Navigate : 1;
  uint16_t ChassisStop : 1;
  uint16_t ChassisDisable : 1;
  uint16_t RobotReStart : 1;
  uint16_t Manual : 1;
	uint16_t one : 1;
  uint16_t two : 1;
  uint16_t three : 1;
  uint16_t four : 1;
  uint16_t five : 1;
  uint16_t six : 1;
}ChassisCtrl_t;

typedef struct
{
//	MachineCtrl_t UpCtrl;
//	MachineCtrl_t DownCtrl;
	ChassisCtrl_t ChassisCtrl;
}RobotCtrl_t;

extern int preMotorFlag[3];
extern int motorFlag[3];



//typedef struct 
//{
//    volatile MotorTypeDef* Motor_Super;//电机结构体
//    TestMotorState teststate;
//    int32_t Origin_Position;
//    int32_t Armed_Position;
//    int32_t Kick_Position;
//    int32_t Kick_Speed;
//}TestMotorTypeDef;

#endif
