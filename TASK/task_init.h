#ifndef __TASK_INIT_H
#define __TASK_INIT_H
#include "includes.h"


/******************TASK PRIORITIES******************/
#define  TASK_START_PRIO                               2u
#define  TASK_HANDLE_PRIO                              22u 
//#define  TASK_REGULATE_PRIO                          10u
//#define  TASK_MONITOR_PRIO                             32u
#define  TASK_INDICATE_PRIO                            42u
#define  TASK_USART_PRIO                               3u   //��������
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

/*��������*/
void TaskStart(void *p_arg);
//void TaskMonitor(void *p_arg);
//void TaskRegulate(void *p_arg);
void TaskIndicate(void *p_arg);
void TaskUSART(void *p_arg);
void TaskHandle(void *p_arg);
void TaskSensor (void *p_arg);
void TaskTodoList(void *p_arg);
void TaskMoveAnalyse(void *p_arg);
/* ************************************ �궨�� **************************************** */
//��������Ϊmotor2������Ϊmotor3������Ϊmotor4 ��˳ʱ��Ϊ����
//�����ֱ۵��Ϊmotor1
#define MOTOR_ARM       Motor1
#define MOTOR_LEFT      Motor4
#define MOTOR_RIGHT     Motor2
#define MOTOR_BEHIND 	Motor3

#define ARM_POS_PLUS      364.0


#define SIDE_BALANCE_P 		2.0
#define SPEEDLIMIT 			200.0
#define AUTOSPEED  		    50.0

/* ************************************ ����  **************************************** */

typedef enum {
	ROD_PULL,
	ROD_PUSH,
}RodTypedef;//�Ƹ�

typedef enum {
	POS_OFF,
	POS_ON,
}PosTypedef;

typedef enum{
	LINE_FB_O,//ǰ��������
	LINE_FB_S,//ǰ��ͬ�����
	LINE_F,//ǰ�����
	LINE_B,//������
	LINE_CC,//ֱ��
	LINE_FX,//ǰ�ඪ��
	LINE_BX,//��ඪ��
	LINE_XX,//˫�ඪ��
	//������Ӧֻ����ҪѲ�ߵ���������ڣ���Ӧ��ʵ�ǵ��������ƫ��ֵ
} LineModeTypedef;

typedef enum{
	TEST_OFF,
	TEST_ON,//����ģʽ��ʱ���������pid���㵫�ǲ����pwm
} TestTypedef;

typedef enum{
	AT_BRAKE,
	AT_MANUAL,
	AT_MANUAL_SENSOR_MOVE,
	AT_MANUAL_TEST,
	AT_AUTO_SENSOR_MOVE,//�����պ����źţ�����ʹ�ù��Դ�������һ���˶�
	AT_AUTO_START,
	AT_AUTO_FOLLOWLINE_SHORT,//Ѳ�߹̶���һ��ʱ�䣬Ȼ���������
	AT_AUTO_FOLLOWLINE_LONG,
	AT_AUTO_FINDPOINT,
	AT_AUTO_FINDCAN,
	AT_AUTO_CATCHCAN,
	AT_AUTO_FINDSTEP1,
	AT_AUTO_PUTCAN,
	AT_AUTO_BACKTOLINE,
	AT_AUTO_FINDSTEP2,
	AT_AUTO_TESTSTART//����ģʽ����ͬ�������Զ����򣬲������������Ͷ�����м�צʹ��
} AttitudeTypedef; //�����κ�ģʽ�´���������ִ�м�⣬������������˶��ϳɺͽ������������
//�����߼���������ԭʼ����-��С����̬��Ϣ-��С���˶��ϳ�-������˶�
//ÿһ��AUTO����״̬��⣬���ָ���������һ����
//�˶��ʹ��м���������д����

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
}SoftErrorTypedef;

typedef enum{
	HEAVYSAFE,
	ERROR_TOO_FAST,
}HeavyErrorTypedef;

typedef struct{
	AttitudeTypedef 	Attitude;
	LineModeTypedef 	LineMode;
	TestTypedef 		TestMode;
	ManualTypedef 		ManualMode;
	uint8_t             Task_Num;
	AutoMoveTypedef     AutoMoveMode;
	SoftErrorTypedef    Soft_Error;
	HeavyErrorTypedef	Heavy_Error;
}RunningStruct;

 typedef struct {
	float Forth;//ǰ��ǰΪ������λ����
	float Side;//���ң���Ϊ��
	float Angle;//��ת�ĽǶȡ���ʱ��Ϊ��,��תΪ��
}MoveStruct;//�Զ��ƶ�������ִ����ת����ִ�����ң���ִ��ǰ��

 typedef struct {
	MotorTypeDef* Motor_Left;
	MotorTypeDef* Motor_Right;
	MotorTypeDef* Motor_Behind;
}W3Classic;//���ݽ���
 
typedef struct{
	float Left;
	float Right;
	float Behind;
}ThreeWheel_MoveDeliver;//���ֳ����ٶȷֽ�ṹ��

typedef struct{
	float 	Forth;
	float	Side;
	float 	Spin;
}ThreeWheel_MoveParameter;//���ֳ����ٶȷֽ�ṹ��

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
extern MoveStruct 						ManualExpected;//�����ٶ�
extern MoveStruct 						AutoSpeedExpected;//�����ٶ�
extern const MoveStruct 				AutoBlank;
extern MoveStruct 						AutoPositionExpected;
#endif
 