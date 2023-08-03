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
#define MOTOR_ARM       Motor1
#define MOTOR_LEFT      Motor2
#define MOTOR_RIGHT     Motor3
#define MOTOR_BEHIND 	Motor4

#define SIDE_BALANCE_P 0.433
#define SPEEDLIMIT_MAX 400.0

/* ************************************ 声明  **************************************** */

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
	AT_AUTO_SENSOR_MOVE,//不接收红外信号，而是使用惯性传感器做一次运动
	AT_AUTO_START,
	AT_AUTO_FOLLOWLINE_SHORT,//巡线固定的一段时间，然后完成任务
	AT_AUTO_FOLLOWLINE_LONG,
	AT_AUTO_FINDPOINT,
	AT_AUTO_FINDCAN,
	AT_AUTO_CATCHCAN,
	AT_AUTO_FINDSTEP1,
	AT_AUTO_PUTCAN,
	AT_AUTO_BACKTOLINE,
	AT_AUTO_FINDSTEP2,
	AT_AUTO_TESTSTART//测试模式，会同步开启自动程序，不过不会给电机和舵机还有夹爪使能
} AttitudeTypedef; //处于任何模式下传感器都在执行检测，不过不会进行运动合成和将结果输出到电机
//控制逻辑，传感器原始数据-》小车姿态信息-》小车运动合成-》电机运动
//每一步AUTO都有状态检测，达成指标则进行下一步，
//运动和传感计算分离出来写函数

typedef enum{
	MANUAL_OFF,
	MANUAL_ON,
}ManualTypedef;

typedef enum {
	ROD_PULL,
	ROD_PUSH,
}RodTypedef;//推杆

typedef struct{
	AttitudeTypedef 	Attitude;
	LineModeTypedef 	LineMode;
	TestTypedef 		TestMode;
	ManualTypedef 		ManualMode;
	uint8_t             Task_Num;
}RunningStruct;

 typedef struct {
	int32_t Forth;//前后，前为正，单位毫米
	int32_t Side;//左右，右为正
	int32_t Angle;//旋转的角度°逆时针为正,左转为正
}MoveStruct;//自动移动函数先执行旋转，再执行左右，再执行前后

 typedef struct {
	MotorTypeDef* Motor_Left;
	MotorTypeDef* Motor_Right;
	MotorTypeDef* Motor_Behind;
}ThreeWheel_Classic;//数据接收
 
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
	ThreeWheel_Classic* classic;
	MotorTypeDef* 		arm;
	RodTypedef*			rod;	
}Wheel3_Degree1_Clamp_SmartCar;


extern RunningStruct 					MainControlRun;
extern Wheel3_Degree1_Clamp_SmartCar 	MyCar;
extern ThreeWheel_Classic 				My3Moter;
extern RodTypedef 						GasPushRod;
extern MoveStruct 						ManualExpected;//调整速度
extern MoveStruct 						AutoExpected;//调整速度

#endif
 