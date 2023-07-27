#ifndef _ROBOT_CAN_DEVICE_H
#define _ROBOT_CAN_DEVICE_H

//sub net master
#define LOCATE        0xff
#define MASTER        0xfe

//locate <--> master
#define LOCATE_SECOND      0x01
#define MASTER_SECOND      0x02
//chassis
#define CHASSIS_BROADCAST  0x00

#define CHASSIS_MOTOR1    0x01
#define CHASSIS_MOTOR2    0x02
#define CHASSIS_MOTOR3    0x03
#define CHASSIS_MOTOR4    0x04
#define CHASSIS_MOTOR5    0x05
#define CHASSIS_MOTOR6    0x06
#define CHASSIS_MOTOR7    0x07
#define CHASSIS_MOTOR8    0x08

//UP MACHINE
//ID:1xxx(B)  //virtual sub net
#define UP_BROADCAST      0x80
#define UP_MAIN_MOTOR     0x01
#define UP_AUX_MOTOR      0x02
#define UP_PITCH_MOTOR    0x03
#define UP_YAW_MOTOR      0x04
#define UP_PUSH_MOTOR     0x05
#define UP_HEAP_MOTOR     0x06



//DOWN MACHINE
//ID:0xxx(B)  //virtual sub net
#define DOWN_BROADCAST    0x00
#define DOWN_MAIN_MOTOR   0x01
#define DOWN_AUX_MOTOR    0x02
#define DOWN_PITCH_MOTOR  0x03
#define DOWN_YAW_MOTOR    0x04
#define DOWN_PUSH_MOTOR   0x05


//INTERNAL DEVICE ID
#define LOCATE_ID     LOCATE
#define MASTER_ID     MASTER

#define LOCATE_SECOND_ID      LOCATE_SECOND
#define MASTER_SECOND_ID      MASTER_SECOND

//chassis
#define CHASSIS_BROADCAST_ID   (CHASSIS_BROADCAST)

#define CHASSIS_MOTOR1_ID  (CHASSIS_BROADCAST_ID + CHASSIS_MOTOR1)
#define CHASSIS_MOTOR2_ID  (CHASSIS_BROADCAST_ID + CHASSIS_MOTOR2)
#define CHASSIS_MOTOR3_ID  (CHASSIS_BROADCAST_ID + CHASSIS_MOTOR3)
#define CHASSIS_MOTOR4_ID  (CHASSIS_BROADCAST_ID + CHASSIS_MOTOR4)
#define CHASSIS_MOTOR5_ID  (CHASSIS_BROADCAST_ID + CHASSIS_MOTOR5)

//UP MACHINE
#define UP_MACHINE_BROADCAST_ID (UP_BROADCAST)			
#define UP_MAIN_MOTOR_ID   (UP_MACHINE_BROADCAST_ID + UP_MAIN_MOTOR)
#define UP_AUX_MOTOR_ID    (UP_MACHINE_BROADCAST_ID + UP_AUX_MOTOR)
#define UP_PITCH_MOTOR_ID  (UP_MACHINE_BROADCAST_ID + UP_PITCH_MOTOR)
#define UP_YAW_MOTOR_ID    (UP_MACHINE_BROADCAST_ID + UP_YAW_MOTOR)
#define UP_PUSH_MOTOR_ID   (UP_MACHINE_BROADCAST_ID + UP_PUSH_MOTOR)

//DOWN MACHINE
#define DOWN_MACHINE_BROADCAST_ID (DOWN_BROADCAST)			
#define DOWN_MAIN_MOTOR_ID   (DOWN_MACHINE_BROADCAST_ID + DOWN_MAIN_MOTOR)
#define DOWN_AUX_MOTOR_ID    (DOWN_MACHINE_BROADCAST_ID + DOWN_AUX_MOTOR)
#define DOWN_PITCH_MOTOR_ID  (DOWN_MACHINE_BROADCAST_ID + DOWN_PITCH_MOTOR)
#define DOWN_YAW_MOTOR_ID    (DOWN_MACHINE_BROADCAST_ID + DOWN_YAW_MOTOR)
#define DOWN_PUSH_MOTOR_ID   (DOWN_MACHINE_BROADCAST_ID + DOWN_PUSH_MOTOR)


#endif

