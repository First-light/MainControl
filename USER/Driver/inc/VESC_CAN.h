#ifndef _VESC_CAN_H
#define _VESC_CAN_H

#include "stm32f4xx_can.h"
#include "RobotCAN_basic.h"
#include "stdint.h"
#include <string.h>
#include "motor_control.h"



#define frictionleft_id       68
#define frictionright_id     66
#define rotationmotor_id      67
#define shootmotor_ID      69
#define PITCH_ID 11    //俯仰电机ID
#define YAW_ID 12    //回转电机ID

typedef enum {
   CAN_PACKET_SET_DUTY = 0,
   CAN_PACKET_SET_CURRENT,
   CAN_PACKET_SET_CURRENT_BRAKE,
   CAN_PACKET_SET_RPM,
   CAN_PACKET_SET_POS,
   CAN_PACKET_FILL_RX_BUFFER,
   CAN_PACKET_FILL_RX_BUFFER_LONG,
   CAN_PACKET_PROCESS_RX_BUFFER,
   CAN_PACKET_PROCESS_SHORT_BUFFER,
   CAN_PACKET_STATUS,
    CAN_PACKET_SET_CURRENT_REL,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
    CAN_PACKET_GET_STATUS
} CAN_PACKET_ID;


void buffer_append_int32(uint8_t* , int32_t , int32_t *);
void comm_can_transmit_eid(uint32_t, const uint8_t *, uint8_t );
void comm_can_set_duty(uint8_t controller_id, float duty);
void comm_can_set_current(uint8_t controller_id, float current);
void comm_can_set_current_brake(uint8_t controller_id, float current);
void comm_can_set_rpm(uint8_t , float );
void comm_can_set_pos(uint8_t, float);
void comm_can_set_pos_with_speed(uint8_t controller_id, float pos,float rpm);
void VESC_set_pos(uint8_t, float);
void comm_can_get_status(uint8_t controller_id);
void comm_can_set_lock_command(uint8_t controller_id, float current) ;

void ProcessVESCFrame(Frame *Frame_Process);


#endif
