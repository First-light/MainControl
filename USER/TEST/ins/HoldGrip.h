#ifndef  _PASSINGHAND_H
#define  _PASSINGHAND_H

#include "stm32f4xx.h"
#include "includes.h"
#include "delay.h"
#include "motor_control.h"
//#include "com_prop.h"
#include "system_config.h"


#define AM_POSITION_RATIO 34.117647f//减速比
#define CHASSIS_UPPER_ANGLE 150.0f//底盘圆弧路径上限角度
#define ARC_GUIDE_ANGLE_HALF 27.61f//圆弧导轨的一半

typedef  enum
{
	H_INIT,
	H_PREPARE,
    PUSH,
    LOOSE,
    H_CHECK
}HoldState;//抓握状态


typedef struct
{
    volatile HoldState Hold_State;
    int cylinderinitflag;
}HoldGripController;

extern volatile HoldGripController HoldGrip_Controller;

void HoldGripControllerInit(void);
void HoldGripControllerRun(void);



#endif