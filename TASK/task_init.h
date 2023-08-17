#ifndef __TASK_INIT_H
#define __TASK_INIT_H
#include "includes.h"


/******************TASK PRIORITIES******************/
#define  TASK_START_PRIO                               2u
#define  TASK_HANDLE_PRIO                              22u 
//#define  TASK_REGULATE_PRIO                          10u
//#define  TASK_MONITOR_PRIO                             32u
#define  TASK_INDICATE_PRIO                            42u
#define  TASK_USART_PRIO                               3u   //串口任务
#define  TASK_SENSOR_PRIO                          	   7u
#define	 TASK_TODOLIST_PRIO                            5u
#define	 TASK_MOVEANALYSE_PRIO                         21u

/******TASK STACK SIZES Size of the task stacks (# of OS_STK entries)*******/
#define  TASK_START_STK_SIZE                 1024u
//#define  TASK_MONITOR_STK_SIZE             256u
#define  TASK_INDICATE_STK_SIZE              1024u
//#define  TASK_REGULATE_STK_SIZE            2048u
#define  TASK_USART_STK_SIZE                 1024u
#define  TASK_HANDLE_STK_SIZE                2048u
#define  TASK_SENSOR_STK_SIZE				 2048u
#define  TASK_TODOLIST_STK_SIZE            	 2048u
#define  TASK_MOVEANALYSE_STK_SIZE           2048u

/*任务申明*/
void TaskStart(void *p_arg);
//void TaskMonitor(void *p_arg);
//void TaskRegulate(void *p_arg);
void TaskIndicate(void *p_arg);
void TaskUSART(void *p_arg);
void TaskHandle(void *p_arg);
void TaskSensor (void *p_arg);
void TaskTodoList(void *p_arg);
void TaskMoveAnalyse(void *p_arg);
/* ************************************ 宏定义 **************************************** */
//定义左轮为motor2，右轮为motor3，后轮为motor4 ，顺时针为正？
//定义手臂电机为motor1
#define MOTOR_ARM       	Motor1
#define MOTOR_LEFT      	Motor4
#define MOTOR_RIGHT     	Motor2
#define MOTOR_BEHIND 		Motor3

#define ARM_POS_PLUS      	364.0

#define SIDE_BALANCE_P 		2.0

#define SPEEDLIMIT 			200.0

#define AUTOLINESPEED       80.0
#define AUTOSPEED  		    50.0
#define AUTOFASTSPEED  		100.0
#define MAX_LOSTLINE_TIME	1000

#define POINTCOUNT          6
#define MAXLINE             10000.0

/* ************************************ 声明  **************************************** */

typedef enum {
	ROD_PULL,
	ROD_PUSH,
}RodTypedef;//推杆

typedef enum {
	POS_OFF,
	POS_ON,
}PosTypedef;

typedef enum{
	LINE_FB_O,//前后异侧出线
	LINE_FB_S,//前后同侧出线
	LINE_F,//前侧出线
	LINE_B,//后侧出线
	LINE_CC,//直行
	LINE_FX,//前侧丢线
	LINE_BX,//后侧丢线
	LINE_XX,//双侧丢线
	//丢线响应只在需要巡线的任务里存在，响应其实是调整输入的偏差值
} LineModeTypedef;

typedef enum{
	TEST_OFF,
	TEST_ON,//测试模式打开时，电机进行pid计算但是不输出pwm
} TestTypedef;

typedef enum{
	AT_BRAKE,
	AT_MANUAL,
	AT_MANUAL_SENSOR_MOVE,
	AT_MANUAL_TEST,
	AT_AUTO_SLOW_MOVE,//不接收红外信号，做一次运动
	AT_AUTO_FAST_MOVE,
	AT_AUTO_FOLLOWLINE,//巡线一段时间
	AT_AUTO_FINDPOINT,//一边巡线一边找交点，找到交点就停
	AT_AUTO_REBASE,
	AT_AUTO_ARM_UP,
	AT_AUTO_ARM_DOWN,
	AT_AUTO_HAND_OPEN,
	AT_AUTO_HAND_CLOSE,
	AT_AUTO_TEST//测试模式，会同步开启自动程序，不过不会给电机和舵机还有夹爪使能
} AttitudeTypedef; //处于任何模式下传感器都在执行检测，不过不会进行运动合成和将结果输出到电机
//控制逻辑，传感器原始数据-》小车姿态信息-》小车运动合成-》电机运动
//每一步AUTO都有状态检测，达成指标则进行下一步，
//运动和传感计算分离出来写函数

typedef enum{
	UNUSE_LINE,
	USE_LINE,
}AutoLineTypedef;

typedef enum{
	MANUAL_OFF,
	MANUAL_ON,
}ManualTypedef;

typedef enum{
	MOVE_OFF,
	MOVE_ON,
}AutoMoveTypedef;

typedef enum{
	SOFTSAFE,
	ERROR_EMPTY_MOVELIST,
	ERROR_SPEEDLIMIT,
	ERROR_BLUESTOP,
}SoftErrorTypedef;

typedef enum{
	HEAVYSAFE,
	ERROR_TOO_FAST,
	ERROR_LOSTLINE,
}HeavyErrorTypedef;

typedef struct{
	AttitudeTypedef 	Attitude;
	LineModeTypedef 	LineMode;
	TestTypedef 		TestMode;
	ManualTypedef 		ManualMode;
	uint8_t             Task_Num;
	AutoMoveTypedef     AutoMoveMode;
	AutoLineTypedef     AutoLineMode;
	SoftErrorTypedef    Soft_Error;
	HeavyErrorTypedef	Heavy_Error;
}RunningStruct;

 typedef struct {
	float Forth;//前后，前为正，单位毫米
	float Side;//左右，右为正
	float Angle;//旋转的角度°逆时针为正,左转为正
}MoveStruct;//自动移动函数先执行旋转，再执行左右，再执行前后

 typedef struct {
	MotorTypeDef* Motor_Left;
	MotorTypeDef* Motor_Right;
	MotorTypeDef* Motor_Behind;
}W3Classic;//数据接收
 
typedef struct{
	float Left;
	float Right;
	float Behind;
}ThreeWheel_MoveDeliver;//三轮车的速度分解结构体

typedef struct{
	float 	Forth;
	float	Side;
	float 	Spin;
}ThreeWheel_MoveParameter;//三轮车的速度分解结构体

typedef struct wheel3_degree1_clamp_smartcar
{
	W3Classic* classic;
	MotorTypeDef* 		arm;
	RodTypedef*			rod;	
}W3D1ClampCar;


extern RunningStruct 					MainControlRun;
extern W3D1ClampCar 					MyCar;
extern W3Classic 						My3Moter;
extern RodTypedef 						GasPushRod;
extern PosTypedef 						ArmPos;
extern MoveStruct 						ManualExpected;//调整速度
extern MoveStruct 						AutoSpeedExpected;//调整速度
extern const MoveStruct 				AutoBlank;
extern MoveStruct 						AutoPositionExpected;
#endif
 