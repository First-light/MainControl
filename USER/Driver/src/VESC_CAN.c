#include "VESC_CAN.h"
#include "RobotCAN_Basic.h"
#include "MyGlobe.h"
#include "hust_math_lib.h"
void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) {
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

uint16_t buffer_get_uint16(const uint8_t *buffer, int32_t *index) {
	uint16_t res = 	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}

int32_t buffer_get_int32(const uint8_t *buffer, int32_t *index) {
	int32_t res =	((uint32_t) buffer[*index]) << 24 |
					((uint32_t) buffer[*index + 1]) << 16 |
					((uint32_t) buffer[*index + 2]) << 8 |
					((uint32_t) buffer[*index + 3]);
	*index += 4;
	return res;
}

void comm_can_get_status(uint8_t controller_id)
{
    int32_t send_index = 0;
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_GET_STATUS << 8), 0, send_index);
}

void comm_can_set_duty(uint8_t controller_id, float duty) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

void comm_can_set_current(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void comm_can_set_current_brake(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), buffer, send_index);
}

void comm_can_set_rpm(uint8_t controller_id, float rpm) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)rpm, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}

void comm_can_set_pos(uint8_t controller_id, float pos) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(pos * 1000000.0), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}

void comm_can_set_pos_with_speed(uint8_t controller_id, float pos,float rpm) {
  int32_t send_index = 0;
	uint8_t buffer[8];
	buffer_append_int32(buffer, (int32_t)(pos * 1000000.0f), &send_index);
	buffer_append_int32(buffer, (int32_t)rpm, &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}
void comm_can_set_lock_command(uint8_t controller_id, float current) {
  int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
	comm_can_transmit_eid(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT_HANDBRAKE << 8), buffer, send_index);
}
void comm_can_transmit_eid(uint32_t id, const uint8_t *data, uint8_t len) {
	CanTxMsg txmsg;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;

    if (len > 8) {
		len = 8;
	}
//  CanTxMsg txmsg;
	txmsg.IDE = CAN_ID_EXT;
	txmsg.ExtId = id;
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = len;
	memcpy(txmsg.Data, data, len);
    while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &txmsg);
	}
}


void VESC_set_pos(uint8_t controller_id, float pos)
{
    uint32_t pos_temp = (pos * 1000000.0);
    uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	CanTxMsg txmsg;
	txmsg.IDE = CAN_ID_EXT;
	txmsg.ExtId = controller_id |((uint32_t)CAN_PACKET_SET_POS << 8);
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = 8;
    
	txmsg.Data[0] = pos_temp>>24;
	txmsg.Data[1] = pos_temp>>16;
	txmsg.Data[2] = pos_temp>>8;
	txmsg.Data[3] = pos_temp;
	txmsg.Data[4] = 0;
	txmsg.Data[5] = 0;
	txmsg.Data[6] = 0;
	txmsg.Data[7] = 0;

    while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &txmsg);
	}

}

void ProcessVESCFrame(Frame *Frame_Process)
{
	int32_t get_index = 0;
  EXT_ID_Typedef ExtId;
  ExtId = Frame_Process->id.ExtID;
	if(ExtId.DesDEVICE_ID==shootmotor_ID&&ExtId.Property==CAN_PACKET_STATUS){//??电机接收
		motorring.SpeedMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index);
		motorring.PositionMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index) /10000.0f;
	}
	if(ExtId.DesDEVICE_ID==frictionright_id&&ExtId.Property==CAN_PACKET_STATUS){//??电机接收
		frictionright.SpeedMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index);
		frictionright.PositionMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index) /10000.0f;
	}
	if(ExtId.DesDEVICE_ID==frictionleft_id &&ExtId.Property==CAN_PACKET_STATUS){//??电机接收
		frictionleft.SpeedMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index);
		frictionleft.PositionMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index) /10000.0f;
	}
	if(ExtId.DesDEVICE_ID==rotationmotor_id&&ExtId.Property==CAN_PACKET_STATUS){//??电机接收
		rotationmotor.SpeedMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index);
		rotationmotor.PositionMeasure = (float)buffer_get_int32(Frame_Process->data.uchars,&get_index) /10000.0f;
	}
}

