#ifndef __TASK_INIT_H
#define __TASK_INIT_H
#include "includes.h"


/******************TASK PRIORITIES******************/
#define  TASK_START_PRIO                               2u
#define  TASK_HANDLE_PRIO                              5u 
//#define  TASK_REGULATE_PRIO                            10u
#define  TASK_MONITOR_PRIO                             20u
#define  TASK_INDICATE_PRIO                            22u
#define  TASK_USART_PRIO                               24u   //串口任务
#define  TASK_SENSOR_PRIO                          		3u


/******TASK STACK SIZES Size of the task stacks (# of OS_STK entries)*******/
#define  TASK_START_STK_SIZE                 512u
#define  TASK_MONITOR_STK_SIZE               512u
#define  TASK_INDICATE_STK_SIZE              512u
//#define  TASK_REGULATE_STK_SIZE              2048u
#define  TASK_USART_STK_SIZE                 2048u
#define  TASK_HANDLE_STK_SIZE                2048u
#define  TASK_SENSOR_STK_SIZE			 	2048u

/*任务申明*/
void TaskStart(void *p_arg);
void TaskMonitor(void *p_arg);
//void TaskRegulate(void *p_arg);
void TaskIndicate(void *p_arg);
void TaskUSART(void *p_arg);
void TaskHandle(void *p_arg);
void TaskSensor (void *p_arg);

/* ************************************ 宏定义 **************************************** */



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
} LineModeTypedef;

typedef enum{
	AT_BRAKE,
	AT_MANUAL,
	AT_MANUAL_SENSOR_MOVE,
	AT_AUTO_SENSOR_MOVE,//不接收红外信号，而是使用惯性传感器做一次运动
	AT_AUTO_START,
	AT_AUTO_FOLLOWLINE_SHORT,
	AT_AUTO_FOLLOWLINE_LONG,
	AT_AUTO_FINDPOINT,
	AT_AUTO_FINDCAN,
	AT_AUTO_CATCHCAN,
	AT_AUTO_FINDSTEP1,
	AT_AUTO_PUTCAN,
	AT_AUTO_BACKTOLINE,
	AT_AUTO_FINDSTEP2,
	AT_AUTO_TEST//测试模式，会同步开启自动程序，不过不会给电机和舵机还有夹爪使能
} AttitudeTypedef; //处于任何模式下传感器都在执行检测，不过不会进行运动合成和将结果输出到电机
//控制逻辑，传感器原始数据-》小车姿态信息-》小车运动合成-》电机运动
//每一步AUTO都有状态检测，达成指标则进行下一步，
//运动和传感计算分离出来写函数

typedef struct{
	AttitudeTypedef Attitude;
	uint8_t LineMode;
}RunningStruct;


#endif
 