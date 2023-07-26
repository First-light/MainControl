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

/******TASK STACK SIZES Size of the task stacks (# of OS_STK entries)*******/
#define  TASK_START_STK_SIZE                 512u
#define  TASK_MONITOR_STK_SIZE               512u
#define  TASK_INDICATE_STK_SIZE              512u
//#define  TASK_REGULATE_STK_SIZE              2048u
#define  TASK_USART_STK_SIZE                 2048u
#define  TASK_HANDLE_STK_SIZE                2048u

/*任务申明*/
void TaskStart(void *p_arg);
void TaskMonitor(void *p_arg);
//void TaskRegulate(void *p_arg);
void TaskIndicate(void *p_arg);
void TaskUSART(void *p_arg);
void TaskHandle(void *p_arg);
#endif
 