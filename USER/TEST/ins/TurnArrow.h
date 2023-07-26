#ifndef TURN_ARROW_H_
#define TURN_ARROW_H_

#include "VESC_CAN.h"
#include "motor_control.h"
#include "delay.h"
#include "hust_math_lib.h"
//#define TURN_ARROW_DEBUG_

#define YM_POSITION_PARA 6//���̼��ٱ�
#define DELTA_DISTANCE       112
#define ARROW_LENGTH         285

extern volatile bool isStart;
extern volatile bool isStop;
typedef enum
{
    PREINIT,
    INIT,
    PREPARE,
    STOP,
    T_CHECK
}TurnState;

typedef struct
{
    MotorTypeDef TurnYawMotor;//�����дYM ƫ���ǵ��
    MotorTypeDef TurnDisMotor;//�����дDM ���ƾ���ĵ��
    
    float rotate_speed;//ת���ٶ�
    
    float YM_InitPosition;
    float DM_InitPosition;
    
    float YM_PrePosition;//���ö��ת��λ�� ���ݵ���λ��ȷ��
    float DM_PrePosition;
    
    volatile int goal_x;
    volatile int goal_y;
    
    volatile int goal_point;
    
    float YM_RealPosition;

   volatile TurnState Turn_State;
}TurnArrowController;

extern volatile TurnArrowController TurnArrow_Controller;

void TurnArrowControllerInit(void);
void TurnArrowControllerRun(void);

#endif