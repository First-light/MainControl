#ifndef _ADXRS453DRIVER_H_
#define _ADXRS453DRIVER_H_  

#include "stm32f4xx.h"
#include "spi.h"

#define ADXRS453_CS_0 GPIO_ResetBits(ADXRS453_CS_GPIO_Port,ADXRS453_CS_Pin)
#define ADXRS453_CS_1 GPIO_SetBits(ADXRS453_CS_GPIO_Port,ADXRS453_CS_Pin)

#define ADXRS453_CLK_0 GPIO_ResetBits(ADXRS453_CLK_GPIO_Port,ADXRS453_CLK_Pin)
#define ADXRS453_CLK_1 GPIO_SetBits(ADXRS453_CLK_GPIO_Port,ADXRS453_CLK_Pin)

#define ADXRS453_MOSI_0 GPIO_ResetBits(ADXRS453_MOSI_GPIO_Port,ADXRS453_MOSI_Pin)
#define ADXRS453_MOSI_1 GPIO_SetBits(ADXRS453_MOSI_GPIO_Port,ADXRS453_MOSI_Pin)

#define ADXRS453_MISO GPIO_ReadInputDataBit(ADXRS453_MISO_GPIO_Port,ADXRS453_MISO_Pin)

#define   RATE1   0x00
#define   RATE0   0x01
#define   TEM1    0x02
#define   TEM0    0x03
#define   LOSCT1  0x04
#define   LOSCT0  0x05
#define   HICST1  0x06
#define   HICST0  0x07
#define   QUAD1   0x08
#define   QUAD0   0x09
#define   FAULT1  0x0A
#define   FAULT0  0x0B
#define   PID1    0x0C
#define   PID0    0x0D
#define   SN3     0x0E
#define   SN2     0x0F
#define   SN1     0x10
#define   SN0     0x11

// Mode
#define WRITE       0x00
#define READ        0x01

int  ADXRS453Command(unsigned char Address, unsigned int SendValue, unsigned char OperateType);
int  ADXRS453SingleRead(unsigned char Address);
int  ADXRS453SensorData(void);
void ADXRS453StartUp(void);
uint32_t ADXRS453_SpiFunction(uint32_t TxData);

float GyroInitNormal(void);
float ReadGyroRate(void);
#endif
