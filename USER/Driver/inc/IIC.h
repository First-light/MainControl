#ifndef IIC_H_
#define IIC_H_

#include "stm32f4xx_spi.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "Includes.h"
#include "delay.h"

#define IIC_GPIO_CLK_CMD            RCC_AHB1PeriphClockCmd
#define IIC_GPIO_PORT               GPIOB
#define IIC_CLK                     RCC_AHB1Periph_GPIOB

#define IIC_SCL                     GPIO_Pin_8
#define IIC_SDA                     GPIO_Pin_9

void IIC_Write_Port(u8 dat,u8 *err);
void IIC_Hard_Init(void);

#endif
