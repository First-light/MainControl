#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "VESC_CAN.h"


#define Motor_1_ID	0x201 
#define Motor_2_ID	0x202 
#define Motor_3_ID	0x203 
#define Motor_4_ID	0x204
#define Motor_5_ID	0x205 
#define Motor_6_ID	0x206
#define Motor_7_ID	0x207 
#define Motor_8_ID	0x208 

typedef  enum
{
	IDLE,
	PIDSPEED,
	PIDPOSITION,
	MOTOR_ERROR,
	MOTOR_PWM,   //PWM ����ģʽ
	MOTOR_CURRENT,
}DriverState;//ϵͳ״̬

typedef struct 
{
	float PositionExpected;
	float PositionMeasure;
	float SpeedExpected;
	float SpeedMeasure;

	short PosPre;
	short PosNow;
	float CurrentExpected;
	float CurrentMeasure;
	
	int32_t 	PWM;
  DriverState    State;	
}MotorTypeDef;

typedef struct 
{
	float helm_angle;
	float helm_speed;//>0
	float wheel_speed;
	float position_loop_range;
	int8_t dir;
}DifferenceTypeDef;

/***PID�����ṹ***/
typedef  struct 
{
	float Kp;
	float Ki;
	float Kd;
	float LimitOutput;  //  Limit for Output limitation
	float LimitIntegral; //Lower Limit for Integral term limitation
	float Integral; //������,�洢��������KI
	float PreError;

}ClassicPidStructTypedef;

typedef  enum
{
	DISABLE1,
	BRAKE,
	ADVANCE,
	RETREAT,
	ROTATE,
	CONTRAROTATE,
	RIGHTTURN,
	LEFTTURN,
}MonotrochState;//���ֳ�״̬


/*********PID*******/
extern ClassicPidStructTypedef MotorPositionPid1,MotorSpeedPid1,MotorCurrentPid1;
extern ClassicPidStructTypedef MotorPositionPid2b,MotorPositionPid2,MotorPositionPid2r,MotorPositionPid2t,MotorSpeedPid2,MotorCurrentPid2;
extern ClassicPidStructTypedef MotorPositionPid3,MotorPositionPid3r,MotorSpeedPid3,MotorCurrentPid3;
extern ClassicPidStructTypedef MotorPositionPid4,MotorPositionPid4r,MotorSpeedPid4,MotorCurrentPid4;
extern ClassicPidStructTypedef MotorPositionPid5,MotorPositionPid5r,MotorSpeedPid5,MotorCurrentPid5;
extern ClassicPidStructTypedef MotorPositionPid6,MotorPositionPid6r,MotorSpeedPid6,MotorCurrentPid6;
extern ClassicPidStructTypedef MotorPositionPid7,MotorSpeedPid7,MotorCurrentPid7;
extern ClassicPidStructTypedef MotorPositionPid8,MotorSpeedPid8,MotorCurrentPid8;

extern volatile MotorTypeDef  Motor1,Motor2,Motor3,Motor4,Motor5,Motor6,Motor7,Motor8;
extern volatile MotorTypeDef  motorring;
extern volatile MotorTypeDef  frictionright,frictionleft,rotationmotor;
extern volatile float HELMSpeed_Limit;
extern volatile float WHEELSpeed_Limit;
extern DifferenceTypeDef Diff1;

extern volatile MonotrochState monotroch_state, pre_state;

void  PidInit(void);
float ClassicPidRegulate(float Reference, float PresentFeedback,ClassicPidStructTypedef *PidStruct);
void MotorUpdate(short I1, short I2,short I3,short I4);
void MotorUpdate1(short I1, short I2,short I3,short I4);
float utils_angle_difference(float angle1, float angle2);
void Difference1MotorSend(DifferenceTypeDef *Diffx);//���Ͷ�ǣ����ı������ٶ�
void Difference1SpeedSend(DifferenceTypeDef *Diffx);//���Ͷ��٣����ı������ٶ�

void Motor_Position_Update(float Motor1_position,float Motor2_position,float Motor3_position,float Motor4_position,float Motor5_position,float Motor6_position,float Motor7_position,float Motor8_position);

#endif
