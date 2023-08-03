#include "system_config.h" 
#include "includes.h"
#include "task_init.h"
#include "elmo.h"

/*  2023/7/31 整理者：徐哲轩

创建新任务：
task_init.h 添加task的 任务函数声明，任务开辟的空间，任务优先级
main.c 声明添加task设置量的结构体， 声明CPU_STK数组
task_xxx，c 添加task任务函数

编写串口数据处理函数：
RobotCOMExecuteLIbc里写处理函数定义，写函数里全局变量的定义，
在proplist-h里写函数声明，定义数据的帧属性宏，写execute里会用到的宏
在proplist-c里的数组里写串口的帧属性字典，以及对应的处理函数

编写串口数据发送函数
RobotCOMCommandlib里写发送函数的定义，（可以）写函数里全局变量的定义，
在proplist-h里写函数声明，（可以）写Commandlib里会用到的宏

创建新的串口
在RobotCOMbasic，维护Process_Frame_COM()，Get_Frame_COM() ，Send_Frame_COM()，{注意#if里USARTn为总串口数}创建新串口的COMFrame 和COMRecStatus定义，在h里添加全局声明
在COMproplist c里加字典数组，在h里加数组定义
在USART.h里修改USARTn，写宏BAUDRATE ，写USART的具体初始化的宏，写MyUSARTTypedef的枚举量，声明接收缓存区ReceiveBuffer
在USART c里写接收缓存区数组定义，添加一堆枚举量，（可以改注释）
在system config c里添加串口的初始化
在stm32f4xx it c里添加中断服务函数

创建任务：
main.c在TaskStart（）函数按格式创建任务，
main.c定义任务OS_TCB（信息结构体）CPU_STK开辟任务空间
task_init.h宏定义任务优先级，任务开辟空间，声明任务函数 （可以声明全局变量）
task_init.c编写任务函数，定义全局变量
（建议）task_xxx.c编写较大任务函数，然后在init.h里声明函数

*/

static  OS_TCB   TaskStartTCB;
static  CPU_STK  TaskStartStk[TASK_START_STK_SIZE];

static  OS_TCB   TaskMonitorTCB;
static  CPU_STK  TaskMonitorStk[TASK_MONITOR_STK_SIZE];

/*
static  OS_TCB   TaskRegualteTCB;
static  CPU_STK  TaskRegulateStk[TASK_REGULATE_STK_SIZE];
*/

static  OS_TCB   TaskIndicateTCB;
static  CPU_STK  TaskIndicateStk[TASK_INDICATE_STK_SIZE];

static  OS_TCB   TaskUSARTTCB;
static  CPU_STK  TaskUSARTStk[TASK_USART_STK_SIZE];

static  OS_TCB   TaskHandleTCB;
static  CPU_STK  TaskHandleStk[TASK_HANDLE_STK_SIZE];

static  OS_TCB   TaskSensorTCB;
static  CPU_STK  TaskSensorStk[TASK_MONITOR_STK_SIZE];

static  OS_TCB   TaskMoveAnalyseTCB;
static  CPU_STK  TaskMoveAnalyseStk[TASK_MOVEANALYSE_STK_SIZE];

void LED_Show(void);

int main(void)
{
    OS_ERR err;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    System_Init();
    delay_init();
    OSInit(&err);

	
    /*创建起始任务*/
    OSTaskCreate ((OS_TCB       *)&TaskStartTCB,
                  (CPU_CHAR     *)"Task Start",
                  (OS_TASK_PTR   )TaskStart,
                  (void         *)0,
                  (OS_PRIO       )TASK_START_PRIO,
                  (CPU_STK      *)&TaskStartStk[0],
                  (CPU_STK_SIZE  )TASK_START_STK_SIZE / 10,
                  (CPU_STK_SIZE  )TASK_START_STK_SIZE,
                  (OS_MSG_QTY    )0,
                  (OS_TICK       )0,
                  (void         *)0,
                  (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                  (OS_ERR       *)&err);
    OSStart(&err);
    (void)&err;
}
void TaskStart(void *p_arg)
{
    OS_ERR err;
    CPU_SR cpu_sr = 0;
    p_arg = p_arg;
    CPU_Init();    // Initialize the uC/CPU services
    Mem_Init();    // Initialize Memory Management Module
    Math_Init();
   // ElmoInit();
	LED_Show();
	
	OS_CRITICAL_ENTER();
    OSTaskCreate  ((OS_TCB       *)&TaskMonitorTCB,
                   (CPU_CHAR     *)"Monitor Task",
                   (OS_TASK_PTR   )TaskMonitor,
                   (void         *)0,
                   (OS_PRIO       )TASK_MONITOR_PRIO,
                   (CPU_STK      *)&TaskMonitorStk[0],
                   (CPU_STK_SIZE  )TASK_MONITOR_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_MONITOR_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
    
    OSTaskCreate  ((OS_TCB       *)&TaskIndicateTCB,
                   (CPU_CHAR     *)"Indicate Task",
                   (OS_TASK_PTR   )TaskIndicate,
                   (void         *)0,
                   (OS_PRIO       )TASK_INDICATE_PRIO,
                   (CPU_STK      *)&TaskIndicateStk[0],
                   (CPU_STK_SIZE  )TASK_INDICATE_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_INDICATE_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
									 
    OSTaskCreate  ((OS_TCB       *)&TaskHandleTCB,
                    (CPU_CHAR     *)"Handle Task",
                    (OS_TASK_PTR   )TaskHandle,
                    (void         *)0,
                    (OS_PRIO       )TASK_HANDLE_PRIO,
                    (CPU_STK      *)&TaskHandleStk[0],
                    (CPU_STK_SIZE  )TASK_HANDLE_STK_SIZE / 10,
                    (CPU_STK_SIZE  )TASK_HANDLE_STK_SIZE,
                    (OS_MSG_QTY    )0,
                    (OS_TICK       )0,
                    (void         *)0,
                    (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                    (OS_ERR       *)&err);
 /*                   
	OSTaskCreate  ((OS_TCB       *)&TaskRegualteTCB,
                   (CPU_CHAR     *)"Regulate Task",
                   (OS_TASK_PTR   )TaskRegulate,
                   (void         *)0,
                   (OS_PRIO       )TASK_REGULATE_PRIO,
                   (CPU_STK      *)&TaskRegulateStk[0],
                   (CPU_STK_SIZE  )TASK_REGULATE_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_REGULATE_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
*/
    OSTaskCreate  ((OS_TCB       *)&TaskUSARTTCB,
                   (CPU_CHAR     *)"USART Task",
                   (OS_TASK_PTR   )TaskUSART,
                   (void         *)0,
                   (OS_PRIO       )TASK_USART_PRIO,
                   (CPU_STK      *)&TaskUSARTStk[0],
                   (CPU_STK_SIZE  )TASK_USART_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_USART_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);

    OSTaskCreate  ((OS_TCB       *)&TaskSensorTCB,
                   (CPU_CHAR     *)"Sensor Task",
                   (OS_TASK_PTR   )TaskSensor,
                   (void         *)0,
                   (OS_PRIO       )TASK_SENSOR_PRIO,
                   (CPU_STK      *)&TaskSensorStk[0],
                   (CPU_STK_SIZE  )TASK_SENSOR_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_SENSOR_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
	/*			   
    OSTaskCreate  ((OS_TCB       *)&TaskTodoListTCB,
                   (CPU_CHAR     *)"TodoList Task",
                   (OS_TASK_PTR   )TaskTodoList,
                   (void         *)0,
                   (OS_PRIO       )TASK_TODOLIST_PRIO,
                   (CPU_STK      *)&TaskTodoListStk[0],
                   (CPU_STK_SIZE  )TASK_TODOLIST_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_TODOLIST_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
    *//*     
    OSTaskCreate  ((OS_TCB       *)&TaskMoveAnalyseTCB,
                   (CPU_CHAR     *)"MoveAnalyse Task",
                   (OS_TASK_PTR   )TaskMoveAnalyse,
                   (void         *)0,
                   (OS_PRIO       )TASK_MOVEANALYSE_PRIO,
                   (CPU_STK      *)&TaskMoveAnalyseStk[0],
                   (CPU_STK_SIZE  )TASK_MOVEANALYSE_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_MOVEANALYSE_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);  */
				   
    OSTaskSuspend((OS_TCB *)&TaskStartTCB, (OS_ERR *) &err);  //挂起起始任务    
	OS_CRITICAL_EXIT();							 
}



void assert_failed(uint8_t* file, uint32_t line)
{
	
}

void LED_Show(void)
{
	for(int i = 0;i<3;i++)
	{	
 	Pin_Up(LED2_GPIO,LED2_Pin);
	Pin_Up(LED1_GPIO,LED1_Pin);
	Pin_Up(LED3_GPIO,LED3_Pin);
    MyDelayms(50);
 	Pin_Down(LED2_GPIO,LED2_Pin);
	Pin_Down(LED1_GPIO,LED1_Pin);
	Pin_Down(LED3_GPIO,LED3_Pin);
	MyDelayms(80);
	}
	MyDelayms(300);
}