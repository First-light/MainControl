#ifndef __ELMO
#define __ELMO
#include "stm32f4xx.h"
#include "RobotCAN_Proplist.h"
#include "RobotCAN_Basic.h"
#include "RobotCAN_IDconf.h"

#define	COB_NMT				0
#define	COB_SYNC			1
#define	COB_TIME_STAMP		2
#define	COB_EMERGENCY		1
#define	COB_TPDO1			3
#define	COB_RPDO1			4
#define	COB_TPDO2			5
#define	COB_RPDO2			6
#define	COB_TPDO3			7
#define	COB_RPDO3			8
#define	COB_TPDO4			9
#define	COB_RPDO4			10
#define	COB_TSDO			11
#define	COB_RSDO			12
#define	COB_ERROR_CONTROL	14

#define SPEED_PARA	(2000.0f/60.0f*3249.0f/169.0f)//    2000/60
#define POSITION_PARA  (2000.0f/360.0f*182.0f/20.0f*3249.0f/169.0f)  //  2000*182/90
#define DECELERATION_PARA   256.0f//

#define	LaunchMotor_DIR		1

//#define POSITIONLOOP_MAXSPEED 10000

#define	BUILD_COB(COB_ID,DEV_ID)	(COB_ID<<7 | DEV_ID)

typedef union
{
	uint32_t	all;
	struct
	{
		uint32_t DeviceId		:7;
		uint32_t COB_ID		:4;
	}ID;
}STD_ID_Typedef;

void ProcessElmoFrame(Frame* Frame_Process);
void StopTPDO(uint8_t TPDONum, uint8_t DevId, CAN_TypeDef* CANx);
void Set_Yaw_EC22_VCT_FeedBack(uint8_t TPDONum, uint8_t DevId);
void Set_Yaw_EC22_PCT_FeedBack(uint8_t TPDONum, uint8_t DevId);
void SetEventTimer(uint8_t TPDONum, uint8_t DevId, uint8_t Time, CAN_TypeDef* CANx);
void ActivateTPDO(uint8_t TPDONum, uint8_t DevId, CAN_TypeDef* CANx);
void NMT_StartNode(CAN_TypeDef* CANx);
void MotorOn(CAN_TypeDef* CANx);
void MotorOff(CAN_TypeDef* CANx);
void Change_To_PositionMode(void);
void Change_To_VelocityMode(void);
void Set_Yaw_EC22_MotorSpeed(int32_t Speed, int32_t DevId);
void Yaw_EC22_SpeedUpdate(float Speed1);

void Set_Yaw_EC22_MotorPosition(int32_t Position, int32_t MaxSpeed, int32_t DevId);
void Yaw_EC22_PositionUpdate(float Position1,int32_t MaxSpeed);

void SetLaunchMotorDeceleration(int32_t Position1, int32_t MaxSpeed1, int32_t Decel, int32_t DevId);

void ElmoInit(void);
void Yaw_EC22_MotorInit(int32_t DevId);


#endif