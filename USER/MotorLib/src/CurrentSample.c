#include "CurrentSample.h"
#include "Sample.h"
#include "filter.h"

float FilterSample;
static float preSampleValue = 2048;

void CurrentSample(uint16_t value)
{	  
	  float adcValue;
	  SAMPLE_DATA_TYPE SampleValue;
	
	  SampleValue.floats_ts[3] = (float)(DT_US_COUNT);
		
	  adcValue  = (float)(value);

	  
		
//		arm_biquad_cascade_df2T_f32(&sFliter,&adcValue,&FilterSample,1);
//		FilterSample = GAIN * FilterSample;
	  
	  SampleValue.floats_ts[0] = adcValue;
		SampleValue.floats_ts[1] = (adcValue + preSampleValue)/2.0f;
		  
		SampleValue.floats_ts[2] = (float)(Motor.PWM);
		
    SampleAdd(&SampleValue);
	
		preSampleValue = adcValue;
}

float GetCurrent()
{
	return (FilterSample - ADC_MEDIAN) * ADC2CURRENT;
}



