#ifndef __SAMPLE_H
#define __SAMPLE_H
#include "stm32f4xx.h"

#define SAMPLE_DEPTH 3000
#define SAMPLE_DWORD_WIDTH 4  //SAMPLE_DWORD_WIDTH <= 4


typedef union
{
    int8_t	 int8_ts[SAMPLE_DWORD_WIDTH * 4];
    int16_t	 int16_ts[SAMPLE_DWORD_WIDTH * 2];
    int32_t	 int32_ts[SAMPLE_DWORD_WIDTH];
    uint8_t	 uint8_ts[SAMPLE_DWORD_WIDTH * 4];
    uint16_t uint16_ts[SAMPLE_DWORD_WIDTH * 2];
    uint32_t uint32_ts[SAMPLE_DWORD_WIDTH];
    float    floats_ts[SAMPLE_DWORD_WIDTH];
}SAMPLE_DATA_TYPE;

typedef enum
{
	SAMPLE_IDLE = 0,
	SAMPLE_WRITE = 1,
	SAMPLE_READ = 2,
	SAMPLE_FORBID = 3,   //forbid write
	SAMPLE_BLANK = 4,
}SAMPLER_STATE_Type;


typedef enum
{
	OPERATE_FAIL = 0,
	OPERATE_SUCCESS = 1,
}SAMPLER_OPERATE_Type;


void SampleForbid();
void SampleEnable();

SAMPLER_OPERATE_Type SampleAdd(SAMPLE_DATA_TYPE* SampleValue);
SAMPLER_OPERATE_Type SampleGet(SAMPLE_DATA_TYPE* ValueBuff);
SAMPLER_STATE_Type SampleInquire();
uint16_t SampleLength();

#endif