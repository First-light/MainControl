#ifndef _AS5047P_H_
#define _AS5047P_H_

#include "stm32f4xx.h"

typedef enum CheckTransmissionErrorTypedef
{
	PARERR,//Parity error
	INVCOMM,//Invalid command error: set to 1 by reading or writing an invalid register address
	FRERR,//Framing error: is set to 1 when a non-compliant SPI frame is detected 帧错误：检测到不兼容的SPI帧
	ERROR_IDEL,//No error
}CheckTransmissionErrorTypedef;

// AS5047P Register Addresses

/** volatile **/
#define AS5047P_NOP 0x0000
#define AS5047P_ERRFL 0x0001
#define AS5047P_PROG 0x0003
#define AS5047P_DIAAGC 0x3FFC
#define AS5047P_CORDICMAG 0x3FFD
#define AS5047P_ANGLEUNC 0x3FFE
#define AS5047P_ANGLECOM 0x3FFF

/** non-volatile **/
#define AS5047P_ZPOSM 0x0016
#define AS5047P_ZPOSL 0x0017
#define AS5047P_SETTINGS1 0x0018
#define AS5047P_SETTINGS2 0x0019

#define AS5047P_RD 0x4000    // bit 14 = "1" is Read + parity even
#define AS5047P_WR 0x3FFF    // bit 14 = "0" is Write

#define AS5047P_Check_MAG_TooLow(DIAAGC)      ((DIAAGC >> 11) & 0x0001)
#define AS5047P_Check_MAG_TooHigh(DIAAGC)     ((DIAAGC >> 10) & 0x0001)
#define AS5047P_Check_CORDIC_Overflow(DIAAGC) ((DIAAGC >> 9)  & 0x0001)
#define AS5047P_Check_LF_finished(DIAAGC)     ((DIAAGC >> 8)  & 0x0001)

#define AS5047P_CS_0 GPIO_ResetBits(AS5047P_CS_GPIO_Port,AS5047P_CS_Pin)
#define AS5047P_CS_1 GPIO_SetBits(AS5047P_CS_GPIO_Port,AS5047P_CS_Pin)

#define AS5047P_CLK_0 GPIO_ResetBits(AS5047P_CLK_GPIO_Port,AS5047P_CLK_Pin)
#define AS5047P_CLK_1 GPIO_SetBits(AS5047P_CLK_GPIO_Port,AS5047P_CLK_Pin)

#define AS5047P_MOSI_0 GPIO_ResetBits(AS5047P_MOSI_GPIO_Port,AS5047P_MOSI_Pin)
#define AS5047P_MOSI_1 GPIO_SetBits(AS5047P_MOSI_GPIO_Port,AS5047P_MOSI_Pin)

#define AS5047P_MISO GPIO_ReadInputDataBit(AS5047P_MISO_GPIO_Port,AS5047P_MISO_Pin)

extern uint8_t data_correction;

uint16_t AS5047P_Write(uint16_t, uint16_t);
void AS5047P_Read(uint16_t *origin_data,uint16_t address);//读取带地址的数据
unsigned int AS5047D_GetZero(void);
unsigned int AS5047P_Get_AGC_Value(void);
unsigned int AS5047D_Get_CORDICMAG_Value(void);
unsigned int AS5047P_Get_ANGLECOM_Value(void);
unsigned int AS5047P_Get_ANGLEUNC_Value(void);
float AS5047P_Get_True_Angle_Value(void);
void AS5047P_SetZero(void);
unsigned int SPI_READ(void);
void SPI_SEND(unsigned int data);
void AS5047P_Init(void);
void AS5047P_ReadData(uint16_t* origin_data);//读取SPI数据
void AS5047P_Check_Transmission_Error(CheckTransmissionErrorTypedef *TransmissionError);
void AS5047P_SetZero(void);
void MyDelayus(uint32_t delay);
uint16_t parity(uint16_t x);

#endif