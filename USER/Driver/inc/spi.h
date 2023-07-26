#ifndef __SPI_H
#define __SPI_H
#include "stm32f4xx.h"
#include "atomIO.h"

#define AS5047P_CS_Pin      GPIO_Pin_12
#define AS5047P_CS_GPIO_Port    GPIOB

#define AS5047P_CLK_Pin     GPIO_Pin_13
#define AS5047P_CLK_GPIO_Port   GPIOB

#define AS5047P_MISO_Pin    GPIO_Pin_14
#define AS5047P_MISO_GPIO_Port  GPIOB

#define AS5047P_MOSI_Pin    GPIO_Pin_15
#define AS5047P_MOSI_GPIO_Port  GPIOB

#define ADXRS453_CS_Pin      GPIO_Pin_12
#define ADXRS453_CS_GPIO_Port    GPIOB

#define ADXRS453_CLK_Pin     GPIO_Pin_13
#define ADXRS453_CLK_GPIO_Port   GPIOB

#define ADXRS453_MISO_Pin    GPIO_Pin_14
#define ADXRS453_MISO_GPIO_Port  GPIOB

#define ADXRS453_MOSI_Pin    GPIO_Pin_15
#define ADXRS453_MOSI_GPIO_Port  GPIOB

void SPI2_Init(void);			 //初始化SPI2口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI2速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI2总线读写一个字节

#endif

