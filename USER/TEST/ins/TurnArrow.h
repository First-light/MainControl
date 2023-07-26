#ifndef TURN_ARROW_H_
#define TURN_ARROW_H_

#include "VESC_CAN.h"
#include "motor_control.h"
#include "delay.h"
#include "hust_math_lib.h"
//#define TURN_ARROW_DEBUG_

#define YM_POSITION_PARA 6//餐盘减速比
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
    MotorTypeDef TurnYawMotor;//下面简写YM 偏航角电机
    MotorTypeDef TurnDisMotor;//下面简写DM 控制距离的电机
    
    float rotate_speed;//转箭速度
    
    float YM_InitPosition;
    float DM_InitPosition;
    
    float YM_PrePosition;//设置多个转箭位置 根据底盘位置确定
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