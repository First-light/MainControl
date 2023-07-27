#include "system_config.h" 
#include "includes.h"
#include "task_init.h"
#include "elmo.h"

/*  2023/7/26
����������
task_init.h ����task�� ���������������񿪱ٵĿռ䣬�������ȼ�
main.c ��������task�������Ľṹ�壬 ����CPU_STK����
task_xxx��c ����task������

��д�������ݴ���������
RobotCOMExecuteLIbc��д�����������壬д������ȫ�ֱ����Ķ��壬
��proplist-h��д�����������������ݵ�֡���Ժ꣬дexecute����õ��ĺ�
��proplist-c���������д���ڵ�֡�����ֵ䣬�Լ���Ӧ�Ĵ�������

��д�������ݷ��ͺ���
RobotCOMCommandlib��д���ͺ����Ķ��壬�����ԣ�д������ȫ�ֱ����Ķ��壬
��proplist-h��д���������������ԣ�дCommandlib����õ��ĺ�

�����µĴ���
��RobotCOMbasic��ά��Process_Frame_COM()��Get_Frame_COM() ��Send_Frame_COM()��{ע��#if��USARTnΪ�ܴ�����}�����´��ڵ�COMFrame ��COMRecStatus���壬��h������ȫ������
��COMproplist c����ֵ����飬��h������鶨��
��USART.h���޸�USARTn��д��BAUDRATE ��дUSART�ľ����ʼ���ĺ꣬дMyUSARTTypedef��ö�������������ջ�����ReceiveBuffer
��USART c��д���ջ��������鶨�壬����һ��ö�����������Ը�ע�ͣ�
��system config c�����Ӵ��ڵĳ�ʼ��
��stm32f4xx it c�������жϷ�����

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

int main(void)
{
    OS_ERR err;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    System_Init();
    delay_init();
    OSInit(&err);

    /*������ʼ����*/
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

    LED_On(RED_LED);
    LED_On(GREEN_LED);
    LED_On(BLUE_LED);
    MyDelayms(500);
    LED_Off(RED_LED);
    LED_Off(GREEN_LED);
    LED_Off(BLUE_LED);


	
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
                   
    OSTaskSuspend((OS_TCB *)&TaskStartTCB, (OS_ERR *) &err);  //������ʼ����    
	OS_CRITICAL_EXIT();							 
}



void assert_failed(uint8_t* file, uint32_t line)
{
	
}