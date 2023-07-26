#include "Sample.h"

static SAMPLE_DATA_TYPE SampleArray[SAMPLE_DEPTH + 1];

volatile static u16 SampleIndex = 0;   //index 0 is preserved



volatile static u16 SampleState = SAMPLE_FORBID;




SAMPLER_OPERATE_Type SampleAdd(SAMPLE_DATA_TYPE *SampleValue)
{
	u8 SampleColumIndex = 0;
	if(SampleState == SAMPLE_IDLE && SampleIndex < SAMPLE_DEPTH)
	{
		SampleState = SAMPLE_WRITE;
		SampleIndex++;

		SampleArray[SampleIndex] = *SampleValue;	

    SampleState	= SAMPLE_IDLE;
		if(SampleIndex == SAMPLE_DEPTH)
		{
			SampleForbid();
		}
		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}

static u8 preSampleState;

SAMPLER_OPERATE_Type SampleGet(SAMPLE_DATA_TYPE* ValueBuff)
{
	u8 SampleColumIndex = 0;
	if(SampleIndex > 0 )
	{
		preSampleState = SampleState;
		SampleState = SAMPLE_READ;

		*ValueBuff = SampleArray[SampleIndex];
		
		SampleIndex--;
		SampleState	= preSampleState;
		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}

void SampleForbid()
{
	SampleState = SAMPLE_FORBID;
}

void SampleEnable()
{
	SampleState = SAMPLE_IDLE;
}

SAMPLER_STATE_Type SampleInquire()
{
	if(SampleIndex == 0 && SampleState == SAMPLE_IDLE)
	{
		return SAMPLE_BLANK;
	}
	return SampleState;
}

uint16_t SampleLength()
{
	return SampleIndex; 
}
