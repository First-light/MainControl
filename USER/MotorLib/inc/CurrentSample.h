#ifndef __CURRENT_SAMPLE_H
#define __CURRENT_SAMPLE_H
#include "stm32f4xx.h"
#include "includes.h"
#include "globalTime.h"

#define ADC2CURRENT               (5000.0f/4096.0f*10.0f)    //LSB->mA
#define ADC_MEDIAN                 2048.0f

void  CurrentSample(uint16_t val);
float GetCurrent(void);

#endif


