#ifndef _FILTER_H_
#define _FILTER_H_

#include "arm_math.h"

//滤波器生成参数

#define GAIN 0.3665f

#define NUM_STAGES 6

#define SAMPLE_RATE  20000

extern arm_biquad_cascade_df2T_instance_f32 sFliter;

extern float pState[2* NUM_STAGES];

extern float pCoeffs[5 * NUM_STAGES];

#endif