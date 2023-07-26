#ifndef ROBOTCAN_IDCONF_H_
#define ROBOTCAN_IDCONF_H_

#include "stm32f4xx_can.h"
#include "RobotCAN_device.h"

#define DEVICE_ID    CHASSIS_MOTOR2_ID   //1号电机注意换向
#define BROADCAST_ID CHASSIS_BROADCAST

//#define SLAVER_DEVICE
#define DEVICE_SECOND_ID  BROADCAST_ID 

#define	FILTER_ID														DEVICE_ID
#define FILTER_SECOND_ID                    DEVICE_SECOND_ID

#endif /*ROBOT_CAN_CONF_H_*/

